//! MiniSDF AST with focus on simplicity

mod ts_parser;
use minisdf_common::Span;
pub use ts_parser::parse_file;

#[derive(Clone, Debug)]
pub enum Ty {
    Float,
    Vec2,
    Vec3,
    Vec4,
    Error,
}

#[derive(Clone, Debug)]
pub enum Literal {
    Int(isize),
    Float(f32),
}

#[derive(Clone, Debug)]
pub struct Ident(pub String);

#[derive(Clone, Debug)]
pub enum Parameter {
    Lit(Literal),
    Ident(Ident),
    TyConstructor { ty: Ty, params: Vec<Parameter> },
    Error,
}

#[derive(Clone, Debug)]
pub enum UnOpTy {
    Translate,
    Repeat,
    Smooth,
    Error,
}

#[derive(Clone, Debug)]
pub struct UnaryOp {
    pub ty: UnOpTy,
    pub parameter: Vec<Parameter>,
    pub subtree: Box<Tree>,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub enum BinOpTy {
    Union,
    Subtraction,
    Intersection,
    Error,
}

#[derive(Clone, Debug)]
pub struct BinaryOp {
    pub ty: BinOpTy,
    pub parameter: Vec<Parameter>,
    pub left: Box<Tree>,
    pub right: Box<Tree>,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub enum PrimTy {
    Box,
    Sphere,
    Torus,
    Plane,
    Error,
}

#[derive(Clone, Debug)]
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

#[derive(Clone, Debug)]
pub struct TypedArg {
    pub ident: Ident,
    pub ty: Ty,
    pub span: Span,
}

///A single field description
#[derive(Clone, Debug)]
pub struct Field {
    pub name: Ident,
    pub args: Vec<TypedArg>,
    pub tree: Tree,
}
