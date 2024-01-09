use std::path::Path;

use minisdf_ast::{Field, TSParseError};
use minisdf_backend_spirv::{rspirv::binary::Assemble, LoweringError, SpirvBackend};
use minisdf_optimizer::{rvsdg::err::LegalizationError, OptError};
use thiserror::Error;

#[derive(Error, Debug)]
pub enum CompileError {
    #[error("Failed to parse file into AST(s): {0}")]
    AstParsingFailed(#[from] TSParseError),
    #[error("High level type check failed")]
    HLTypeCheckFailed,
    #[error("Optimizer error: {0}")]
    OptErr(#[from] OptError),
    #[error("Failed to lower LLGraph to SPIR-V: {0}")]
    LoweringErr(#[from] LoweringError),
    #[error("Failed to legalize RVSDG: {0}")]
    LegalizeErr(#[from] LegalizationError),
}

///Compiles fields in `file`. If successful, returns all SPIR-V modules and their field names.
pub fn compile_file(file: impl AsRef<Path>) -> Result<Vec<(String, Vec<u32>)>, CompileError> {
    let p = file.as_ref();

    let fields = minisdf_ast::parse_file(p)?;

    let mut asts = Vec::new();
    for ast in fields {
        let name = ast.name.0.clone();
        let spv = compile_ast(ast, file.as_ref())?;

        asts.push((name, spv));
    }

    Ok(asts)
}

///Compiles the `ast` based on `file` into a SPIR-V buffer
pub fn compile_ast(ast: Field, file: impl AsRef<Path>) -> Result<Vec<u32>, CompileError> {
    let hltree = minisdf_optimizer::hlgraph_from_ast(ast, file).unwrap();

    //rvsdg_viewer::into_svg(&hltree.graph, &format!("hl_{}.svg", name));

    if !hltree.type_check() {
        println!("Type check failed 😭");
        return Err(CompileError::HLTypeCheckFailed);
    }

    hltree.graph.is_legal_structural()?;
    let mut ll_graph = hltree.into_ll_graph();

    //rvsdg_viewer::into_svg(&ll_graph.graph, &format!("ll_{}.svg", name));

    ll_graph.verify()?;
    ll_graph.inline();
    //rvsdg_viewer::into_svg(&ll_graph.graph, &format!("ll_{}_post_inline.svg", name));
    ll_graph.cne();
    //rvsdg_viewer::into_svg(&ll_graph.graph, &format!("ll_{}_post_cne.svg", name));
    ll_graph.type_resolve()?;
    ll_graph.graph.is_legal_structural()?;

    let spvmod = ll_graph.lower()?;
    let dta = spvmod.assemble();
    Ok(dta)
}
