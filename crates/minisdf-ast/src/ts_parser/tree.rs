use super::{err::TSParseError, parse_ident, report_error, ty::parse_type};
use crate::{BinOpTy, Literal, Parameter, PrimTy, Tree, UnOpTy};
use minisdf_common::Span;
use tree_sitter::Node;

pub fn parse_unopty(data: &[u8], node: &Node) -> UnOpTy {
    if !TSParseError::check_token(node, "unary_op") {
        return UnOpTy::Error;
    }

    let name = match node.utf8_text(data) {
        Err(_e) => {
            report_error(TSParseError::InvalidIdent, Span::from(node));
            "invalid_ident".to_owned()
        }
        Ok(s) => s.to_owned(),
    };

    match name.as_str() {
        "translate" => UnOpTy::Translate,
        "repeat" => UnOpTy::Repeat,
        "smooth" => UnOpTy::Smooth,
        _ => {
            report_error(TSParseError::UnknownOp(name), Span::from(node));
            UnOpTy::Error
        }
    }
}

pub fn parse_binopty(data: &[u8], node: &Node) -> BinOpTy {
    if TSParseError::check_token(node, "binary_op") {
        return BinOpTy::Error;
    }

    let name = match node.utf8_text(data) {
        Err(_e) => {
            report_error(TSParseError::InvalidIdent, Span::from(node));
            "invalid_ident".to_owned()
        }
        Ok(s) => s.to_owned(),
    };

    match name.as_str() {
        "inter" => BinOpTy::Intersection,
        "sub" => BinOpTy::Subtraction,
        "union" => BinOpTy::Union,
        _ => {
            report_error(TSParseError::UnknownOp(name), Span::from(node));
            BinOpTy::Error
        }
    }
}

pub fn parse_prim_ty(data: &[u8], node: &Node) -> PrimTy {
    if TSParseError::check_token(node, "prim") {
        return PrimTy::Error;
    }

    let name = match node.utf8_text(data) {
        Err(_e) => {
            report_error(TSParseError::InvalidIdent, Span::from(node));
            "invalid_ident".to_owned()
        }
        Ok(s) => s.to_owned(),
    };

    match name.as_str() {
        "box" => PrimTy::Box,
        "sphere" => PrimTy::Sphere,
        "torus" => PrimTy::Torus,
        "plane" => PrimTy::Plane,
        _ => {
            report_error(TSParseError::UnknownPrim(name), Span::from(node));
            PrimTy::Error
        }
    }
}

pub fn parse_lit(data: &[u8], node: &Node) -> Literal {
    match node.kind() {
        "float_literal" => {
            let as_string = node.utf8_text(data).unwrap();
            let float: f32 = as_string.parse().expect("could not parse float!");
            Literal::Float(float)
        }
        "integer_literal" => {
            let as_string = node.utf8_text(data).unwrap();
            let int: isize = as_string.parse().expect("could not parse float!");
            Literal::Int(int)
        }
        _ => {
            report_error(
                TSParseError::UnexpectedToken(
                    node.kind().to_owned(),
                    "float_literal | integer_literal".to_owned(),
                ),
                Span::from(node),
            );
            Literal::Int(0xdeadbeef)
        }
    }
}

pub fn parse_param(data: &[u8], node: &Node) -> Parameter {
    let child = node.child(0).unwrap();
    match child.kind() {
        "literal" => Parameter::Lit(parse_lit(data, &child.child(0).as_ref().unwrap())),
        "identifier" => Parameter::Ident(parse_ident(data, &child)),
        "type_construct" => {
            let ty = parse_type(data, child.child(0).as_ref().unwrap());
            let params = parse_call_params(data, child.child(2).as_ref().unwrap());
            Parameter::TyConstructor { ty, params }
        }
        _ => {
            report_error(
                TSParseError::UnexpectedToken(
                    child.kind().to_owned(),
                    "literal | identifier | type_construct".to_owned(),
                ),
                Span::from(&child),
            );
            Parameter::Error
        }
    }
}

pub fn parse_call_params(data: &[u8], node: &Node) -> Vec<Parameter> {
    let mut params = Vec::new();
    let mut walker = node.walk();
    for child in node.children(&mut walker) {
        match child.kind() {
            "param" => params.push(parse_param(data, &child)),
            "," => {}
            _ => {
                report_error(
                    TSParseError::UnexpectedToken(child.kind().to_owned(), "param | ,".to_owned()),
                    Span::from(&child),
                );
            }
        }
    }
    params
}

pub fn parse_tree(data: &[u8], node: &Node) -> Tree {
    match node.kind() {
        "binary_call" => {
            let op = parse_binopty(data, node.child(0).as_ref().unwrap());
            let mut sub_a_offset = 4;
            let mut sub_b_offset = 7;
            let params = if let "call_params" = node.child(2).as_ref().unwrap().kind() {
                sub_a_offset = 5;
                sub_b_offset = 6;
                parse_call_params(data, node.child(2).as_ref().unwrap())
            } else {
                Vec::with_capacity(0)
            };

            let sub_a = parse_tree(data, node.child(sub_a_offset).as_ref().unwrap());
            let sub_b = parse_tree(data, node.child(sub_b_offset).as_ref().unwrap());

            Tree::Binary(crate::BinaryOp {
                ty: op,
                parameter: params,
                left: Box::new(sub_a),
                right: Box::new(sub_b),
                span: Span::from(node),
            })
        }
        "unary_call" => {
            let op = parse_unopty(data, node.child(0).as_ref().unwrap());
            let mut param_offset = 0;
            let params = if let "call_params" = node.child(2).as_ref().unwrap().kind() {
                param_offset = 1;
                parse_call_params(data, node.child(2).as_ref().unwrap())
            } else {
                Vec::with_capacity(0)
            };
            let sub = parse_tree(data, node.child(4 + param_offset).as_ref().unwrap());

            let _ = TSParseError::check_token(node.child(2 + param_offset).as_ref().unwrap(), ")");
            let _ = TSParseError::check_token(node.child(3 + param_offset).as_ref().unwrap(), "{");
            let _ = TSParseError::check_token(node.child(5 + param_offset).as_ref().unwrap(), "}");

            Tree::Unary(crate::UnaryOp {
                ty: op,
                parameter: params,
                subtree: Box::new(sub),
                span: Span::from(node),
            })
        }
        "prim_call" => {
            let prim = parse_prim_ty(data, node.child(0).as_ref().unwrap());
            let params = if let "call_params" = node.child(2).as_ref().unwrap().kind() {
                parse_call_params(data, node.child(2).as_ref().unwrap())
            } else {
                Vec::with_capacity(0)
            };

            let opening = node.child(1).unwrap();
            let _ = TSParseError::check_token(&opening, "(");

            let closing = node.child(3).unwrap();
            let _ = TSParseError::check_token(&closing, ")");

            Tree::Prim {
                prim,
                params,
                span: Span::from(node),
            }
        }
        _ => {
            report_error(
                TSParseError::UnexpectedToken(
                    node.kind().to_owned(),
                    "prim_call | unary_call | binary_call".to_owned(),
                ),
                Span::from(node),
            );
            Tree::Error
        }
    }
}
