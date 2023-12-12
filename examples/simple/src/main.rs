const SRCFILE: &'static str = "examples/simple/default.minisdf";
fn main() {
    let fields = match minisdf_ast::parse_file(SRCFILE) {
        Ok(ast) => ast,
        Err(e) => {
            println!("Failed to compiler, last error: {}", e);
            return;
        }
    };

    for ast in fields {
        println!("Parsing ast: \n{:#?}", ast);
        let name = ast.name.0.clone();
        let hltree = minisdf_optimizer::hlgraph_from_ast(ast, SRCFILE).unwrap();
        rvsdg_viewer::into_svg(&hltree.graph, &format!("{}.svg", name));
    }
}
