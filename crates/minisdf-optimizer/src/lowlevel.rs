//! The HL -> LL transformation does two things
//! 1. transfor each highlevel node to a λ-Node
//! 2. build a static stack for the position (or @) variable, by supplying it as the first argument to any λ-node
//!
//! Each λ-Node that was created returns a single float (the signed distance), per definition.

use std::collections::VecDeque;

use crate::{
    edge::OptEdge,
    highlevel::{HLOp, HLOpTy},
    HLGraph,
};
use ahash::AHashMap;
use minisdf_ast::Ty;
use minisdf_common::Span;
use rvsdg::{
    attrib::AttribStore,
    builder::RegionBuilder,
    edge::{OutportLocation, OutputType},
    nodes::{LangNode, NodeType, OmegaNode, StructuralNode},
    region::{Input, Output},
    NodeRef, Rvsdg,
};
use tinyvec::TinyVec;

use self::{
    emit_walker::LambdaLookupKey, lambda_emitter_ops::build_lambda_ops,
    lambda_emitter_prims::build_lambda_prims,
};

mod emit_walker;
mod lambda_emitter_ops;
mod lambda_emitter_prims;
mod view;

#[derive(Debug)]
pub enum LLOpTy {
    Error,

    Add,
    Sub,
    Mul,
    Div,

    ///Rounds the fraction to the next integer.
    Round,
    ///Calculates a vector's length
    Length,
    ///Choses the maximum of two values
    Max,
    ///Choses the minimum of two values
    Min,

    ///Selects the n-th coord of a vector.
    ///
    /// `n` needs to be an integer < the arity of the vector argument
    CoordSelect,

    Abs,
    ///Dot product of two same-arity vectors.
    Dot,

    ImmF32(f32),
    ImmI32(i32),
    TypeConstruct(Ty),
}

#[derive(Debug)]
pub struct LLOp {
    pub ty: LLOpTy,
    //The source span this op originates from.
    pub span: Span,
    pub inputs: TinyVec<[Input; 3]>,
    pub outputs: TinyVec<[Output; 3]>,
}

impl LLOp {
    pub fn new(ty: LLOpTy, span: Span) -> Self {
        LLOp {
            ty,
            span,
            inputs: TinyVec::default(),
            outputs: TinyVec::default(),
        }
    }

    pub fn with_inputs(mut self, input_count: usize) -> Self {
        self.inputs.resize(input_count, Input::default());
        self
    }
    pub fn with_outputs(mut self, output_count: usize) -> Self {
        self.outputs.resize(output_count, Output::default());
        self
    }
}

impl LangNode for LLOp {
    fn inputs(&self) -> &[Input] {
        &self.inputs
    }
    fn inputs_mut(&mut self) -> &mut [Input] {
        &mut self.inputs
    }
    fn outputs(&self) -> &[Output] {
        &self.outputs
    }
    fn outputs_mut(&mut self) -> &mut [Output] {
        &mut self.outputs
    }
}

pub struct LLGraph {
    pub graph: Rvsdg<LLOp, OptEdge>,
    pub type_table: AttribStore<Ty>,
    //debugging label
    pub labels: AttribStore<String>,
}

impl HLGraph {
    pub fn into_ll_graph(mut self) -> LLGraph {
        //The general algorithm introduces a new @-parameter to the ω-Region, we then explore the hl-tree bottom up. For each node we emit the
        // λ-Node template, that internally will call all siblings (for binary-op, single child for unary-op, no child for prim). The @-parameter is always supplied as first argument to the internal
        // λ-nodes / calls.
        //
        // This scheme allows us to change @ before calls on a per-hl-op basis, as well as change the returned signed distance, before passing it up the tree.

        let mut llgraph = Rvsdg::new();
        let mut ll_type_table = AttribStore::new();
        let mut ll_labels = AttribStore::new();
        //lookuptable that lets you map a hl NodeRef to a ll NodeRef,
        let mut hl_ll_node_map: AHashMap<NodeRef, NodeRef> = AHashMap::default();

        //setup the ω-region's @ import, and copy all imports from the hl graph including type information
        let (at_import, sdf_export, _params) = llgraph.on_omega_node(|omega| {
            let at_import = omega.import();
            ll_type_table.push_attrib(&at_import.clone().into(), Ty::Vec3);
            ll_labels.push_attrib(&at_import.clone().into(), "at".to_owned());

            let hl_omega_node = self.graph.entry_node();
            //add the omega->omega mapping
            hl_ll_node_map.insert(hl_omega_node, omega.on_region(|reg| reg.parent()));
            let mut cpy_params = Vec::new();
            //copy the import decls to the llgraph
            for (import_idx, _import) in self
                .graph
                .node(hl_omega_node)
                .regions()
                .get(0)
                .unwrap()
                .arguments
                .iter()
                .enumerate()
            {
                let ll_import = omega.import();
                let hl_port_location = OutportLocation {
                    node: hl_omega_node,
                    output: OutputType::Argument(import_idx),
                };
                if let Some(tys) = self.type_table.attrib(&hl_port_location.clone().into()) {
                    if tys.len() > 1 {
                        println!(
                            "Warning: HLNode omega had >1 type declerations on import {}",
                            import_idx
                        );
                    }

                    if let Some(ty) = tys.get(0) {
                        ll_type_table.push_attrib(&ll_import.clone().into(), ty.clone());
                    }
                }

                cpy_params.push(ll_import);
            }

            //Add export as well
            let exp = omega.export();

            (at_import, exp, cpy_params)
        });

        //build all lambda declerations we need, and save them to the lookuptable
        let mut lambda_lt = AHashMap::default();
        llgraph.on_omega_node(|omgea| {
            omgea.on_region(|reg| {
                build_lambda_lt(reg, &mut lambda_lt);
            })
        });

        //now explore the tree, and build the recursive call structure.
        //we pick the seeding op our self
        let start_hl_node = self.graph.on_omega_node(|omg| {
            let omg_export_edge = omg.node().get_export(0).unwrap().edge.unwrap();
            omg.on_region(|reg| reg.ctx().edge(omg_export_edge).src.clone().node)
        });

        llgraph.on_omega_node(|omg| {
            omg.on_region(|reg| {
                let export_node =
                    build_call_trees(start_hl_node, &self, &lambda_lt, at_import, reg);
                reg.ctx_mut()
                    .connect(export_node, sdf_export, OptEdge::Value)
                    .expect("Could not connect to export!")
            })
        });

        LLGraph {
            graph: llgraph,
            type_table: ll_type_table,
            labels: ll_labels,
        }
    }
}

pub fn build_lambda_lt<R: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, R>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    build_lambda_ops(region, lambda_lt);
    build_lambda_prims(region, lambda_lt);
}

///Transforms some HL node's `arg` in `hl_graph` into a ll_graph output.
///
/// This takes care of translating constant creation, type construction and ω-Node argument rounting.
fn arg_to_outport(
    node: &HLOp,
    arg: usize,
    hl_graph: &HLGraph,
    ll_region: &mut RegionBuilder<LLOp, OptEdge, OmegaNode>,
) -> OutportLocation {
    let arg = {
        let edg = node.inputs[arg]
            .edge
            .as_ref()
            .expect("Expected arg to be connected");
        hl_graph.graph.edge(*edg).src.clone()
    };

    //at this point, check what we have at src
    let src_hl_node = match &hl_graph.graph.node(arg.node).node_type {
        NodeType::Omega(_o) => {
            //In case of an omega node, we should be an argument, not a output
            assert!(arg.output.is_argument());
            //match the argument index to the ll_regions index
            //NOTE: per definition this is the hl_arg_index + 1 in the ll_graph
            if let OutputType::Argument(i) = arg.output {
                return ll_region
                    .ctx()
                    .entry_node()
                    .as_outport_location(OutputType::Argument(i + 1));
            } else {
                panic!("argument came from omega node, but was no argument");
            }
        }
        NodeType::Simple(hl) => {
            assert!(!arg.output.is_argument());
            hl
        }
        _ => panic!("Unexpected node type!"),
    };

    match &src_hl_node.ty {
        HLOpTy::ConstFloat(f) => ll_region
            .insert_node(LLOp::new(LLOpTy::ImmF32(*f), Span::empty()).with_outputs(1))
            .as_outport_location(OutputType::Output(0)),

        HLOpTy::ConstInt(i) => ll_region
            .insert_node(
                LLOp::new(
                    LLOpTy::ImmI32(i.clone().try_into().expect("Could not turn isize into i32")),
                    Span::empty(),
                )
                .with_outputs(1),
            )
            .as_outport_location(OutputType::Output(0)),

        HLOpTy::TyConst(ty) => match ty {
            Ty::Error | Ty::Sdf | Ty::Int | Ty::Float => panic!("Type error on type constructor"),
            Ty::Vec2 => {
                let x = arg_to_outport(&src_hl_node, 0, hl_graph, ll_region);
                let y = arg_to_outport(&src_hl_node, 1, hl_graph, ll_region);
                let (create_node, _) = ll_region
                    .connect_node(
                        LLOp::new(LLOpTy::TypeConstruct(Ty::Vec2), Span::empty())
                            .with_inputs(2)
                            .with_outputs(1),
                        &[x, y],
                    )
                    .expect("Could not create vec2");
                create_node.as_outport_location(OutputType::Output(0))
            }
            Ty::Vec3 => {
                let x = arg_to_outport(&src_hl_node, 0, hl_graph, ll_region);
                let y = arg_to_outport(&src_hl_node, 1, hl_graph, ll_region);
                let z = arg_to_outport(&src_hl_node, 2, hl_graph, ll_region);
                let (create_node, _) = ll_region
                    .connect_node(
                        LLOp::new(LLOpTy::TypeConstruct(Ty::Vec3), Span::empty())
                            .with_inputs(3)
                            .with_outputs(1),
                        &[x, y, z],
                    )
                    .expect("Could not create vec3");
                create_node.as_outport_location(OutputType::Output(0))
            }
            Ty::Vec4 => {
                let x = arg_to_outport(&src_hl_node, 0, hl_graph, ll_region);
                let y = arg_to_outport(&src_hl_node, 1, hl_graph, ll_region);
                let z = arg_to_outport(&src_hl_node, 2, hl_graph, ll_region);
                let w = arg_to_outport(&src_hl_node, 3, hl_graph, ll_region);
                let (create_node, _) = ll_region
                    .connect_node(
                        LLOp::new(LLOpTy::TypeConstruct(Ty::Vec4), Span::empty())
                            .with_inputs(4)
                            .with_outputs(1),
                        &[x, y, z, w],
                    )
                    .expect("Could not create vec4");
                create_node.as_outport_location(OutputType::Output(0))
            }
        },

        _ => panic!("Unexpected node type: {:?}", src_hl_node.ty),
    }
}

///Builds the call to `hl_node` in the low-level graph, and, if needed advances the
/// `at_stack`
pub fn build_call_trees(
    hl_node: NodeRef,
    hl_graph: &HLGraph,
    lambda_lt: &AHashMap<LambdaLookupKey, OutportLocation>,
    ll_at_stack_port: OutportLocation,
    ll_region: &mut RegionBuilder<LLOp, OptEdge, OmegaNode>,
) -> OutportLocation {
    let node = if let NodeType::Simple(s) = &hl_graph.graph.node(hl_node).node_type {
        s
    } else {
        panic!("Found non-simple node in hl graph")
    };

    match &node.ty {
        HLOpTy::BinaryOp(bop) => {
            //if there is an on_at call involved, append to the at_tree, otherwise don't.
            println!("BinOp: {:?}", bop);
            let call_arg_range = node.inputs.len() - 2;
            let mut args = (0..call_arg_range)
                .into_iter()
                .map(|argidx| arg_to_outport(&node, argidx, hl_graph, ll_region))
                .collect::<Vec<_>>();

            //push the @value to the args buffer
            args.push(ll_at_stack_port.clone());

            let at_port = if let Some(on_at_lambda) = lambda_lt.get(&LambdaLookupKey::BinaryOp {
                op: bop.clone(),
                on_at: true,
            }) {
                // Call the on_stack lambda with all arguments, except for the last two, which should be the
                // sdf recursions

                let (apply_node, _) = ll_region
                    .call(on_at_lambda.clone(), &args)
                    .expect("Could not connect binary op on_at call");
                apply_node.as_outport_location(OutputType::Output(0))
            } else {
                ll_at_stack_port.clone()
            };

            //Evaluate both sides
            let sdf0_edge = hl_graph.graph.edge(
                *node
                    .inputs
                    .get(call_arg_range)
                    .unwrap()
                    .edge
                    .as_ref()
                    .unwrap(),
            );
            let sdf0 = build_call_trees(
                sdf0_edge.src.clone().node,
                hl_graph,
                lambda_lt,
                at_port.clone(),
                ll_region,
            );

            let sdf1_edge = hl_graph.graph.edge(
                *node
                    .inputs
                    .get(call_arg_range + 1)
                    .unwrap()
                    .edge
                    .as_ref()
                    .unwrap(),
            );
            let sdf1 = build_call_trees(
                sdf1_edge.src.clone().node,
                hl_graph,
                lambda_lt,
                at_port,
                ll_region,
            );

            //same for the "on_sdf" portion. but this time we pre evalute both first arguments
            if let Some(on_at_lambda) = lambda_lt.get(&LambdaLookupKey::BinaryOp {
                op: bop.clone(),
                on_at: false,
            }) {
                //push both sdfs
                args.push(sdf0);
                args.push(sdf1);

                let (apply_node, _) = ll_region
                    .call(on_at_lambda.clone(), &args[..args.len() - 1])
                    .expect("Could not connect binary op post_at call");
                apply_node.as_outport_location(OutputType::Output(0))
            } else {
                panic!("Found no post_evaluation rule for binary op");
            }
        }
        HLOpTy::UnaryOp(uop) => {
            println!("UnOp: {:?}", uop);
            //Unary calls work similar to binary calls. But this time both, pre and post evaluation rules
            // are optional.
            let call_arg_range = node.inputs.len() - 1;
            let mut args = (0..call_arg_range)
                .into_iter()
                .map(|argidx| arg_to_outport(&node, argidx, hl_graph, ll_region))
                .collect::<Vec<_>>();
            //push the @value to the args buffer
            args.push(ll_at_stack_port.clone());

            let at_port = if let Some(on_at_lambda) = lambda_lt.get(&LambdaLookupKey::UnaryOp {
                op: uop.clone(),
                on_at: true,
            }) {
                // Call the on_stack lambda with all arguments, except for the last two, which should be the
                // sdf recursions
                let (apply_node, _) = ll_region
                    .call(on_at_lambda.clone(), &args)
                    .expect("Could not connect binary op on_at call");
                apply_node.as_outport_location(OutputType::Output(0))
            } else {
                ll_at_stack_port.clone()
            };

            //Evaluate inner sdf
            let sdf0_edge = hl_graph.graph.edge(
                *node
                    .inputs
                    .get(call_arg_range)
                    .unwrap()
                    .edge
                    .as_ref()
                    .unwrap(),
            );
            let sdf0 = build_call_trees(
                sdf0_edge.src.clone().node,
                hl_graph,
                lambda_lt,
                at_port,
                ll_region,
            );

            //same for the "on_sdf" portion. but this time we pre evalute both first arguments
            if let Some(on_at_lambda) = lambda_lt.get(&LambdaLookupKey::UnaryOp {
                op: uop.clone(),
                on_at: false,
            }) {
                //push both sdfs
                args.push(sdf0);

                let (apply_node, _) = ll_region
                    .call(on_at_lambda.clone(), &args[0..args.len() - 1])
                    .expect("Could not connect binary op post_at call");
                apply_node.as_outport_location(OutputType::Output(0))
            } else {
                sdf0
            }
        }
        HLOpTy::Prim(p) => {
            println!("Prim: {:?}", p);
            //primitive calculation is at the _middle_ of both of our trees. It ties the ll_at_stack to the sdf tree, by
            // evaluating the sdf at the _at_
            let op = if let Some(op) = lambda_lt.get(&LambdaLookupKey::Prim { prim: p.clone() }) {
                op
            } else {
                panic!("No lambda found for prim op {:?}", p);
            };

            //find all argument ports, then call the sdf lambda and return the result port
            let call_arg_range = node.inputs.len();
            let mut args = (0..call_arg_range)
                .into_iter()
                .map(|argidx| arg_to_outport(&node, argidx, hl_graph, ll_region))
                .collect::<Vec<_>>();

            //add the @ parameter that is active to the front
            args.push(ll_at_stack_port);

            let (apply_node, _) = ll_region
                .call(op.clone(), &args)
                .expect("Could not connect prim-op args");
            apply_node.as_outport_location(OutputType::Output(0))
        }
        _ => panic!("Unexpected node type: {:?}", node.ty),
    }
}
