fn main() {
    let ast = match minisdf_ast::parse_file("examples/simple/default.minisdf") {
        Ok(ast) => ast,
        Err(e) => {
            println!("Failed to compiler, last error: {}", e);
            return;
        }
    };

    println!("TREE:\n{:#?}", ast);
}
