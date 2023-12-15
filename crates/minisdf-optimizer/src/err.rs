use std::sync::Mutex;

use crate::highlevel::HLOpTy;
use lazy_static::lazy_static;
use minisdf_ast::Ty;
use minisdf_common::{CommonError, ErrorPrintBundle, Span};
use rvsdg::attrib::AttribLocation;
use thiserror::Error;

//defines a global buffer for the string we are parsing
lazy_static! {
    static ref OPTSRC: Mutex<Vec<String>> = Mutex::new(Vec::with_capacity(0));
    static ref OPT_LASTERR: Mutex<Option<CommonError<OptError>>> = Mutex::new(None);
}

///Sets the default file for reported errors.
pub fn set_parse_string(file: &String) {
    //TODO: split lines and push into TSSRC
    let lines = file
        .lines()
        .into_iter()
        .map(|line| line.to_owned())
        .collect();
    *OPTSRC.lock().unwrap() = lines;
}

///Reports `error` on `span`
pub fn report_error(error: OptError, span: Span) {
    let error = CommonError::new(span, error);
    println!(
        "{}",
        ErrorPrintBundle {
            error: &error,
            src_lines: &OPTSRC.lock().as_ref().unwrap()
        }
    );
    *OPT_LASTERR.lock().unwrap() = Some(error);
}

#[derive(Debug, Error)]
pub enum OptError {
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
    #[error("Expected HLOp {expect:?} got {was:?}")]
    HlOpExpect { expect: HLOpTy, was: HLOpTy },
    #[error("No type information for node {0:?}")]
    NoTypeInfo(AttribLocation),
}

impl Default for OptError {
    fn default() -> Self {
        OptError::Any
    }
}
