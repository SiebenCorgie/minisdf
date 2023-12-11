//! MiniSDF AST with focus on simplicity

mod ts_parser;
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
    ty: UnOpTy,
    parameter: Vec<Parameter>,
    subtree: Box<Tree>,
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
    ty: BinOpTy,
    parameter: Vec<Parameter>,
    left: Box<Tree>,
    right: Box<Tree>,
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
        prim: PrimTy,
        params: Vec<Parameter>,
    },
    Error,
}

#[derive(Clone, Debug)]
pub struct TypedArg {
    ident: Ident,
    ty: Ty,
}

///A single field description
#[derive(Clone, Debug)]
pub struct Field {
    name: Ident,
    args: Vec<TypedArg>,
    tree: Tree,
}
