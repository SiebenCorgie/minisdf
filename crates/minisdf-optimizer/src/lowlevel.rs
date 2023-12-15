//! The HL -> LL transformation does two things
//! 1. transfor each highlevel node to a λ-Node
//! 2. build a static stack for the position (or @) variable, by supplying it as the first argument to any λ-node
//!
//! Each λ-Node that was created returns a single float (the signed distance), per definition.

use crate::{edge::OptEdge, err::OptError, highlevel::HLOpTy, HLGraph};
use ahash::AHashMap;
use minisdf_ast::Ty;
use minisdf_common::Span;
use rvsdg::{
    attrib::AttribStore,
    edge::{OutportLocation, OutputType},
    nodes::LangNode,
    region::{Input, Output},
    NodeRef, Rvsdg,
};
use tinyvec::TinyVec;

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
}

#[derive(Debug)]
pub struct LLOp {
    pub ty: LLOpTy,
    //The source span this op originates from.
    pub span: Span,
    pub inputs: TinyVec<[Input; 3]>,
    pub outputs: TinyVec<[Output; 3]>,
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
    pub fn into_ll_graph(self) -> LLGraph {
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
        let (at_import, sdf_export, params) = llgraph.on_omega_node(|omega| {
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

        //now explore the tree, and build the recursive call structure.

        LLGraph {
            graph: llgraph,
            type_table: ll_type_table,
            labels: ll_labels,
        }
    }
}

///Emits all λ-nodes that can be called by any HLOpTy. Returns the lookup table for the λ-declerations
fn emit_all_lambda_decls() -> AHashMap<HLOpTy, OutportLocation> {
    let mut table = AHashMap::new();

    todo!("build table");

    table
}

fn map_node(
    hl_node: NodeRef,
    llgraph: Rvsdg<LLOp, OptEdge>,
    ll_type_table: &mut AttribStore<Ty>,
    ll_labels: AttribStore<String>,
    lambda_decl_map: AHashMap<HLOpTy, OutportLocation>,
    hl_ll_node_map: AHashMap<NodeRef, NodeRef>,
) -> Result<(), OptError> {
    //Recursive transformer

    Ok(())
}
