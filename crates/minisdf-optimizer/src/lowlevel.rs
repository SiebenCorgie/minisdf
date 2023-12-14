use minisdf_common::Span;
use rvsdg::{
    nodes::LangNode,
    region::{Input, Output},
};
use tinyvec::TinyVec;

use crate::highlevel::HLOp;

#[derive(Debug)]
pub enum LLOpTy {
    Error,
    HLOp(HLOp),

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
