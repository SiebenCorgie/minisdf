//! Common diagnosis helper. This is mostly Span of nodes, as well their reporting.

use std::{fmt::Display, str::FromStr};

use backtrace::Backtrace;

use annotate_snippets::{
    display_list::{DisplayList, FormatOptions},
    snippet::{Annotation, AnnotationType, Slice, Snippet, SourceAnnotation},
};
use tinyvec_string::TinyString;

mod reporter;
pub use reporter::ErrorReporter;

pub type TinyErrorString = TinyString<[u8; 32]>;

///Source-Code span information.
#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub struct Span {
    pub file: TinyErrorString,
    pub from: (usize, usize),
    pub to: (usize, usize),
}

impl Span {
    pub fn empty() -> Self {
        Span {
            file: TinyString::default(),
            from: (0, 0),
            to: (0, 0),
        }
    }

    pub fn with_file(mut self, file_name: &str) -> Self {
        self.file = TinyString::from_str(file_name).unwrap();
        self
    }
}

impl<'a> From<&tree_sitter::Node<'a>> for Span {
    fn from(value: &tree_sitter::Node) -> Self {
        Span {
            file: TinyString::default(),
            from: (value.start_position().row, value.start_position().column),
            to: (value.end_position().row, value.end_position().column),
        }
    }
}

#[derive(Clone, Debug)]
pub struct CommonError<E: std::error::Error> {
    pub span: Span,
    pub source: E,
    pub backtrace: Option<Backtrace>,
}

impl<E: std::error::Error> CommonError<E> {
    pub fn new(span: Span, source: E) -> Self {
        CommonError {
            span,
            source,
            backtrace: if std::env::var("MINISDF_BACKTRACE").is_ok() {
                Some(Backtrace::new())
            } else {
                None
            },
        }
    }
}

pub struct ErrorPrintBundle<'a, E: std::error::Error> {
    pub error: &'a CommonError<E>,
    pub src_lines: &'a [String],
}

impl<'a, E: std::error::Error + Default> Display for ErrorPrintBundle<'a, E> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let ErrorPrintBundle { error, src_lines } = self;
        let error_str = error.source.to_string();
        //NOTE: usually an error is only on one line / at one point. However,
        // sometimes it goes over multiple lines. In this case, this makes sure we only
        // attach annotation to the last line, by clamping to the first line + start offset, and last line - start offset
        let snippet = if error.span.from.0 != error.span.to.0 {
            let mut slices = Vec::with_capacity(error.span.to.0 - error.span.from.0);
            for line_number in error.span.from.0..error.span.to.0 {
                let slice_line = &src_lines[line_number];
                let annotations = if line_number == error.span.from.0 {
                    vec![SourceAnnotation {
                        label: &error_str,
                        annotation_type: AnnotationType::Error,
                        range: (0, slice_line.chars().count() - 1),
                    }]
                } else if line_number == error.span.to.0 {
                    vec![SourceAnnotation {
                        label: "end of error region",
                        annotation_type: AnnotationType::Error,
                        range: (0, slice_line.chars().count()),
                    }]
                } else {
                    vec![]
                };

                slices.push(Slice {
                    source: slice_line,
                    line_start: line_number + 1, //+1 since we are using indices, but want to display the line number
                    origin: None,                //TODO carry filename at some point
                    fold: false,
                    annotations,
                })
            }

            Snippet {
                title: Some(Annotation {
                    label: Some("CommonError"),
                    id: None, //TODO might want to turn those into error IDs at some point
                    annotation_type: AnnotationType::Error,
                }),
                footer: vec![],
                slices,
                opt: FormatOptions {
                    color: true,
                    ..Default::default()
                },
            }
        } else {
            //Simple single line reporting
            Snippet {
                title: Some(Annotation {
                    label: None,
                    id: None, //TODO might want to turn those into error IDs at some point
                    annotation_type: AnnotationType::Error,
                }),
                footer: vec![],
                slices: vec![Slice {
                    source: src_lines[error.span.from.0].as_str(),
                    line_start: error.span.from.0 + 1, //+1 since we are using indices, but want to display the line number
                    origin: None,                      //TODO carry filename at some point
                    fold: true,
                    annotations: vec![SourceAnnotation {
                        label: &error_str,
                        annotation_type: AnnotationType::Error,
                        range: (error.span.from.1, error.span.to.1),
                    }],
                }],
                opt: FormatOptions {
                    color: true,
                    ..Default::default()
                },
            }
        };

        let dl = DisplayList::from(snippet);
        let res = dl.fmt(f);
        if let Some(bt) = &error.backtrace {
            write!(f, "\nBacktrace:")?;
            write!(f, "\n{:?}", bt)?;
        } else {
            write!(
                f,
                "\n`MINISDF_BACKTRACE=1` to print the backtrace of the error occurrence"
            )?;
        }
        res
    }
}

impl<E: std::error::Error + Default> Default for CommonError<E> {
    fn default() -> Self {
        CommonError {
            span: Span::empty(),
            source: E::default(),
            backtrace: None,
        }
    }
}
