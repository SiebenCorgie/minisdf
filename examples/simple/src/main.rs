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
        let name = ast.name.0.clone();
        let hltree = minisdf_optimizer::hlgraph_from_ast(ast, SRCFILE).unwrap();
        rvsdg_viewer::into_svg(&hltree.graph, &format!("hl_{}.svg", name));
        if !hltree.type_check() {
            println!("Type check failed 😭");
            return;
        }
        let ll_graph = hltree.into_ll_graph();
        rvsdg_viewer::into_svg(&ll_graph.graph, &format!("ll_{}.svg", name));
    }
}
