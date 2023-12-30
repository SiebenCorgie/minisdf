use minisdf_backend_spirv::{rspirv::binary::Disassemble, SpirvBackend};
use minisdf_optimizer::rvsdg::nodes::NodeType;
use rvsdg_viewer::View;

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
        let mut ll_graph = hltree.into_ll_graph();
        /*
                for node in ll_graph.graph.walk_reachable() {
                    match &ll_graph.graph.node(node).node_type {
                        NodeType::Simple(s) => println!("Simple: {} : {}", s.name(), node),
                        NodeType::Lambda(_) => println!("Lambda: {}", node),
                        NodeType::Omega(_) => println!("Omega: {}", node),
                        NodeType::Apply(_) => println!("Apply: {}", node),
                        _ => println!("Wrong node type!"),
                    }
                }
        */
        rvsdg_viewer::into_svg(&ll_graph.graph, &format!("ll_{}.svg", name));

        ll_graph.verify().unwrap();

        ll_graph.inline();
        rvsdg_viewer::into_svg(&ll_graph.graph, &format!("ll_{}_post_inline.svg", name));

        ll_graph.cne();
        rvsdg_viewer::into_svg(&ll_graph.graph, &format!("ll_{}_post_cne.svg", name));

        ll_graph.type_resolve().unwrap();

        let spvmod = ll_graph.lower().unwrap();
        println!("{}", spvmod.disassemble());
    }
}
