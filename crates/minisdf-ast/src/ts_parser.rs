//! Parses a file via tree-sitter-minisdf and returns the field, if parsed correctly.

use std::{path::Path, sync::Mutex};

use lazy_static::lazy_static;
use minisdf_common::{CommonError, Span};
use tree_sitter::{Node, Parser, TreeCursor};

use crate::{
    ts_parser::{tree::parse_tree, ty::parse_type},
    Field, Ident, Tree, TypedArg,
};

use self::err::TSParseError;
use minisdf_common::ErrorPrintBundle;
mod err;
mod tree;
mod ty;

//defines a global buffer for the string we are parsing
lazy_static! {
    static ref TSSRC: Mutex<Vec<String>> = Mutex::new(Vec::with_capacity(0));
    static ref LASTERR: Mutex<Option<CommonError<TSParseError>>> = Mutex::new(None);
}

///Sets the default file for reported errors.
pub fn set_parse_string(file: &String) {
    //TODO: split lines and push into TSSRC
    let lines = file
        .lines()
        .into_iter()
        .map(|line| line.to_owned())
        .collect();
    *TSSRC.lock().unwrap() = lines;
}

///Reports `error` on `span`
pub fn report_error(error: err::TSParseError, span: Span) {
    let error = CommonError::new(span, error);
    println!(
        "{}",
        ErrorPrintBundle {
            error: &error,
            src_lines: &TSSRC.lock().as_ref().unwrap()
        }
    );
    *LASTERR.lock().unwrap() = Some(error);
}

fn parser() -> Parser {
    let mut parser = Parser::new();
    parser
        .set_language(tree_sitter_minisdf::language())
        .expect("Failed to load treesitter minisdf");
    parser
}

///Tries to parse `file` as an MiniSDF tree. Returns err if any error occured. In that case the
/// parsing should be considered failed.
pub fn parse_file(file: impl AsRef<Path>) -> Result<Vec<Field>, err::TSParseError> {
    let file_string = std::fs::read_to_string(file.as_ref()).expect("Could not read source file!");
    //notify reporter
    set_parse_string(&file_string);

    //recursively parse all nodes
    let mut parser = parser();
    let data = std::fs::read(file).expect("Could not read file to bytes");
    let syn_tree = parser
        .parse(&data, None)
        .expect("Could not parse via tree-sitter!");

    println!("SYNTREE:\n{}", syn_tree.root_node().to_sexp());

    let field = parse_toplevel(&data, syn_tree);
    if let Some(err) = LASTERR.lock().unwrap().take() {
        Err(err.source)
    } else {
        Ok(field)
    }
}

fn parse_ident(data: &[u8], node: &Node) -> Ident {
    if node.kind() != "identifier" {
        report_error(TSParseError::InvalidIdent, Span::from(node));
        return Ident("invalid ident".to_owned());
    }

    let name = node.utf8_text(data).unwrap();
    Ident(name.to_owned())
}

fn parse_typed_args(data: &[u8], arg_list: &Node) -> Vec<TypedArg> {
    assert!(arg_list.kind() == "arg_list");
    let mut args = Vec::new();
    let mut walker = arg_list.walk();
    for child in arg_list.children(&mut walker) {
        if child.kind() == "," {
            continue;
        }
        if child.kind() != "typed_arg" {
            report_error(TSParseError::ExpectedTypedIdent, Span::from(&child));
            continue;
        }

        //first child should be ident, other should be type
        let ident = parse_ident(data, &child.child(0).as_ref().unwrap());
        let ty = parse_type(data, &child.child(2).as_ref().unwrap());
        args.push(TypedArg { ident, ty })
    }
    args
}

fn parse_field_decl(data: &[u8], node: &Node) -> Field {
    assert!(node.kind() == "field_decl");

    let mut walker = node.walk();
    let mut children = node.children(&mut walker);

    assert!(children.next().unwrap().kind() == "field");

    let name_ident = children.next().unwrap();
    let name = match name_ident.utf8_text(data) {
        Err(_e) => {
            report_error(TSParseError::InvalidIdent, Span::from(&name_ident));
            "invalid_ident".to_owned()
        }
        Ok(s) => s.to_owned(),
    };
    assert!(children.next().unwrap().kind() == "(");

    let next = children.next().unwrap();
    let arg_list = match next.kind() {
        "arg_list" => {
            let typed_args = parse_typed_args(data, &next);
            //take of the ")" after the list
            assert!(children.next().unwrap().kind() == ")");
            typed_args
        }
        ")" => Vec::with_capacity(0),
        _ => {
            report_error(
                TSParseError::UnexpectedToken(next.kind().to_owned()),
                Span::from(&next),
            );
            Vec::new()
        }
    };

    assert!(children.next().unwrap().kind() == "{");
    let tree = parse_tree(data, &children.next().unwrap());
    assert!(children.next().unwrap().kind() == "}");

    Field {
        name: Ident(name),
        args: arg_list,
        tree,
    }
}

fn parse_toplevel(data: &[u8], parser: tree_sitter::Tree) -> Vec<Field> {
    let root = parser.root_node();
    assert!(root.kind() == "source_file");
    let mut walker = root.walk();
    let mut fields = Vec::new();
    for child in root.children(&mut walker) {
        match child.kind() {
            "comment" => {}
            "field_decl" => fields.push(parse_field_decl(data, &child)),
            _ => report_error(
                TSParseError::UnexpectedToken(child.kind().to_owned()),
                Span::from(&child),
            ),
        }
    }

    fields
}
