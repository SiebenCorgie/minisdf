//! Highlevel representation of an SDF in an RVSDG, akin to the AST.
//!

use std::{path::Path, sync::Mutex};

use crate::edge::OptEdge;
use ahash::AHashMap;
use lazy_static::lazy_static;
use minisdf_ast::{
    BinOpTy, BinaryOp, Field, Literal, Parameter, PrimTy, Tree, Ty, UnOpTy, UnaryOp,
};
use minisdf_common::{CommonError, ErrorPrintBundle, Span};
use rvsdg::{
    attrib::AttribStore,
    builder::RegionBuilder,
    edge::{InputType, OutportLocation, OutputType},
    nodes::{LangNode, Node, NodeType, OmegaNode},
    region::{Input, Output},
    NodeRef, Rvsdg,
};
use rvsdg_viewer::View;
use thiserror::Error;
use tinyvec::TinyVec;

//defines a global buffer for the string we are parsing
lazy_static! {
    static ref HLSRC: Mutex<Vec<String>> = Mutex::new(Vec::with_capacity(0));
    static ref HL_LASTERR: Mutex<Option<CommonError<HLError>>> = Mutex::new(None);
}

///Sets the default file for reported errors.
pub fn set_parse_string(file: &String) {
    //TODO: split lines and push into TSSRC
    let lines = file
        .lines()
        .into_iter()
        .map(|line| line.to_owned())
        .collect();
    *HLSRC.lock().unwrap() = lines;
}

///Reports `error` on `span`
pub fn report_error(error: HLError, span: Span) {
    let error = CommonError::new(span, error);
    println!(
        "{}",
        ErrorPrintBundle {
            error: &error,
            src_lines: &HLSRC.lock().as_ref().unwrap()
        }
    );
    *HL_LASTERR.lock().unwrap() = Some(error);
}

#[derive(Debug, Error)]
pub enum HLError {
    #[error("Any HLError")]
    Any,
    #[error("Ast contained error node")]
    AstError,
    #[error("Highlevel graph contained error node")]
    HLError,
    #[error("Identifier {0} is not defined!")]
    UndefinedIdent(String),
    #[error("Expected variable of type {expect:?}, found {was:?}")]
    TypeExpected { expect: Ty, was: Option<Ty> },
    #[error("Expected input {0} to be subtree")]
    SubtreeExpected(usize),
    #[error("Expected input {0} to be connected")]
    InputConnectionExpected(usize),
    #[error("Expected input {0} to be existent")]
    InputExpected(usize),
    #[error("Too many inputs, expected {0} inputs, got {1}")]
    TooManyInputs(usize, usize),
}

impl Default for HLError {
    fn default() -> Self {
        HLError::Any
    }
}

#[derive(Debug)]
pub enum HLOpTy {
    ConstFloat(f32),
    ConstInt(isize),
    ///Constructs `{0}` from its inputs
    TyConst(Ty),
    BinaryOp(BinOpTy),
    UnaryOp(UnOpTy),
    Prim(PrimTy),

    Error,
}

#[derive(Debug)]
pub struct HLOp {
    pub ty: HLOpTy,
    //The source span this op originates from.
    pub span: Span,
    pub inputs: TinyVec<[Input; 3]>,
    pub outputs: TinyVec<[Output; 3]>,
}

impl LangNode for HLOp {
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

impl View for HLOp {
    fn color(&self) -> rvsdg_viewer::macroquad::color::Color {
        rvsdg_viewer::macroquad::color::Color::from_rgba(200, 100, 50, 255)
    }
    fn name(&self) -> &str {
        match &self.ty {
            HLOpTy::BinaryOp(bop) => match bop {
                BinOpTy::Error => "Error Binary Op",
                BinOpTy::Intersection => "Intersection",
                BinOpTy::Subtraction => "Subtraction",
                BinOpTy::Union => "Union",
            },
            HLOpTy::UnaryOp(uop) => match uop {
                UnOpTy::Error => "Error Unary Op",
                UnOpTy::Repeat => "Repeat",
                UnOpTy::Smooth => "Smooth",
                UnOpTy::Translate => "Translate",
            },
            HLOpTy::ConstFloat(_f) => "ImmFloat",
            HLOpTy::ConstInt(_i) => "ImmInt",
            HLOpTy::Error => "Error HlOp",
            HLOpTy::Prim(p) => match p {
                PrimTy::Box => "Box",
                PrimTy::Error => "Error Primitive",
                PrimTy::Plane => "Plane",
                PrimTy::Sphere => "Sphere",
                PrimTy::Torus => "Torus",
            },
            HLOpTy::TyConst(ty) => match ty {
                Ty::Error => "Error Type",
                Ty::Float => "create float",
                Ty::Vec2 => "create vec2",
                Ty::Vec3 => "create vec3",
                Ty::Vec4 => "create vec4",
            },
        }
    }
    fn stroke(&self) -> rvsdg_viewer::Stroke {
        rvsdg_viewer::Stroke::Line
    }
}

impl HLOp {
    pub fn new(ty: HLOpTy, span: Span) -> Self {
        HLOp {
            ty,
            span,
            inputs: TinyVec::default(),
            outputs: TinyVec::default(),
        }
    }

    pub fn add_input(&mut self) -> usize {
        self.inputs.push(Input::default());
        self.inputs.len() - 1
    }

    pub fn add_output(&mut self) -> usize {
        self.outputs.push(Output::default());
        self.outputs.len() - 1
    }
}

pub enum Identified {
    Node {
        def_span: Span,
        node: NodeRef,
    },
    Arg {
        def_span: Span,
        port: OutportLocation,
    },
}

pub struct HLGraph {
    pub graph: Rvsdg<HLOp, OptEdge>,
    //Annotates all known types
    pub type_table: AttribStore<Ty>,
    //stores all known identifiers
    pub identifier_table: AHashMap<String, Identified>,
}

///Tries to parse the Highlevel graph from the
pub fn hlgraph_from_ast(ast: Field, src_file: impl AsRef<Path>) -> Result<HLGraph, HLError> {
    let src_file = std::fs::read_to_string(src_file.as_ref()).unwrap();
    set_parse_string(&src_file);

    //First thing is, to collect all arguments as typed imports into the toplevel module
    let mut graph = Rvsdg::new();
    let mut type_table = AttribStore::new();
    let mut identifier_table = AHashMap::default();

    //collect attributes
    for attrib in ast.args {
        graph.on_omega_node(|omega| {
            let import = omega.import();
            //register type and node
            type_table.push_attrib(import.clone(), attrib.ty);
            identifier_table.insert(
                attrib.ident.0.clone(),
                Identified::Arg {
                    def_span: attrib.span,
                    port: import,
                },
            );
        })
    }
    //with all attribs hooked up, we can now start transforming the ast into a DAG
    let (field_def, field_export) = graph.on_omega_node(|omega| {
        let export_src = omega
            .on_region(|reg| tree_from_ast(ast.tree, reg, &mut type_table, &mut identifier_table));
        let export_dst = omega.export();
        (export_src, export_dst)
    });

    //Export our definition
    graph
        .connect(field_def, field_export, OptEdge::Value)
        .unwrap();

    Ok(HLGraph {
        graph,
        type_table,
        identifier_table,
    })
}

//transforms a ASTNode to an RVSDGNode, returns the output port of the ASTNode
fn tree_from_ast(
    tree: Tree,
    region: &mut RegionBuilder<HLOp, OptEdge, OmegaNode>,
    type_table: &mut AttribStore<Ty>,
    identifier_table: &mut AHashMap<String, Identified>,
) -> OutportLocation {
    //For each node, we inspect the parameters presented in the AST, as well as the parameters needed
    // as defined by the represented HLOp.
    match tree {
        Tree::Error => {
            report_error(HLError::AstError, Span::empty());
            let node = region.insert_node(HLOp::new(HLOpTy::Error, Span::empty()));
            node.as_outport_location(OutputType::Output(node_push_output(
                region.ctx_mut().node_mut(node),
            )))
        }
        Tree::Binary(BinaryOp {
            ty,
            parameter,
            left,
            right,
            span,
        }) => {
            if let BinOpTy::Error = ty {
                report_error(HLError::AstError, span.clone());
            }
            //setup the unary node, recurse bot children and setup connections
            let left = tree_from_ast(*left, region, type_table, identifier_table);
            let right = tree_from_ast(*right, region, type_table, identifier_table);
            let node = region.insert_node(HLOp::new(HLOpTy::BinaryOp(ty), span));
            //resolve parameters, if one is not found, insert error node instead and call error.
            let parameter: Vec<_> = parameter
                .into_iter()
                .map(|p| param_from_ast(p, region, type_table, identifier_table))
                .collect();
            for param in parameter {
                let into_p_idx = node_push_input(region.ctx_mut().node_mut(node));
                region
                    .ctx_mut()
                    .connect(
                        param,
                        node.as_inport_location(InputType::Input(into_p_idx)),
                        OptEdge::Value,
                    )
                    .unwrap();
            }
            //after parameters, push left and right
            let left_idx = node_push_input(region.ctx_mut().node_mut(node));
            let right_idx = node_push_input(region.ctx_mut().node_mut(node));
            region
                .ctx_mut()
                .connect(
                    left,
                    node.as_inport_location(InputType::Input(left_idx)),
                    OptEdge::Value,
                )
                .unwrap();
            region
                .ctx_mut()
                .connect(
                    right,
                    node.as_inport_location(InputType::Input(right_idx)),
                    OptEdge::Value,
                )
                .unwrap();

            node.as_outport_location(OutputType::Output(node_push_output(
                region.ctx_mut().node_mut(node),
            )))
        }
        Tree::Unary(UnaryOp {
            ty,
            parameter,
            subtree,
            span,
        }) => {
            if let UnOpTy::Error = ty {
                report_error(HLError::AstError, span.clone());
            }
            let inner = tree_from_ast(*subtree, region, type_table, identifier_table);
            let node = region.insert_node(HLOp::new(HLOpTy::UnaryOp(ty), span));

            //resolve parameters, if one is not found, insert error node instead and call error.
            let parameter: Vec<_> = parameter
                .into_iter()
                .map(|p| param_from_ast(p, region, type_table, identifier_table))
                .collect();
            for param in parameter {
                let into_p_idx = node_push_input(region.ctx_mut().node_mut(node));
                region
                    .ctx_mut()
                    .connect(
                        param,
                        node.as_inport_location(InputType::Input(into_p_idx)),
                        OptEdge::Value,
                    )
                    .unwrap();
            }
            //after parameters, push left and right
            let inner_idx = node_push_input(region.ctx_mut().node_mut(node));
            region
                .ctx_mut()
                .connect(
                    inner,
                    node.as_inport_location(InputType::Input(inner_idx)),
                    OptEdge::Value,
                )
                .unwrap();

            node.as_outport_location(OutputType::Output(node_push_output(
                region.ctx_mut().node_mut(node),
            )))
        }
        Tree::Prim { prim, params, span } => {
            if let PrimTy::Error = prim {
                report_error(HLError::AstError, span.clone());
            }
            //just resolve the parameters then setup the prim node.
            let node = region.insert_node(HLOp::new(HLOpTy::Prim(prim), span));

            //resolve parameters, if one is not found, insert error node instead and call error.
            let parameter: Vec<_> = params
                .into_iter()
                .map(|p| param_from_ast(p, region, type_table, identifier_table))
                .collect();
            for param in parameter {
                let into_p_idx = node_push_input(region.ctx_mut().node_mut(node));
                region
                    .ctx_mut()
                    .connect(
                        param,
                        node.as_inport_location(InputType::Input(into_p_idx)),
                        OptEdge::Value,
                    )
                    .unwrap();
            }

            node.as_outport_location(OutputType::Output(node_push_output(
                region.ctx_mut().node_mut(node),
            )))
        }
    }
}

///Creates the parameter's output (typed, if possible), or an error node.
fn param_from_ast(
    param: Parameter,
    region: &mut RegionBuilder<HLOp, OptEdge, OmegaNode>,
    type_table: &mut AttribStore<Ty>,
    identifier_table: &mut AHashMap<String, Identified>,
) -> OutportLocation {
    match param {
        Parameter::Error => {
            report_error(HLError::AstError, Span::empty());
            let node = region.insert_node(HLOp::new(HLOpTy::Error, Span::empty()));
            node.as_outport_location(OutputType::Output(0))
        }
        Parameter::Ident(ident) => {
            if let Some(port) = identifier_table.get(&ident.0) {
                match port {
                    Identified::Arg { def_span, port } => port.clone(),
                    //NOTE: We assume that all nodes have a single output atm.
                    Identified::Node { def_span, node } => {
                        node.as_outport_location(OutputType::Output(0))
                    }
                }
            } else {
                report_error(HLError::UndefinedIdent(ident.0), Span::empty());
                let errornode = region.insert_node(HLOp::new(HLOpTy::Error, Span::empty()));
                errornode.as_outport_location(OutputType::Output(node_push_output(
                    region.ctx_mut().node_mut(errornode),
                )))
            }
        }
        Parameter::Lit(literal) => match literal {
            Literal::Float(f) => {
                let node = region.insert_node(HLOp::new(HLOpTy::ConstFloat(f), Span::empty()));
                node.as_outport_location(OutputType::Output(node_push_output(
                    region.ctx_mut().node_mut(node),
                )))
            }
            Literal::Int(i) => {
                let node = region.insert_node(HLOp::new(HLOpTy::ConstInt(i), Span::empty()));
                node.as_outport_location(OutputType::Output(node_push_output(
                    region.ctx_mut().node_mut(node),
                )))
            }
        },
        Parameter::TyConstructor { ty, params } => {
            let params: Vec<_> = params
                .into_iter()
                .map(|p| param_from_ast(p, region, type_table, identifier_table))
                .collect();
            let constructor_node =
                region.insert_node(HLOp::new(HLOpTy::TyConst(ty), Span::empty()));
            for param in params {
                let into_p_idx = node_push_input(region.ctx_mut().node_mut(constructor_node));
                region
                    .ctx_mut()
                    .connect(
                        param,
                        constructor_node.as_inport_location(InputType::Input(into_p_idx)),
                        OptEdge::Value,
                    )
                    .unwrap();
            }

            constructor_node.as_outport_location(OutputType::Output(node_push_output(
                region.ctx_mut().node_mut(constructor_node),
            )))
        }
    }
}

fn node_push_input(node: &mut Node<HLOp>) -> usize {
    if let NodeType::Simple(n) = &mut node.node_type {
        n.add_input()
    } else {
        panic!("Not HLOp")
    }
}
fn node_push_output(node: &mut Node<HLOp>) -> usize {
    if let NodeType::Simple(n) = &mut node.node_type {
        n.add_output()
    } else {
        panic!("Not HLOp")
    }
}
