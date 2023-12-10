#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 80
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
  anon_sym_SEMI = 9,
  anon_sym_sphere = 10,
  anon_sym_box = 11,
  anon_sym_torus = 12,
  anon_sym_plane = 13,
  anon_sym_translate = 14,
  anon_sym_repeat = 15,
  anon_sym_smooth = 16,
  anon_sym_union = 17,
  anon_sym_sub = 18,
  anon_sym_inter = 19,
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
  [anon_sym_SEMI] = ";",
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
  [anon_sym_SEMI] = anon_sym_SEMI,
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
  [anon_sym_SEMI] = {
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
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '/') ADVANCE(1);
      if (lookahead == ':') ADVANCE(8);
      if (lookahead == ';') ADVANCE(9);
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
      ACCEPT_TOKEN(anon_sym_SEMI);
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
    [anon_sym_SEMI] = ACTIONS(1),
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
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_float] = ACTIONS(1),
    [anon_sym_vec2] = ACTIONS(1),
    [anon_sym_vec3] = ACTIONS(1),
    [anon_sym_vec4] = ACTIONS(1),
    [sym_digit] = ACTIONS(1),
    [sym_comment] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(76),
    [sym_field_decl] = STATE(17),
    [aux_sym_source_file_repeat1] = STATE(17),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_field] = ACTIONS(5),
    [sym_comment] = ACTIONS(7),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 7,
    STATE(49), 1,
      sym_binary_op,
    STATE(51), 1,
      sym_unary_op,
    STATE(52), 1,
      sym_prim,
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
    STATE(53), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [32] = 7,
    STATE(49), 1,
      sym_binary_op,
    STATE(51), 1,
      sym_unary_op,
    STATE(52), 1,
      sym_prim,
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
    STATE(78), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [64] = 7,
    STATE(49), 1,
      sym_binary_op,
    STATE(51), 1,
      sym_unary_op,
    STATE(52), 1,
      sym_prim,
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
    STATE(75), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [96] = 7,
    STATE(49), 1,
      sym_binary_op,
    STATE(51), 1,
      sym_unary_op,
    STATE(52), 1,
      sym_prim,
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
    STATE(42), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [128] = 7,
    STATE(49), 1,
      sym_binary_op,
    STATE(51), 1,
      sym_unary_op,
    STATE(52), 1,
      sym_prim,
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
    STATE(63), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [160] = 7,
    STATE(49), 1,
      sym_binary_op,
    STATE(51), 1,
      sym_unary_op,
    STATE(52), 1,
      sym_prim,
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
    STATE(65), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [192] = 7,
    STATE(49), 1,
      sym_binary_op,
    STATE(51), 1,
      sym_unary_op,
    STATE(52), 1,
      sym_prim,
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
  [224] = 7,
    STATE(49), 1,
      sym_binary_op,
    STATE(51), 1,
      sym_unary_op,
    STATE(52), 1,
      sym_prim,
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
    STATE(69), 4,
      sym__field_tree,
      sym_unary_call,
      sym_binary_call,
      sym_prim_call,
  [256] = 11,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(17), 1,
      anon_sym_RPAREN,
    ACTIONS(19), 1,
      anon_sym_float,
    ACTIONS(23), 1,
      sym_digit,
    STATE(14), 1,
      aux_sym_call_params_repeat1,
    STATE(36), 1,
      sym_param,
    STATE(41), 1,
      sym_type,
    STATE(46), 1,
      sym_call_params,
    STATE(31), 2,
      sym_type_constructor,
      sym_literal,
    STATE(35), 2,
      sym_integer_literal,
      sym_float_literal,
    ACTIONS(21), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [294] = 11,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_float,
    ACTIONS(23), 1,
      sym_digit,
    ACTIONS(25), 1,
      anon_sym_RPAREN,
    STATE(14), 1,
      aux_sym_call_params_repeat1,
    STATE(36), 1,
      sym_param,
    STATE(41), 1,
      sym_type,
    STATE(58), 1,
      sym_call_params,
    STATE(31), 2,
      sym_type_constructor,
      sym_literal,
    STATE(35), 2,
      sym_integer_literal,
      sym_float_literal,
    ACTIONS(21), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [332] = 11,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_float,
    ACTIONS(23), 1,
      sym_digit,
    ACTIONS(27), 1,
      anon_sym_RPAREN,
    STATE(14), 1,
      aux_sym_call_params_repeat1,
    STATE(36), 1,
      sym_param,
    STATE(41), 1,
      sym_type,
    STATE(44), 1,
      sym_call_params,
    STATE(31), 2,
      sym_type_constructor,
      sym_literal,
    STATE(35), 2,
      sym_integer_literal,
      sym_float_literal,
    ACTIONS(21), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [370] = 10,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_float,
    ACTIONS(23), 1,
      sym_digit,
    STATE(14), 1,
      aux_sym_call_params_repeat1,
    STATE(36), 1,
      sym_param,
    STATE(41), 1,
      sym_type,
    STATE(61), 1,
      sym_call_params,
    STATE(31), 2,
      sym_type_constructor,
      sym_literal,
    STATE(35), 2,
      sym_integer_literal,
      sym_float_literal,
    ACTIONS(21), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [405] = 9,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_float,
    ACTIONS(23), 1,
      sym_digit,
    STATE(15), 1,
      aux_sym_call_params_repeat1,
    STATE(28), 1,
      sym_param,
    STATE(41), 1,
      sym_type,
    STATE(31), 2,
      sym_type_constructor,
      sym_literal,
    STATE(35), 2,
      sym_integer_literal,
      sym_float_literal,
    ACTIONS(21), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [437] = 9,
    ACTIONS(29), 1,
      sym_identifier,
    ACTIONS(32), 1,
      anon_sym_float,
    ACTIONS(38), 1,
      sym_digit,
    STATE(15), 1,
      aux_sym_call_params_repeat1,
    STATE(41), 1,
      sym_type,
    STATE(62), 1,
      sym_param,
    STATE(31), 2,
      sym_type_constructor,
      sym_literal,
    STATE(35), 2,
      sym_integer_literal,
      sym_float_literal,
    ACTIONS(35), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [469] = 2,
    ACTIONS(41), 2,
      anon_sym_float,
      sym_identifier,
    ACTIONS(43), 4,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
      sym_digit,
  [480] = 4,
    ACTIONS(5), 1,
      anon_sym_field,
    ACTIONS(45), 1,
      ts_builtin_sym_end,
    ACTIONS(47), 1,
      sym_comment,
    STATE(20), 2,
      sym_field_decl,
      aux_sym_source_file_repeat1,
  [494] = 2,
    STATE(30), 1,
      sym_type,
    ACTIONS(21), 4,
      anon_sym_float,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [504] = 5,
    ACTIONS(49), 1,
      sym_identifier,
    ACTIONS(51), 1,
      anon_sym_RPAREN,
    STATE(26), 1,
      aux_sym_arg_list_repeat1,
    STATE(33), 1,
      sym_typed_arg,
    STATE(64), 1,
      sym_arg_list,
  [520] = 4,
    ACTIONS(53), 1,
      ts_builtin_sym_end,
    ACTIONS(55), 1,
      anon_sym_field,
    ACTIONS(58), 1,
      sym_comment,
    STATE(20), 2,
      sym_field_decl,
      aux_sym_source_file_repeat1,
  [534] = 3,
    ACTIONS(61), 1,
      sym_identifier,
    STATE(21), 1,
      aux_sym_arg_list_repeat1,
    STATE(47), 1,
      sym_typed_arg,
  [544] = 2,
    ACTIONS(66), 1,
      sym_digit,
    ACTIONS(64), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [552] = 1,
    ACTIONS(68), 3,
      ts_builtin_sym_end,
      anon_sym_field,
      sym_comment,
  [558] = 1,
    ACTIONS(70), 3,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [564] = 1,
    ACTIONS(72), 3,
      ts_builtin_sym_end,
      anon_sym_field,
      sym_comment,
  [570] = 3,
    ACTIONS(49), 1,
      sym_identifier,
    STATE(21), 1,
      aux_sym_arg_list_repeat1,
    STATE(32), 1,
      sym_typed_arg,
  [580] = 2,
    ACTIONS(76), 1,
      anon_sym_DOT,
    ACTIONS(74), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [588] = 2,
    ACTIONS(78), 1,
      anon_sym_RPAREN,
    ACTIONS(80), 1,
      anon_sym_COMMA,
  [595] = 1,
    ACTIONS(82), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [600] = 1,
    ACTIONS(84), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [605] = 1,
    ACTIONS(86), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [610] = 2,
    ACTIONS(88), 1,
      anon_sym_RPAREN,
    ACTIONS(90), 1,
      anon_sym_COMMA,
  [617] = 2,
    ACTIONS(90), 1,
      anon_sym_COMMA,
    ACTIONS(92), 1,
      anon_sym_RPAREN,
  [624] = 1,
    ACTIONS(94), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [629] = 1,
    ACTIONS(96), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [634] = 2,
    ACTIONS(80), 1,
      anon_sym_COMMA,
    ACTIONS(98), 1,
      anon_sym_RPAREN,
  [641] = 1,
    ACTIONS(100), 1,
      anon_sym_LPAREN,
  [645] = 1,
    ACTIONS(102), 1,
      anon_sym_LBRACE,
  [649] = 1,
    ACTIONS(104), 1,
      sym_identifier,
  [653] = 1,
    ACTIONS(106), 1,
      anon_sym_SEMI,
  [657] = 1,
    ACTIONS(108), 1,
      anon_sym_LPAREN,
  [661] = 1,
    ACTIONS(110), 1,
      anon_sym_RBRACE,
  [665] = 1,
    ACTIONS(112), 1,
      anon_sym_LBRACE,
  [669] = 1,
    ACTIONS(114), 1,
      anon_sym_RPAREN,
  [673] = 1,
    ACTIONS(116), 1,
      anon_sym_LBRACE,
  [677] = 1,
    ACTIONS(118), 1,
      anon_sym_RPAREN,
  [681] = 1,
    ACTIONS(90), 1,
      anon_sym_COMMA,
  [685] = 1,
    ACTIONS(120), 1,
      anon_sym_RBRACE,
  [689] = 1,
    ACTIONS(122), 1,
      anon_sym_LPAREN,
  [693] = 1,
    ACTIONS(124), 1,
      anon_sym_SEMI,
  [697] = 1,
    ACTIONS(126), 1,
      anon_sym_LPAREN,
  [701] = 1,
    ACTIONS(128), 1,
      anon_sym_LPAREN,
  [705] = 1,
    ACTIONS(130), 1,
      anon_sym_RBRACE,
  [709] = 1,
    ACTIONS(132), 1,
      anon_sym_LPAREN,
  [713] = 1,
    ACTIONS(134), 1,
      anon_sym_LPAREN,
  [717] = 1,
    ACTIONS(136), 1,
      anon_sym_LBRACE,
  [721] = 1,
    ACTIONS(138), 1,
      sym_identifier,
  [725] = 1,
    ACTIONS(140), 1,
      anon_sym_RPAREN,
  [729] = 1,
    ACTIONS(142), 1,
      anon_sym_LBRACE,
  [733] = 1,
    ACTIONS(144), 1,
      anon_sym_RBRACE,
  [737] = 1,
    ACTIONS(146), 1,
      anon_sym_RPAREN,
  [741] = 1,
    ACTIONS(80), 1,
      anon_sym_COMMA,
  [745] = 1,
    ACTIONS(148), 1,
      anon_sym_RBRACE,
  [749] = 1,
    ACTIONS(150), 1,
      anon_sym_RPAREN,
  [753] = 1,
    ACTIONS(152), 1,
      anon_sym_RBRACE,
  [757] = 1,
    ACTIONS(154), 1,
      anon_sym_COLON,
  [761] = 1,
    ACTIONS(156), 1,
      anon_sym_LBRACE,
  [765] = 1,
    ACTIONS(158), 1,
      anon_sym_RBRACE,
  [769] = 1,
    ACTIONS(160), 1,
      anon_sym_RBRACE,
  [773] = 1,
    ACTIONS(162), 1,
      anon_sym_LBRACE,
  [777] = 1,
    ACTIONS(164), 1,
      anon_sym_RBRACE,
  [781] = 1,
    ACTIONS(166), 1,
      anon_sym_RBRACE,
  [785] = 1,
    ACTIONS(168), 1,
      anon_sym_LPAREN,
  [789] = 1,
    ACTIONS(170), 1,
      anon_sym_LBRACE,
  [793] = 1,
    ACTIONS(172), 1,
      anon_sym_RBRACE,
  [797] = 1,
    ACTIONS(174), 1,
      ts_builtin_sym_end,
  [801] = 1,
    ACTIONS(176), 1,
      anon_sym_RBRACE,
  [805] = 1,
    ACTIONS(178), 1,
      anon_sym_RBRACE,
  [809] = 1,
    ACTIONS(180), 1,
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
  [SMALL_STATE(11)] = 294,
  [SMALL_STATE(12)] = 332,
  [SMALL_STATE(13)] = 370,
  [SMALL_STATE(14)] = 405,
  [SMALL_STATE(15)] = 437,
  [SMALL_STATE(16)] = 469,
  [SMALL_STATE(17)] = 480,
  [SMALL_STATE(18)] = 494,
  [SMALL_STATE(19)] = 504,
  [SMALL_STATE(20)] = 520,
  [SMALL_STATE(21)] = 534,
  [SMALL_STATE(22)] = 544,
  [SMALL_STATE(23)] = 552,
  [SMALL_STATE(24)] = 558,
  [SMALL_STATE(25)] = 564,
  [SMALL_STATE(26)] = 570,
  [SMALL_STATE(27)] = 580,
  [SMALL_STATE(28)] = 588,
  [SMALL_STATE(29)] = 595,
  [SMALL_STATE(30)] = 600,
  [SMALL_STATE(31)] = 605,
  [SMALL_STATE(32)] = 610,
  [SMALL_STATE(33)] = 617,
  [SMALL_STATE(34)] = 624,
  [SMALL_STATE(35)] = 629,
  [SMALL_STATE(36)] = 634,
  [SMALL_STATE(37)] = 641,
  [SMALL_STATE(38)] = 645,
  [SMALL_STATE(39)] = 649,
  [SMALL_STATE(40)] = 653,
  [SMALL_STATE(41)] = 657,
  [SMALL_STATE(42)] = 661,
  [SMALL_STATE(43)] = 665,
  [SMALL_STATE(44)] = 669,
  [SMALL_STATE(45)] = 673,
  [SMALL_STATE(46)] = 677,
  [SMALL_STATE(47)] = 681,
  [SMALL_STATE(48)] = 685,
  [SMALL_STATE(49)] = 689,
  [SMALL_STATE(50)] = 693,
  [SMALL_STATE(51)] = 697,
  [SMALL_STATE(52)] = 701,
  [SMALL_STATE(53)] = 705,
  [SMALL_STATE(54)] = 709,
  [SMALL_STATE(55)] = 713,
  [SMALL_STATE(56)] = 717,
  [SMALL_STATE(57)] = 721,
  [SMALL_STATE(58)] = 725,
  [SMALL_STATE(59)] = 729,
  [SMALL_STATE(60)] = 733,
  [SMALL_STATE(61)] = 737,
  [SMALL_STATE(62)] = 741,
  [SMALL_STATE(63)] = 745,
  [SMALL_STATE(64)] = 749,
  [SMALL_STATE(65)] = 753,
  [SMALL_STATE(66)] = 757,
  [SMALL_STATE(67)] = 761,
  [SMALL_STATE(68)] = 765,
  [SMALL_STATE(69)] = 769,
  [SMALL_STATE(70)] = 773,
  [SMALL_STATE(71)] = 777,
  [SMALL_STATE(72)] = 781,
  [SMALL_STATE(73)] = 785,
  [SMALL_STATE(74)] = 789,
  [SMALL_STATE(75)] = 793,
  [SMALL_STATE(76)] = 797,
  [SMALL_STATE(77)] = 801,
  [SMALL_STATE(78)] = 805,
  [SMALL_STATE(79)] = 809,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [29] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(31),
  [32] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(24),
  [35] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(24),
  [38] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(27),
  [41] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [55] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(39),
  [58] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(20),
  [61] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_arg_list_repeat1, 2), SHIFT_REPEAT(66),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 2),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 8),
  [70] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 7),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_integer_literal, 1),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_params, 2),
  [80] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_constructor, 4),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_typed_arg, 3),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_param, 1),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_list, 2),
  [90] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_list, 1),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 3),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 1),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_params, 1),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_op, 1),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [112] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim_call, 4),
  [122] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [124] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_op, 1),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim, 1),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arg_list_repeat1, 2),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim_call, 5),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_call, 6),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [166] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_call, 7),
  [168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [174] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_call, 9),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_call, 10),
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
