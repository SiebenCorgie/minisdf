//! MiniSDF AST with focus on simplicity

mod ts_parser;
use minisdf_common::Span;
pub use ts_parser::parse_file;

#[derive(Clone, Debug, PartialEq, Eq)]
pub enum Ty {
    Float,
    Vec2,
    Vec3,
    Vec4,
    Int,
    Sdf,
    Error,
}

#[derive(Clone, Debug, PartialEq)]
pub enum Literal {
    Int(isize),
    Float(f32),
}

#[derive(Clone, Debug, PartialEq)]
pub struct Ident(pub String);

#[derive(Clone, Debug, PartialEq)]
pub enum Parameter {
    Lit(Literal),
    Ident(Ident),
    TyConstructor { ty: Ty, params: Vec<Parameter> },
    Error,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub enum UnOpTy {
    Translate,
    Repeat,
    Smooth,
    Error,
}

#[derive(Clone, Debug, PartialEq)]
pub struct UnaryOp {
    pub ty: UnOpTy,
    pub parameter: Vec<Parameter>,
    pub subtree: Box<Tree>,
    pub span: Span,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub enum BinOpTy {
    Union,
    Subtraction,
    Intersection,
    Error,
}

#[derive(Clone, Debug, PartialEq)]
pub struct BinaryOp {
    pub ty: BinOpTy,
    pub parameter: Vec<Parameter>,
    pub left: Box<Tree>,
    pub right: Box<Tree>,
    pub span: Span,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub enum PrimTy {
    Box,
    Sphere,
    Torus,
    Plane,
    Error,
}

#[derive(Clone, Debug, PartialEq)]
pub enum Tree {
    Unary(UnaryOp),
    Binary(BinaryOp),
    Prim {
        span: Span,
        prim: PrimTy,
        params: Vec<Parameter>,
    },
    Error,
}

#[derive(Clone, Debug, PartialEq)]
pub struct TypedArg {
    pub ident: Ident,
    pub ty: Ty,
    pub span: Span,
}

///A single field description
#[derive(Clone, Debug, PartialEq)]
pub struct Field {
    pub name: Ident,
    pub args: Vec<TypedArg>,
    pub tree: Tree,
}
