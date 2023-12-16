use ahash::AHashMap;
use minisdf_common::Span;
use rvsdg::{
    builder::RegionBuilder,
    edge::OutportLocation,
    nodes::{NodeType, StructuralNode},
    region::Inport,
    NodeRef,
};

use crate::{edge::OptEdge, highlevel::HLOpTy, HLGraph};

use super::{
    lambda_emitter_ops::{emit_binary_op, emit_unary_op},
    LLOp, LLOpTy,
};

pub fn emit_const_i32<P: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, P>,
    int: i32,
) -> OutportLocation {
    region
        .insert_node(LLOp::new(LLOpTy::ImmI32(int), Span::empty()).with_outputs(1))
        .as_outport_location(rvsdg::edge::OutputType::Output(0))
}
pub fn emit_const_f32<P: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, P>,
    float: f32,
) -> OutportLocation {
    region
        .insert_node(LLOp::new(LLOpTy::ImmF32(float), Span::empty()).with_outputs(1))
        .as_outport_location(rvsdg::edge::OutputType::Output(0))
}

pub enum HLArgTy {
    ///Was an external argument (to the field), this is the matched OutportLocation in the HLGraph, needs to be imported.
    ExternalArg(OutportLocation),
}

///Figures out input `port` on `node` and resolves it to some Outport in `region`.
///
/// This takes care one of those cases, depending on the connection type:
///
/// - Connected to HLNode: call hl_ll_walk(), which will resolve the whole subtree and return the SDF output of that node.
/// - Connected to OmegaNode argument: Resolves to the equivalent LL-OmegaNode argument, and imports the value into `region`
/// - Connected to const (or tree of const operations, which currently is only a set of VecConst HL operations): builds the construction tree and returns the
/// final result.
pub fn arg_to_port(arg: &Inport) -> HLArgTy {}

///Walks a single node in the high_level graph, and translates it, and its siblings into the recursive call structure of the ll graph.
pub fn hl_ll_walk<P: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, P>,
    hl_node: NodeRef,
    hl_graph: &HLGraph,
    hl_ll_map: AHashMap<NodeRef, NodeRef>,
) -> OutportLocation {
    let hlnode = if let NodeType::Simple(n) = hl_graph.graph.node(hl_node).node_type {
        n
    } else {
        panic!("non-simple-node in hl_graph");
    };

    match hlnode.ty {
        HLOpTy::Error => panic!("HLError on node"),
        HLOpTy::ConstFloat(f) => emit_const_f32(region, f),
        HLOpTy::ConstInt(i) => emit_const_i32(
            region,
            i.try_into().expect("Could not convert isize into i32"),
        ),
        HLOpTy::BinaryOp(bop) => emit_binary_op(region, &hlnode, bop, hl_graph, hl_ll_map),
        HLOpTy::UnaryOp(uop) => emit_unary_op(region, &hlnode, uop, hl_graph, hl_ll_map),
        HLOpTy::Prim(p) => todo!("unimpl"),
        HLOpTy::TyConst(ty_construct) => todo!("impl ty constructor"),
    }
}
