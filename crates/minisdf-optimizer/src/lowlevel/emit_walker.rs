use ahash::AHashMap;
use minisdf_ast::{BinOpTy, PrimTy, UnOpTy};
use minisdf_common::Span;
use rvsdg::{
    builder::RegionBuilder,
    edge::OutportLocation,
    nodes::{NodeType, StructuralNode},
    region::Inport,
    NodeRef,
};

use crate::{edge::OptEdge, highlevel::HLOpTy, HLGraph};

use super::{LLOp, LLOpTy};

#[derive(Hash, Clone, Debug, PartialEq, Eq)]
pub enum LambdaLookupKey {
    BinaryOp { op: BinOpTy, on_at: bool },
    UnaryOp { op: UnOpTy, on_at: bool },
    Prim { prim: PrimTy },
}
