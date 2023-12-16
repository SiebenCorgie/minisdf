use ahash::AHashMap;
use minisdf_ast::{BinOpTy, UnOpTy};
use minisdf_common::Span;
use rvsdg::{
    builder::RegionBuilder,
    edge::{OutportLocation, OutputType},
    nodes::StructuralNode,
    NodeRef,
};

use crate::{edge::OptEdge, highlevel::HLOp, HLGraph};

use super::{
    emit_walker::{emit_const_f32, hl_ll_walk},
    LLOp, LLOpTy,
};

pub fn emit_binary_op<P: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, P>,
    node: &HLOp,
    bop: BinOpTy,
    hl_graph: &HLGraph,
    hl_ll_map: AHashMap<NodeRef, NodeRef>,
) -> OutportLocation {
    match bop {
        BinOpTy::Error => panic!("binop was error"),
        BinOpTy::Intersection => {
            emit_simple_bop(region, node, hl_graph, hl_ll_map, SimpleBop::Intersection)
        }
        BinOpTy::Subtraction => {
            emit_simple_bop(region, node, hl_graph, hl_ll_map, SimpleBop::Subtraction)
        }
        BinOpTy::Union => emit_simple_bop(region, node, hl_graph, hl_ll_map, SimpleBop::Union),
    }
}

enum SimpleBop {
    Union,
    Subtraction,
    Intersection,
}

fn emit_simple_bop<P: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, P>,
    node: &HLOp,
    hl_graph: &HLGraph,
    hl_ll_map: AHashMap<NodeRef, NodeRef>,
    bop_arg: SimpleBop,
) -> OutportLocation {
    //for simple binary ops we have only our two subnodes, so we call those, apply them, and call bop (min, max, -d,).

    let (lambda_node, ()) = region.new_function(|intersection| {
        let intersection_output = intersection.add_result();
        intersection.on_region(|inter_region| {
            let left_src = hl_graph
                .graph
                .edge(*node.inputs[0].edge.as_ref().unwrap())
                .src
                .clone();
            //NOTE: all nodes in HL have only one output, so we don't need to inspect hte left_src.output_type.
            let left = hl_ll_walk(inter_region, left_src.node, hl_graph, hl_ll_map);

            let right_src = hl_graph
                .graph
                .edge(*node.inputs[1].edge.as_ref().unwrap())
                .src
                .clone();
            let right = hl_ll_walk(inter_region, right_src.node, hl_graph, hl_ll_map);

            //depending on bop_arg, emit min, max or negate left and emit max
            let min_node = match bop_arg {
                SimpleBop::Intersection => {
                    let (min_node, _edges) = inter_region
                        .connect_node(
                            LLOp::new(LLOpTy::Min, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[left_src, right_src],
                        )
                        .unwrap();
                    min_node
                }
                SimpleBop::Union => {
                    let (max_node, _edges) = inter_region
                        .connect_node(
                            LLOp::new(LLOpTy::Max, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[left_src, right_src],
                        )
                        .unwrap();
                    max_node
                }
                SimpleBop::Subtraction => {
                    //negate left then max both
                    let minus_one = emit_const_f32(inter_region, -1.0);
                    let (muled, _edg) = inter_region
                        .connect_node(
                            LLOp::new(LLOpTy::Mul, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[minus_one, left_src],
                        )
                        .expect("Could not negate left_src for Subtraction operation");
                    //now do max on muled and right_src

                    let (max_node, _edges) = inter_region
                        .connect_node(
                            LLOp::new(LLOpTy::Max, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[muled.as_outport_location(OutputType::Output(0)), right_src],
                        )
                        .unwrap();
                    max_node
                }
            };

            inter_region
                .ctx_mut()
                .connect(
                    min_node.as_outport_location(OutputType::Output(0)),
                    intersection_output,
                    OptEdge::Value,
                )
                .expect("Could not connect intersection output to λ result");
        });
    });

    //Create the intersection lambda node in `region`. Now call it and return the output port of the call
    let (call, _edg) = region
        .call(
            lambda_node.as_outport_location(OutputType::LambdaDeclaration),
            &[],
        )
        .expect("Could not call Intersection");
    call.as_outport_location(OutputType::Output(0))
}

pub fn emit_unary_op<P: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, P>,
    node: &HLOp,
    bop: UnOpTy,
    hl_graph: &HLGraph,
    hl_ll_map: AHashMap<NodeRef, NodeRef>,
) -> OutportLocation {
    todo!("impl")
}
