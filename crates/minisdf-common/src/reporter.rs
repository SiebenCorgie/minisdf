use std::{error::Error, str::FromStr};

use ahash::AHashMap;
use tinyvec::TinyVec;
use tinyvec_string::TinyString;

use crate::{CommonError, ErrorPrintBundle, Span, TinyErrorString};

///Helper utility that collects [CommonError](crate::CommonError)s, and reports them when asked.
pub struct ErrorReporter<E: Error + Default> {
    src_file: TinyErrorString,
    errors: TinyVec<[CommonError<E>; 10]>,
    ///Map of cached files we already _know_.
    cached_files: AHashMap<String, Vec<String>>,
}

impl<E: Error + Default> ErrorReporter<E> {
    pub fn new() -> Self {
        ErrorReporter {
            src_file: TinyString::default(),
            errors: TinyVec::default(),
            cached_files: AHashMap::default(),
        }
    }

    pub fn set_default_file(&mut self, file_path: &str) {
        self.src_file = TinyString::from_str(file_path).unwrap();
    }

    pub fn has_errors(&self) -> bool {
        self.errors.len() > 0
    }

    pub fn push_error(&mut self, mut error: CommonError<E>) {
        //Overwrite file, if none was set
        if error.span.file.is_empty() {
            error.span.file = self.src_file.clone();
        }
        self.errors.push(error);
    }

    ///Loads the sub slice for the span. Returns an error string, if the file can not be read.
    pub fn load_span_line<'a>(&'a mut self, span: &Span) -> &'a [String] {
        if !self.cached_files.contains_key(span.file.as_str()) {
            //try to load the file, if not possible, ignore
            match std::fs::read_to_string(span.file.as_str()) {
                Ok(file) => {
                    let _ = self.cached_files.insert(
                        span.file.as_str().to_owned(),
                        file.lines().map(|line| line.to_owned()).collect(),
                    );
                }
                Err(e) => {
                    println!("failed to read file {} : {}", span.file.as_str(), e);
                    let _ = self.cached_files.insert(
                        span.file.as_str().to_owned(),
                        vec![format!("Could not read file: {}", span.file.as_str())],
                    );
                }
            }
        }

        if let Some(file_content) = self.cached_files.get(span.file.as_str()) {
            //try to get the lines range
            file_content
        } else {
            &[]
        }
    }

    ///Prints all errors to stdout that occurred till now. Also returns them as an collection
    pub fn report_all(&mut self) -> TinyVec<[CommonError<E>; 10]> {
        let mut errors: TinyVec<[CommonError<E>; 10]> = TinyVec::default();
        std::mem::swap(&mut errors, &mut self.errors);
        println!("{} Errors:", errors.len());
        for error in &errors {
            let span_lines = self.load_span_line(&error.span);
            if span_lines.is_empty() {
                //fall back to just printing E
                println!(
                    "Error {}:{} .. {}:{}: {}",
                    error.span.from.0,
                    error.span.from.1,
                    error.span.to.0,
                    error.span.to.1,
                    error.source,
                );
                if let Some(bt) = &error.backtrace {
                    println!("Backtrace:\n{:?}", bt);
                }
            } else {
                //otherwise use the pretty printer
                let bundle = ErrorPrintBundle {
                    error: &error,
                    src_lines: span_lines,
                };
                println!("{}", bundle);
            }
        }
        errors
    }
}
