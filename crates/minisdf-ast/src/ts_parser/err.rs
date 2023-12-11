use thiserror::Error;

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
    #[error("Unexpected Token {0}")]
    UnexpectedToken(String),
    #[error("Unknown Type {0}")]
    UnknownType(String),
    #[error("Unknown operation {0}")]
    UnknownOp(String),
    #[error("Unknown primitive type {0}")]
    UnknownPrim(String),
}

impl Default for TSParseError {
    fn default() -> Self {
        TSParseError::Any
    }
}
