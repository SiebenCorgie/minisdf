//! MiniSDF AST with focus on simplicity

mod ts_parser;
use minisdf_common::Span;
pub use ts_parser::parse_file;
pub use ts_parser::TSParseError;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub enum Ty {
    Float,
    Vec2,
    Vec3,
    Vec4,
    Int,
    Sdf,
    Error,
}

impl Ty {
    pub fn is_vec(&self) -> bool {
        match self {
            Ty::Vec2 | Ty::Vec3 | Ty::Vec4 => true,
            _ => false,
        }
    }

    ///Returns the sub element count that can be accessed. is 1 for all base types, 2 for Vec2, 3 for Vec3 etc.
    pub fn element_count(&self) -> usize {
        match self {
            Ty::Vec2 => 2,
            Ty::Vec3 => 3,
            Ty::Vec4 => 4,
            _ => 1,
        }
    }
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
