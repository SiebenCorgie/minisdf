#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 82
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 48
#define ALIAS_COUNT 0
#define TOKEN_COUNT 27
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 10
#define PRODUCTION_ID_COUNT 1

enum {
  sym_identifier = 1,
  anon_sym_field = 2,
  anon_sym_LPAREN = 3,
  anon_sym_RPAREN = 4,
  anon_sym_LBRACE = 5,
  anon_sym_RBRACE = 6,
  anon_sym_COMMA = 7,
  anon_sym_COLON = 8,
  anon_sym_sphere = 9,
  anon_sym_box = 10,
  anon_sym_torus = 11,
  anon_sym_plane = 12,
  anon_sym_translate = 13,
  anon_sym_repeat = 14,
  anon_sym_smooth = 15,
  anon_sym_union = 16,
  anon_sym_sub = 17,
  anon_sym_inter = 18,
  anon_sym_DASH = 19,
  anon_sym_DOT = 20,
  anon_sym_float = 21,
  anon_sym_vec2 = 22,
  anon_sym_vec3 = 23,
  anon_sym_vec4 = 24,
  sym_digit = 25,
  sym_comment = 26,
  sym_source_file = 27,
  sym_field_decl = 28,
  sym_arg_list = 29,
  sym_typed_arg = 30,
  sym__field_tree = 31,
  sym_unary_call = 32,
  sym_binary_call = 33,
  sym_prim_call = 34,
  sym_call_params = 35,
  sym_param = 36,
  sym_type_constructor = 37,
  sym_prim = 38,
  sym_unary_op = 39,
  sym_binary_op = 40,
  sym_literal = 41,
  sym_integer_literal = 42,
  sym_float_literal = 43,
  sym_type = 44,
  aux_sym_source_file_repeat1 = 45,
  aux_sym_arg_list_repeat1 = 46,
  aux_sym_call_params_repeat1 = 47,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_field] = "field",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_COMMA] = ",",
  [anon_sym_COLON] = ":",
  [anon_sym_sphere] = "sphere",
  [anon_sym_box] = "box",
  [anon_sym_torus] = "torus",
  [anon_sym_plane] = "plane",
  [anon_sym_translate] = "translate",
  [anon_sym_repeat] = "repeat",
  [anon_sym_smooth] = "smooth",
  [anon_sym_union] = "union",
  [anon_sym_sub] = "sub",
  [anon_sym_inter] = "inter",
  [anon_sym_DASH] = "-",
  [anon_sym_DOT] = ".",
  [anon_sym_float] = "float",
  [anon_sym_vec2] = "vec2",
  [anon_sym_vec3] = "vec3",
  [anon_sym_vec4] = "vec4",
  [sym_digit] = "digit",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym_field_decl] = "field_decl",
  [sym_arg_list] = "arg_list",
  [sym_typed_arg] = "typed_arg",
  [sym__field_tree] = "_field_tree",
  [sym_unary_call] = "unary_call",
  [sym_binary_call] = "binary_call",
  [sym_prim_call] = "prim_call",
  [sym_call_params] = "call_params",
  [sym_param] = "param",
  [sym_type_constructor] = "type_constructor",
  [sym_prim] = "prim",
  [sym_unary_op] = "unary_op",
  [sym_binary_op] = "binary_op",
  [sym_literal] = "literal",
  [sym_integer_literal] = "integer_literal",
  [sym_float_literal] = "float_literal",
  [sym_type] = "type",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_arg_list_repeat1] = "arg_list_repeat1",
  [aux_sym_call_params_repeat1] = "call_params_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_field] = anon_sym_field,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_sphere] = anon_sym_sphere,
  [anon_sym_box] = anon_sym_box,
  [anon_sym_torus] = anon_sym_torus,
  [anon_sym_plane] = anon_sym_plane,
  [anon_sym_translate] = anon_sym_translate,
  [anon_sym_repeat] = anon_sym_repeat,
  [anon_sym_smooth] = anon_sym_smooth,
  [anon_sym_union] = anon_sym_union,
  [anon_sym_sub] = anon_sym_sub,
  [anon_sym_inter] = anon_sym_inter,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_float] = anon_sym_float,
  [anon_sym_vec2] = anon_sym_vec2,
  [anon_sym_vec3] = anon_sym_vec3,
  [anon_sym_vec4] = anon_sym_vec4,
  [sym_digit] = sym_digit,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym_field_decl] = sym_field_decl,
  [sym_arg_list] = sym_arg_list,
  [sym_typed_arg] = sym_typed_arg,
  [sym__field_tree] = sym__field_tree,
  [sym_unary_call] = sym_unary_call,
  [sym_binary_call] = sym_binary_call,
  [sym_prim_call] = sym_prim_call,
  [sym_call_params] = sym_call_params,
  [sym_param] = sym_param,
  [sym_type_constructor] = sym_type_constructor,
  [sym_prim] = sym_prim,
  [sym_unary_op] = sym_unary_op,
  [sym_binary_op] = sym_binary_op,
  [sym_literal] = sym_literal,
  [sym_integer_literal] = sym_integer_literal,
  [sym_float_literal] = sym_float_literal,
  [sym_type] = sym_type,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_arg_list_repeat1] = aux_sym_arg_list_repeat1,
  [aux_sym_call_params_repeat1] = aux_sym_call_params_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_field] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sphere] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_box] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_torus] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_plane] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_translate] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_repeat] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_smooth] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_union] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sub] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_inter] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_float] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_vec2] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_vec3] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_vec4] = {
    .visible = true,
    .named = false,
  },
  [sym_digit] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_field_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_arg_list] = {
    .visible = true,
    .named = true,
  },
  [sym_typed_arg] = {
    .visible = true,
    .named = true,
  },
  [sym__field_tree] = {
    .visible = false,
    .named = true,
  },
  [sym_unary_call] = {
    .visible = true,
    .named = true,
  },
  [sym_binary_call] = {
    .visible = true,
    .named = true,
  },
  [sym_prim_call] = {
    .visible = true,
    .named = true,
  },
  [sym_call_params] = {
    .visible = true,
    .named = true,
  },
  [sym_param] = {
    .visible = true,
    .named = true,
  },
  [sym_type_constructor] = {
    .visible = true,
    .named = true,
  },
  [sym_prim] = {
    .visible = true,
    .named = true,
  },
  [sym_unary_op] = {
    .visible = true,
    .named = true,
  },
  [sym_binary_op] = {
    .visible = true,
    .named = true,
  },
  [sym_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_integer_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_float_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_type] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_arg_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_call_params_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(2);
      if (lookahead == '(') ADVANCE(3);
      if (lookahead == ')') ADVANCE(4);
      if (lookahead == ',') ADVANCE(7);
      if (lookahead == '-') ADVANCE(9);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '/') ADVANCE(1);
      if (lookahead == ':') ADVANCE(8);
      if (lookahead == 'v') ADVANCE(17);
      if (lookahead == '{') ADVANCE(5);
      if (lookahead == '}') ADVANCE(6);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(14);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(18);
      END_STATE();
    case 1:
      if (lookahead == '/') ADVANCE(19);
      END_STATE();
    case 2:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 3:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 4:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(anon_sym_vec2);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(anon_sym_vec3);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_vec4);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(sym_digit);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_') ADVANCE(14);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(11);
      if (lookahead == '3') ADVANCE(12);
      if (lookahead == '4') ADVANCE(13);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(18);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(15);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(18);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(16);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(18);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(18);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (lookahead == 'b') ADVANCE(1);
      if (lookahead == 'f') ADVANCE(2);
      if (lookahead == 'i') ADVANCE(3);
      if (lookahead == 'p') ADVANCE(4);
      if (lookahead == 'r') ADVANCE(5);
      if (lookahead == 's') ADVANCE(6);
      if (lookahead == 't') ADVANCE(7);
      if (lookahead == 'u') ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'o') ADVANCE(9);
      END_STATE();
    case 2:
      if (lookahead == 'i') ADVANCE(10);
      if (lookahead == 'l') ADVANCE(11);
      END_STATE();
    case 3:
      if (lookahead == 'n') ADVANCE(12);
      END_STATE();
    case 4:
      if (lookahead == 'l') ADVANCE(13);
      END_STATE();
    case 5:
      if (lookahead == 'e') ADVANCE(14);
      END_STATE();
    case 6:
      if (lookahead == 'm') ADVANCE(15);
      if (lookahead == 'p') ADVANCE(16);
      if (lookahead == 'u') ADVANCE(17);
      END_STATE();
    case 7:
      if (lookahead == 'o') ADVANCE(18);
      if (lookahead == 'r') ADVANCE(19);
      END_STATE();
    case 8:
      if (lookahead == 'n') ADVANCE(20);
      END_STATE();
    case 9:
      if (lookahead == 'x') ADVANCE(21);
      END_STATE();
    case 10:
      if (lookahead == 'e') ADVANCE(22);
      END_STATE();
    case 11:
      if (lookahead == 'o') ADVANCE(23);
      END_STATE();
    case 12:
      if (lookahead == 't') ADVANCE(24);
      END_STATE();
    case 13:
      if (lookahead == 'a') ADVANCE(25);
      END_STATE();
    case 14:
      if (lookahead == 'p') ADVANCE(26);
      END_STATE();
    case 15:
      if (lookahead == 'o') ADVANCE(27);
      END_STATE();
    case 16:
      if (lookahead == 'h') ADVANCE(28);
      END_STATE();
    case 17:
      if (lookahead == 'b') ADVANCE(29);
      END_STATE();
    case 18:
      if (lookahead == 'r') ADVANCE(30);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(31);
      END_STATE();
    case 20:
      if (lookahead == 'i') ADVANCE(32);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_box);
      END_STATE();
    case 22:
      if (lookahead == 'l') ADVANCE(33);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(34);
      END_STATE();
    case 24:
      if (lookahead == 'e') ADVANCE(35);
      END_STATE();
    case 25:
      if (lookahead == 'n') ADVANCE(36);
      END_STATE();
    case 26:
      if (lookahead == 'e') ADVANCE(37);
      END_STATE();
    case 27:
      if (lookahead == 'o') ADVANCE(38);
      END_STATE();
    case 28:
      if (lookahead == 'e') ADVANCE(39);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_sub);
      END_STATE();
    case 30:
      if (lookahead == 'u') ADVANCE(40);
      END_STATE();
    case 31:
      if (lookahead == 'n') ADVANCE(41);
      END_STATE();
    case 32:
      if (lookahead == 'o') ADVANCE(42);
      END_STATE();
    case 33:
      if (lookahead == 'd') ADVANCE(43);
      END_STATE();
    case 34:
      if (lookahead == 't') ADVANCE(44);
      END_STATE();
    case 35:
      if (lookahead == 'r') ADVANCE(45);
      END_STATE();
    case 36:
      if (lookahead == 'e') ADVANCE(46);
      END_STATE();
    case 37:
      if (lookahead == 'a') ADVANCE(47);
      END_STATE();
    case 38:
      if (lookahead == 't') ADVANCE(48);
      END_STATE();
    case 39:
      if (lookahead == 'r') ADVANCE(49);
      END_STATE();
    case 40:
      if (lookahead == 's') ADVANCE(50);
      END_STATE();
    case 41:
      if (lookahead == 's') ADVANCE(51);
      END_STATE();
    case 42:
      if (lookahead == 'n') ADVANCE(52);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_field);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_float);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_inter);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_plane);
      END_STATE();
    case 47:
      if (lookahead == 't') ADVANCE(53);
      END_STATE();
    case 48:
      if (lookahead == 'h') ADVANCE(54);
      END_STATE();
    case 49:
      if (lookahead == 'e') ADVANCE(55);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_torus);
      END_STATE();
    case 51:
      if (lookahead == 'l') ADVANCE(56);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_union);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_repeat);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_smooth);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_sphere);
      END_STATE();
    case 56:
      if (lookahead == 'a') ADVANCE(57);
      END_STATE();
    case 57:
      if (lookahead == 't') ADVANCE(58);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(59);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_translate);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_field] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_sphere] = ACTIONS(1),
    [anon_sym_box] = ACTIONS(1),
    [anon_sym_torus] = ACTIONS(1),
    [anon_sym_plane] = ACTIONS(1),
    [anon_sym_translate] = ACTIONS(1),
    [anon_sym_repeat] = ACTIONS(1),
    [anon_sym_smooth] = ACTIONS(1),
    [anon_sym_union] = ACTIONS(1),
    [anon_sym_sub] = ACTIONS(1),
    [anon_sym_inter] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_float] = ACTIONS(1),
    [anon_sym_vec2] = ACTIONS(1),
    [anon_sym_vec3] = ACTIONS(1),
    [anon_sym_vec4] = ACTIONS(1),
    [sym_digit] = ACTIONS(1),
    [sym_comment] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(78),
    [sym_field_decl] = STATE(18),
    [aux_sym_source_file_repeat1] = STATE(18),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_field] = ACTIONS(5),
    [sym_comment] = ACTIONS(7),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 7,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 3,
      anon_sym_translate,
      anon_sym_repeat,
      anon_sym_smooth,
    ACTIONS(13), 3,
      anon_sym_union,
      anon_sym_sub,
      anon_sym_inter,
    ACTIONS(9), 4,
      anon_sym_sphere,
      anon_sym_box,
      anon_sym_torus,
      anon_sym_plane,
    STATE(80), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [32] = 7,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 3,
      anon_sym_translate,
      anon_sym_repeat,
      anon_sym_smooth,
    ACTIONS(13), 3,
      anon_sym_union,
      anon_sym_sub,
      anon_sym_inter,
    ACTIONS(9), 4,
      anon_sym_sphere,
      anon_sym_box,
      anon_sym_torus,
      anon_sym_plane,
    STATE(77), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [64] = 7,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 3,
      anon_sym_translate,
      anon_sym_repeat,
      anon_sym_smooth,
    ACTIONS(13), 3,
      anon_sym_union,
      anon_sym_sub,
      anon_sym_inter,
    ACTIONS(9), 4,
      anon_sym_sphere,
      anon_sym_box,
      anon_sym_torus,
      anon_sym_plane,
    STATE(40), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [96] = 7,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 3,
      anon_sym_translate,
      anon_sym_repeat,
      anon_sym_smooth,
    ACTIONS(13), 3,
      anon_sym_union,
      anon_sym_sub,
      anon_sym_inter,
    ACTIONS(9), 4,
      anon_sym_sphere,
      anon_sym_box,
      anon_sym_torus,
      anon_sym_plane,
    STATE(73), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [128] = 7,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 3,
      anon_sym_translate,
      anon_sym_repeat,
      anon_sym_smooth,
    ACTIONS(13), 3,
      anon_sym_union,
      anon_sym_sub,
      anon_sym_inter,
    ACTIONS(9), 4,
      anon_sym_sphere,
      anon_sym_box,
      anon_sym_torus,
      anon_sym_plane,
    STATE(71), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [160] = 7,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 3,
      anon_sym_translate,
      anon_sym_repeat,
      anon_sym_smooth,
    ACTIONS(13), 3,
      anon_sym_union,
      anon_sym_sub,
      anon_sym_inter,
    ACTIONS(9), 4,
      anon_sym_sphere,
      anon_sym_box,
      anon_sym_torus,
      anon_sym_plane,
    STATE(66), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [192] = 7,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 3,
      anon_sym_translate,
      anon_sym_repeat,
      anon_sym_smooth,
    ACTIONS(13), 3,
      anon_sym_union,
      anon_sym_sub,
      anon_sym_inter,
    ACTIONS(9), 4,
      anon_sym_sphere,
      anon_sym_box,
      anon_sym_torus,
      anon_sym_plane,
    STATE(48), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [224] = 7,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 3,
      anon_sym_translate,
      anon_sym_repeat,
      anon_sym_smooth,
    ACTIONS(13), 3,
      anon_sym_union,
      anon_sym_sub,
      anon_sym_inter,
    ACTIONS(9), 4,
      anon_sym_sphere,
      anon_sym_box,
      anon_sym_torus,
      anon_sym_plane,
    STATE(64), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [256] = 12,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(17), 1,
      anon_sym_RPAREN,
    ACTIONS(19), 1,
      anon_sym_DASH,
    ACTIONS(21), 1,
      anon_sym_float,
    ACTIONS(25), 1,
      sym_digit,
    STATE(14), 1,
      aux_sym_call_params_repeat1,
    STATE(37), 1,
      sym_param,
    STATE(42), 1,
      sym_type,
    STATE(47), 1,
      sym_call_params,
    STATE(30), 2,
      sym_integer_literal,
      sym_float_literal,
    STATE(38), 2,
      sym_type_constructor,
      sym_literal,
    ACTIONS(23), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [297] = 12,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_DASH,
    ACTIONS(21), 1,
      anon_sym_float,
    ACTIONS(25), 1,
      sym_digit,
    ACTIONS(27), 1,
      anon_sym_RPAREN,
    STATE(14), 1,
      aux_sym_call_params_repeat1,
    STATE(37), 1,
      sym_param,
    STATE(42), 1,
      sym_type,
    STATE(45), 1,
      sym_call_params,
    STATE(30), 2,
      sym_integer_literal,
      sym_float_literal,
    STATE(38), 2,
      sym_type_constructor,
      sym_literal,
    ACTIONS(23), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [338] = 12,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_DASH,
    ACTIONS(21), 1,
      anon_sym_float,
    ACTIONS(25), 1,
      sym_digit,
    ACTIONS(29), 1,
      anon_sym_RPAREN,
    STATE(14), 1,
      aux_sym_call_params_repeat1,
    STATE(37), 1,
      sym_param,
    STATE(41), 1,
      sym_call_params,
    STATE(42), 1,
      sym_type,
    STATE(30), 2,
      sym_integer_literal,
      sym_float_literal,
    STATE(38), 2,
      sym_type_constructor,
      sym_literal,
    ACTIONS(23), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [379] = 11,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_DASH,
    ACTIONS(21), 1,
      anon_sym_float,
    ACTIONS(25), 1,
      sym_digit,
    STATE(14), 1,
      aux_sym_call_params_repeat1,
    STATE(37), 1,
      sym_param,
    STATE(42), 1,
      sym_type,
    STATE(62), 1,
      sym_call_params,
    STATE(30), 2,
      sym_integer_literal,
      sym_float_literal,
    STATE(38), 2,
      sym_type_constructor,
      sym_literal,
    ACTIONS(23), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [417] = 10,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_DASH,
    ACTIONS(21), 1,
      anon_sym_float,
    ACTIONS(25), 1,
      sym_digit,
    STATE(15), 1,
      aux_sym_call_params_repeat1,
    STATE(36), 1,
      sym_param,
    STATE(42), 1,
      sym_type,
    STATE(30), 2,
      sym_integer_literal,
      sym_float_literal,
    STATE(38), 2,
      sym_type_constructor,
      sym_literal,
    ACTIONS(23), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [452] = 10,
    ACTIONS(31), 1,
      sym_identifier,
    ACTIONS(34), 1,
      anon_sym_DASH,
    ACTIONS(37), 1,
      anon_sym_float,
    ACTIONS(43), 1,
      sym_digit,
    STATE(15), 1,
      aux_sym_call_params_repeat1,
    STATE(42), 1,
      sym_type,
    STATE(63), 1,
      sym_param,
    STATE(30), 2,
      sym_integer_literal,
      sym_float_literal,
    STATE(38), 2,
      sym_type_constructor,
      sym_literal,
    ACTIONS(40), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [487] = 2,
    ACTIONS(46), 2,
      anon_sym_float,
      sym_identifier,
    ACTIONS(48), 5,
      anon_sym_DASH,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
      sym_digit,
  [499] = 2,
    STATE(33), 1,
      sym_type,
    ACTIONS(23), 4,
      anon_sym_float,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [509] = 4,
    ACTIONS(5), 1,
      anon_sym_field,
    ACTIONS(50), 1,
      ts_builtin_sym_end,
    ACTIONS(52), 1,
      sym_comment,
    STATE(20), 2,
      sym_field_decl,
      aux_sym_source_file_repeat1,
  [523] = 5,
    ACTIONS(54), 1,
      sym_identifier,
    ACTIONS(56), 1,
      anon_sym_RPAREN,
    STATE(26), 1,
      aux_sym_arg_list_repeat1,
    STATE(34), 1,
      sym_typed_arg,
    STATE(61), 1,
      sym_arg_list,
  [539] = 4,
    ACTIONS(58), 1,
      ts_builtin_sym_end,
    ACTIONS(60), 1,
      anon_sym_field,
    ACTIONS(63), 1,
      sym_comment,
    STATE(20), 2,
      sym_field_decl,
      aux_sym_source_file_repeat1,
  [553] = 3,
    ACTIONS(66), 1,
      sym_identifier,
    STATE(21), 1,
      aux_sym_arg_list_repeat1,
    STATE(68), 1,
      sym_typed_arg,
  [563] = 2,
    ACTIONS(71), 1,
      sym_digit,
    ACTIONS(69), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [571] = 1,
    ACTIONS(73), 3,
      ts_builtin_sym_end,
      anon_sym_field,
      sym_comment,
  [577] = 2,
    ACTIONS(77), 1,
      anon_sym_DOT,
    ACTIONS(75), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [585] = 1,
    ACTIONS(79), 3,
      ts_builtin_sym_end,
      anon_sym_field,
      sym_comment,
  [591] = 3,
    ACTIONS(54), 1,
      sym_identifier,
    STATE(21), 1,
      aux_sym_arg_list_repeat1,
    STATE(35), 1,
      sym_typed_arg,
  [601] = 2,
    ACTIONS(83), 1,
      sym_digit,
    ACTIONS(81), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [609] = 1,
    ACTIONS(85), 3,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [615] = 1,
    ACTIONS(81), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [620] = 1,
    ACTIONS(87), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [625] = 1,
    ACTIONS(89), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [630] = 1,
    ACTIONS(91), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [635] = 1,
    ACTIONS(93), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [640] = 2,
    ACTIONS(95), 1,
      anon_sym_RPAREN,
    ACTIONS(97), 1,
      anon_sym_COMMA,
  [647] = 2,
    ACTIONS(97), 1,
      anon_sym_COMMA,
    ACTIONS(99), 1,
      anon_sym_RPAREN,
  [654] = 2,
    ACTIONS(101), 1,
      anon_sym_RPAREN,
    ACTIONS(103), 1,
      anon_sym_COMMA,
  [661] = 2,
    ACTIONS(103), 1,
      anon_sym_COMMA,
    ACTIONS(105), 1,
      anon_sym_RPAREN,
  [668] = 1,
    ACTIONS(107), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [673] = 1,
    ACTIONS(109), 1,
      sym_identifier,
  [677] = 1,
    ACTIONS(111), 1,
      anon_sym_RBRACE,
  [681] = 1,
    ACTIONS(113), 1,
      anon_sym_RPAREN,
  [685] = 1,
    ACTIONS(115), 1,
      anon_sym_LPAREN,
  [689] = 1,
    ACTIONS(117), 1,
      anon_sym_LPAREN,
  [693] = 1,
    ACTIONS(119), 1,
      anon_sym_LBRACE,
  [697] = 1,
    ACTIONS(121), 1,
      anon_sym_RPAREN,
  [701] = 1,
    ACTIONS(123), 1,
      anon_sym_LBRACE,
  [705] = 1,
    ACTIONS(125), 1,
      anon_sym_RPAREN,
  [709] = 1,
    ACTIONS(127), 1,
      anon_sym_RBRACE,
  [713] = 1,
    ACTIONS(129), 1,
      anon_sym_DOT,
  [717] = 1,
    ACTIONS(131), 1,
      anon_sym_LPAREN,
  [721] = 1,
    ACTIONS(133), 1,
      anon_sym_RBRACE,
  [725] = 1,
    ACTIONS(135), 1,
      anon_sym_LPAREN,
  [729] = 1,
    ACTIONS(137), 1,
      anon_sym_LPAREN,
  [733] = 1,
    ACTIONS(139), 1,
      anon_sym_LPAREN,
  [737] = 1,
    ACTIONS(141), 1,
      anon_sym_RBRACE,
  [741] = 1,
    ACTIONS(143), 1,
      sym_identifier,
  [745] = 1,
    ACTIONS(145), 1,
      anon_sym_LBRACE,
  [749] = 1,
    ACTIONS(147), 1,
      anon_sym_LBRACE,
  [753] = 1,
    ACTIONS(149), 1,
      anon_sym_LBRACE,
  [757] = 1,
    ACTIONS(151), 1,
      sym_digit,
  [761] = 1,
    ACTIONS(153), 1,
      anon_sym_RPAREN,
  [765] = 1,
    ACTIONS(155), 1,
      anon_sym_RPAREN,
  [769] = 1,
    ACTIONS(103), 1,
      anon_sym_COMMA,
  [773] = 1,
    ACTIONS(157), 1,
      anon_sym_RBRACE,
  [777] = 1,
    ACTIONS(159), 1,
      anon_sym_COLON,
  [781] = 1,
    ACTIONS(161), 1,
      anon_sym_RBRACE,
  [785] = 1,
    ACTIONS(163), 1,
      anon_sym_LBRACE,
  [789] = 1,
    ACTIONS(97), 1,
      anon_sym_COMMA,
  [793] = 1,
    ACTIONS(165), 1,
      anon_sym_LPAREN,
  [797] = 1,
    ACTIONS(167), 1,
      anon_sym_RBRACE,
  [801] = 1,
    ACTIONS(169), 1,
      anon_sym_RBRACE,
  [805] = 1,
    ACTIONS(171), 1,
      anon_sym_LBRACE,
  [809] = 1,
    ACTIONS(173), 1,
      anon_sym_RBRACE,
  [813] = 1,
    ACTIONS(175), 1,
      anon_sym_RBRACE,
  [817] = 1,
    ACTIONS(177), 1,
      anon_sym_LPAREN,
  [821] = 1,
    ACTIONS(179), 1,
      anon_sym_LBRACE,
  [825] = 1,
    ACTIONS(181), 1,
      anon_sym_RBRACE,
  [829] = 1,
    ACTIONS(183), 1,
      ts_builtin_sym_end,
  [833] = 1,
    ACTIONS(185), 1,
      anon_sym_RBRACE,
  [837] = 1,
    ACTIONS(187), 1,
      anon_sym_RBRACE,
  [841] = 1,
    ACTIONS(189), 1,
      anon_sym_RBRACE,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 32,
  [SMALL_STATE(4)] = 64,
  [SMALL_STATE(5)] = 96,
  [SMALL_STATE(6)] = 128,
  [SMALL_STATE(7)] = 160,
  [SMALL_STATE(8)] = 192,
  [SMALL_STATE(9)] = 224,
  [SMALL_STATE(10)] = 256,
  [SMALL_STATE(11)] = 297,
  [SMALL_STATE(12)] = 338,
  [SMALL_STATE(13)] = 379,
  [SMALL_STATE(14)] = 417,
  [SMALL_STATE(15)] = 452,
  [SMALL_STATE(16)] = 487,
  [SMALL_STATE(17)] = 499,
  [SMALL_STATE(18)] = 509,
  [SMALL_STATE(19)] = 523,
  [SMALL_STATE(20)] = 539,
  [SMALL_STATE(21)] = 553,
  [SMALL_STATE(22)] = 563,
  [SMALL_STATE(23)] = 571,
  [SMALL_STATE(24)] = 577,
  [SMALL_STATE(25)] = 585,
  [SMALL_STATE(26)] = 591,
  [SMALL_STATE(27)] = 601,
  [SMALL_STATE(28)] = 609,
  [SMALL_STATE(29)] = 615,
  [SMALL_STATE(30)] = 620,
  [SMALL_STATE(31)] = 625,
  [SMALL_STATE(32)] = 630,
  [SMALL_STATE(33)] = 635,
  [SMALL_STATE(34)] = 640,
  [SMALL_STATE(35)] = 647,
  [SMALL_STATE(36)] = 654,
  [SMALL_STATE(37)] = 661,
  [SMALL_STATE(38)] = 668,
  [SMALL_STATE(39)] = 673,
  [SMALL_STATE(40)] = 677,
  [SMALL_STATE(41)] = 681,
  [SMALL_STATE(42)] = 685,
  [SMALL_STATE(43)] = 689,
  [SMALL_STATE(44)] = 693,
  [SMALL_STATE(45)] = 697,
  [SMALL_STATE(46)] = 701,
  [SMALL_STATE(47)] = 705,
  [SMALL_STATE(48)] = 709,
  [SMALL_STATE(49)] = 713,
  [SMALL_STATE(50)] = 717,
  [SMALL_STATE(51)] = 721,
  [SMALL_STATE(52)] = 725,
  [SMALL_STATE(53)] = 729,
  [SMALL_STATE(54)] = 733,
  [SMALL_STATE(55)] = 737,
  [SMALL_STATE(56)] = 741,
  [SMALL_STATE(57)] = 745,
  [SMALL_STATE(58)] = 749,
  [SMALL_STATE(59)] = 753,
  [SMALL_STATE(60)] = 757,
  [SMALL_STATE(61)] = 761,
  [SMALL_STATE(62)] = 765,
  [SMALL_STATE(63)] = 769,
  [SMALL_STATE(64)] = 773,
  [SMALL_STATE(65)] = 777,
  [SMALL_STATE(66)] = 781,
  [SMALL_STATE(67)] = 785,
  [SMALL_STATE(68)] = 789,
  [SMALL_STATE(69)] = 793,
  [SMALL_STATE(70)] = 797,
  [SMALL_STATE(71)] = 801,
  [SMALL_STATE(72)] = 805,
  [SMALL_STATE(73)] = 809,
  [SMALL_STATE(74)] = 813,
  [SMALL_STATE(75)] = 817,
  [SMALL_STATE(76)] = 821,
  [SMALL_STATE(77)] = 825,
  [SMALL_STATE(78)] = 829,
  [SMALL_STATE(79)] = 833,
  [SMALL_STATE(80)] = 837,
  [SMALL_STATE(81)] = 841,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [31] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(38),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(60),
  [37] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(28),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(28),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(24),
  [46] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [52] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [60] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(39),
  [63] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(20),
  [66] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_arg_list_repeat1, 2), SHIFT_REPEAT(65),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 2),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 8),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_integer_literal, 1),
  [77] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 7),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 3),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 1),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_constructor, 4),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 4),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_typed_arg, 3),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_list, 1),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_list, 2),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_params, 2),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_params, 1),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_param, 1),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_op, 1),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim_call, 4),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_op, 1),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim, 1),
  [139] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim_call, 3),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arg_list_repeat1, 2),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_call, 6),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_call, 7),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [183] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [185] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_call, 9),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [189] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_call, 10),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_minisdf(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
