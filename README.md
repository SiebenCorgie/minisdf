# MiniSDF

Proof of concept RVSDG based compiler for a simple SignedDistanceField language.

## Crates
`tree-sitter-minisdf`: The tree-sitter grammar and parser, if you get strange tree-sitter errors, change into that directory and call ´tree-sitter generate´

`minisdf-ast`: AST implementation for MiniSDF. Can either be parsed from a file (using tree-sitter), or generated by a program.

`minisdf-optimizer`: The RVSDG based optimizer / _middle-end_. Takes an AST and builds a RVSDG representation using basic lowlevel-_ish_ operations. 

`minisdf-backend-spirv`: simple SPIR-V backend based on [rspirv](https://crates.io/crates/rspirv).

## Example

The following example defines a field that subtracts smoothed-box from a unit box that repeats in the domain 4³.

The offset of the subtracted box is set by an external `offset` parameter. Which can be animated through the calling 
shader.

```
field myfield(offset: vec3){
    sub(){
        repeat(4.0, 4.0, 4.0){
            box(vec3(1.0, 1.0, 1.0))
        }
    }{
        translate(offset){
            smooth(0.25){
                box(vec3(1.0, 1.0, 2.0))
            }
        }
    }
}
```

## License

Licensed under either of

- Apache License, Version 2.0, ([LICENSE-APACHE](LICENSE-APACHE) or <http://www.apache.org/licenses/LICENSE-2.0>)
- MIT license ([LICENSE-MIT](LICENSE-MIT) or <http://opensource.org/licenses/MIT>)

at your option.

### Contribution

Unless you explicitly state otherwise, any contribution intentionally submitted for inclusion in the work by you, as defined in the Apache-2.0 license, shall be dual licensed as above, without any additional terms or conditions.
