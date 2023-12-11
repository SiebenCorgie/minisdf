module.exports = grammar({
  name: 'minisdf',

  word: $ => $.identifier,


  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => repeat(choice(
      $.comment,
      $.field_decl
    )),

    field_decl: $ => seq(
      "field",
      $.identifier,
      "(",
      optional($.arg_list),
      ")",
      "{",
      $._field_tree,
      "}"
    ),


    arg_list: $ => seq(
      repeat(seq(
        $.typed_arg,
        ","
      )),
      $.typed_arg,
    ),

    typed_arg: $ => seq(
      $.identifier,
      ":",
      $.type
    ),

    _field_tree: $ => choice(
      $.unary_call,
      $.binary_call,
      $.prim_call,
    ),


    unary_call: $ => seq(
      $.unary_op,
      "(",
      optional($.call_params),
      ")",
      "{",
      $._field_tree,
      "}"
    ),

    binary_call: $ => seq(
      $.binary_op,
      "(",
      optional($.call_params),
      ")",
      "{",
      $._field_tree,
      "}",
      "{",
      $._field_tree,
      "}",
    ),

    prim_call: $ => seq(
      $.prim,
      "(",
      optional($.call_params),
      ")"
    ),

    call_params: $ => seq(
      repeat(seq(
        $.param,
        ","
      )),
      $.param
    ),

    param: $ => choice(
      $.literal,
      $.identifier,
      $.type_constructor
    ),

    type_constructor: $ => seq(
      $.type,
      "(",
      $.call_params,
      ")"
    ),

    //all primitives the language knows
    prim: $ => choice(
      "sphere",
      "box",
      "torus",
      "plane",
    ),

    unary_op: $ => choice(
      "translate",
      "repeat",
      "smooth",
    ),

    ///All operations on two sub trees
    binary_op: $ => choice(
      "union",
      "sub",
      "inter",
    ),

    literal: $ => choice(
      $.integer_literal,
      $.float_literal
    ),
    integer_literal: $ => $.digit,

    float_literal: $ => seq(
      optional("-"),
      $.digit,
      '.',
      optional($.digit)
    ),

    type: $ => choice(
      "float",
      "vec2",
      "vec3",
      "vec4",
    ),

    digit: $ => /[0-9][0-9_]*/,
    identifier: $ => /[a-z_]+/,
    comment: $ => token(seq('//')),
  }
});
