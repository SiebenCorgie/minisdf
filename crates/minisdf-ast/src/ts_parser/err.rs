use minisdf_common::Span;
use thiserror::Error;
use tree_sitter::Node;

use super::report_error;

#[derive(Error, Debug)]
pub enum TSParseError {
    #[error("SomeError")]
    Any,
    #[error("Expected identifier")]
    ExpectedIdent,
    #[error("Expected typed identifier")]
    ExpectedTypedIdent,
    #[error("Invalid identifier")]
    InvalidIdent,
    #[error("Unexpected Token {0}, expected {1}")]
    UnexpectedToken(String, String),
    #[error("Unknown Type {0}")]
    UnknownType(String),
    #[error("Unknown operation {0}")]
    UnknownOp(String),
    #[error("Unknown primitive type {0}")]
    UnknownPrim(String),
}

impl TSParseError {
    pub fn check_token(node: &Node, kind: &str) -> bool {
        if node.kind() != kind {
            report_error(
                TSParseError::UnexpectedToken(node.kind().to_owned(), kind.to_owned()),
                Span::from(node),
            );
            false
        } else {
            true
        }
    }
}

impl Default for TSParseError {
    fn default() -> Self {
        TSParseError::Any
    }
}
