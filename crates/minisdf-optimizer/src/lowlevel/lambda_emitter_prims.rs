use ahash::AHashMap;
use minisdf_ast::{BinOpTy, PrimTy, UnOpTy};
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

pub fn emit_prim_op<P: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, P>,
    node: &HLOp,
    prim: PrimTy,
    hl_graph: &HLGraph,
    hl_ll_map: AHashMap<NodeRef, NodeRef>,
) -> OutportLocation {
    match prim {
        PrimTy::Box => {

        }
        _ => todo!("impl prims"),
    }
}


fn emit_box<P: StructuralNode>(region: &mut RegionBuilder<LLOp, OptEdge, P>, node: &HLOp, hl_graph: &HLGraph, hl_ll_map: AHashMap<NodeRef, NodeRef>) -> OutportLocation{
    let (lmd_box, _) = region.new_function(|lmd_box|{

    })
}
