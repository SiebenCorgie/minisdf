fn main() {
    let ast = minisdf_ast::parse_file("examples/simple/default.minisdf").unwrap();

    println!("TREE:\n{:#?}", ast);
}
