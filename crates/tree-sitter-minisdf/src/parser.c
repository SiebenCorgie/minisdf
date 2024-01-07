#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 82
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 52
#define ALIAS_COUNT 0
#define TOKEN_COUNT 31
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
  anon_sym_repeat_in = 15,
  anon_sym_smooth = 16,
  anon_sym_union = 17,
  anon_sym_smooth_union = 18,
  anon_sym_sub = 19,
  anon_sym_smooth_sub = 20,
  anon_sym_inter = 21,
  anon_sym_smooth_inter = 22,
  anon_sym_DASH = 23,
  anon_sym_DOT = 24,
  anon_sym_float = 25,
  anon_sym_vec2 = 26,
  anon_sym_vec3 = 27,
  anon_sym_vec4 = 28,
  sym_digit = 29,
  sym_comment = 30,
  sym_source_file = 31,
  sym_field_decl = 32,
  sym_arg_list = 33,
  sym_typed_arg = 34,
  sym__field_tree = 35,
  sym_unary_call = 36,
  sym_binary_call = 37,
  sym_prim_call = 38,
  sym_call_params = 39,
  sym_param = 40,
  sym_type_constructor = 41,
  sym_prim = 42,
  sym_unary_op = 43,
  sym_binary_op = 44,
  sym_literal = 45,
  sym_integer_literal = 46,
  sym_float_literal = 47,
  sym_type = 48,
  aux_sym_source_file_repeat1 = 49,
  aux_sym_arg_list_repeat1 = 50,
  aux_sym_call_params_repeat1 = 51,
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
  [anon_sym_repeat_in] = "repeat_in",
  [anon_sym_smooth] = "smooth",
  [anon_sym_union] = "union",
  [anon_sym_smooth_union] = "smooth_union",
  [anon_sym_sub] = "sub",
  [anon_sym_smooth_sub] = "smooth_sub",
  [anon_sym_inter] = "inter",
  [anon_sym_smooth_inter] = "smooth_inter",
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
  [anon_sym_repeat_in] = anon_sym_repeat_in,
  [anon_sym_smooth] = anon_sym_smooth,
  [anon_sym_union] = anon_sym_union,
  [anon_sym_smooth_union] = anon_sym_smooth_union,
  [anon_sym_sub] = anon_sym_sub,
  [anon_sym_smooth_sub] = anon_sym_smooth_sub,
  [anon_sym_inter] = anon_sym_inter,
  [anon_sym_smooth_inter] = anon_sym_smooth_inter,
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
  [anon_sym_repeat_in] = {
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
  [anon_sym_smooth_union] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sub] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_smooth_sub] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_inter] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_smooth_inter] = {
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
      if (lookahead == '_') ADVANCE(57);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_smooth);
      if (lookahead == '_') ADVANCE(58);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_sphere);
      END_STATE();
    case 56:
      if (lookahead == 'a') ADVANCE(59);
      END_STATE();
    case 57:
      if (lookahead == 'i') ADVANCE(60);
      END_STATE();
    case 58:
      if (lookahead == 'i') ADVANCE(61);
      if (lookahead == 's') ADVANCE(62);
      if (lookahead == 'u') ADVANCE(63);
      END_STATE();
    case 59:
      if (lookahead == 't') ADVANCE(64);
      END_STATE();
    case 60:
      if (lookahead == 'n') ADVANCE(65);
      END_STATE();
    case 61:
      if (lookahead == 'n') ADVANCE(66);
      END_STATE();
    case 62:
      if (lookahead == 'u') ADVANCE(67);
      END_STATE();
    case 63:
      if (lookahead == 'n') ADVANCE(68);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(69);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_repeat_in);
      END_STATE();
    case 66:
      if (lookahead == 't') ADVANCE(70);
      END_STATE();
    case 67:
      if (lookahead == 'b') ADVANCE(71);
      END_STATE();
    case 68:
      if (lookahead == 'i') ADVANCE(72);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_translate);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(73);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_smooth_sub);
      END_STATE();
    case 72:
      if (lookahead == 'o') ADVANCE(74);
      END_STATE();
    case 73:
      if (lookahead == 'r') ADVANCE(75);
      END_STATE();
    case 74:
      if (lookahead == 'n') ADVANCE(76);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_smooth_inter);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_smooth_union);
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
    [anon_sym_repeat_in] = ACTIONS(1),
    [anon_sym_smooth] = ACTIONS(1),
    [anon_sym_union] = ACTIONS(1),
    [anon_sym_smooth_union] = ACTIONS(1),
    [anon_sym_sub] = ACTIONS(1),
    [anon_sym_smooth_sub] = ACTIONS(1),
    [anon_sym_inter] = ACTIONS(1),
    [anon_sym_smooth_inter] = ACTIONS(1),
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
  [0] = 8,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 2,
      anon_sym_translate,
      anon_sym_repeat_in,
    ACTIONS(13), 2,
      anon_sym_repeat,
      anon_sym_smooth,
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
    ACTIONS(15), 6,
      anon_sym_union,
      anon_sym_smooth_union,
      anon_sym_sub,
      anon_sym_smooth_sub,
      anon_sym_inter,
      anon_sym_smooth_inter,
  [38] = 8,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 2,
      anon_sym_translate,
      anon_sym_repeat_in,
    ACTIONS(13), 2,
      anon_sym_repeat,
      anon_sym_smooth,
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
    ACTIONS(15), 6,
      anon_sym_union,
      anon_sym_smooth_union,
      anon_sym_sub,
      anon_sym_smooth_sub,
      anon_sym_inter,
      anon_sym_smooth_inter,
  [76] = 8,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 2,
      anon_sym_translate,
      anon_sym_repeat_in,
    ACTIONS(13), 2,
      anon_sym_repeat,
      anon_sym_smooth,
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
    ACTIONS(15), 6,
      anon_sym_union,
      anon_sym_smooth_union,
      anon_sym_sub,
      anon_sym_smooth_sub,
      anon_sym_inter,
      anon_sym_smooth_inter,
  [114] = 8,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 2,
      anon_sym_translate,
      anon_sym_repeat_in,
    ACTIONS(13), 2,
      anon_sym_repeat,
      anon_sym_smooth,
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
    ACTIONS(15), 6,
      anon_sym_union,
      anon_sym_smooth_union,
      anon_sym_sub,
      anon_sym_smooth_sub,
      anon_sym_inter,
      anon_sym_smooth_inter,
  [152] = 8,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 2,
      anon_sym_translate,
      anon_sym_repeat_in,
    ACTIONS(13), 2,
      anon_sym_repeat,
      anon_sym_smooth,
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
    ACTIONS(15), 6,
      anon_sym_union,
      anon_sym_smooth_union,
      anon_sym_sub,
      anon_sym_smooth_sub,
      anon_sym_inter,
      anon_sym_smooth_inter,
  [190] = 8,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 2,
      anon_sym_translate,
      anon_sym_repeat_in,
    ACTIONS(13), 2,
      anon_sym_repeat,
      anon_sym_smooth,
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
    ACTIONS(15), 6,
      anon_sym_union,
      anon_sym_smooth_union,
      anon_sym_sub,
      anon_sym_smooth_sub,
      anon_sym_inter,
      anon_sym_smooth_inter,
  [228] = 8,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 2,
      anon_sym_translate,
      anon_sym_repeat_in,
    ACTIONS(13), 2,
      anon_sym_repeat,
      anon_sym_smooth,
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
    ACTIONS(15), 6,
      anon_sym_union,
      anon_sym_smooth_union,
      anon_sym_sub,
      anon_sym_smooth_sub,
      anon_sym_inter,
      anon_sym_smooth_inter,
  [266] = 8,
    STATE(43), 1,
      sym_prim,
    STATE(54), 1,
      sym_unary_op,
    STATE(69), 1,
      sym_binary_op,
    ACTIONS(11), 2,
      anon_sym_translate,
      anon_sym_repeat_in,
    ACTIONS(13), 2,
      anon_sym_repeat,
      anon_sym_smooth,
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
    ACTIONS(15), 6,
      anon_sym_union,
      anon_sym_smooth_union,
      anon_sym_sub,
      anon_sym_smooth_sub,
      anon_sym_inter,
      anon_sym_smooth_inter,
  [304] = 12,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(19), 1,
      anon_sym_RPAREN,
    ACTIONS(21), 1,
      anon_sym_DASH,
    ACTIONS(23), 1,
      anon_sym_float,
    ACTIONS(27), 1,
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
    ACTIONS(25), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [345] = 12,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(21), 1,
      anon_sym_DASH,
    ACTIONS(23), 1,
      anon_sym_float,
    ACTIONS(27), 1,
      sym_digit,
    ACTIONS(29), 1,
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
    ACTIONS(25), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [386] = 12,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(21), 1,
      anon_sym_DASH,
    ACTIONS(23), 1,
      anon_sym_float,
    ACTIONS(27), 1,
      sym_digit,
    ACTIONS(31), 1,
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
    ACTIONS(25), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [427] = 11,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(21), 1,
      anon_sym_DASH,
    ACTIONS(23), 1,
      anon_sym_float,
    ACTIONS(27), 1,
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
    ACTIONS(25), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [465] = 10,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(21), 1,
      anon_sym_DASH,
    ACTIONS(23), 1,
      anon_sym_float,
    ACTIONS(27), 1,
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
    ACTIONS(25), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [500] = 10,
    ACTIONS(33), 1,
      sym_identifier,
    ACTIONS(36), 1,
      anon_sym_DASH,
    ACTIONS(39), 1,
      anon_sym_float,
    ACTIONS(45), 1,
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
    ACTIONS(42), 3,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [535] = 2,
    ACTIONS(48), 2,
      anon_sym_float,
      sym_identifier,
    ACTIONS(50), 5,
      anon_sym_DASH,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
      sym_digit,
  [547] = 2,
    STATE(33), 1,
      sym_type,
    ACTIONS(25), 4,
      anon_sym_float,
      anon_sym_vec2,
      anon_sym_vec3,
      anon_sym_vec4,
  [557] = 4,
    ACTIONS(5), 1,
      anon_sym_field,
    ACTIONS(52), 1,
      ts_builtin_sym_end,
    ACTIONS(54), 1,
      sym_comment,
    STATE(20), 2,
      sym_field_decl,
      aux_sym_source_file_repeat1,
  [571] = 5,
    ACTIONS(56), 1,
      sym_identifier,
    ACTIONS(58), 1,
      anon_sym_RPAREN,
    STATE(26), 1,
      aux_sym_arg_list_repeat1,
    STATE(34), 1,
      sym_typed_arg,
    STATE(61), 1,
      sym_arg_list,
  [587] = 4,
    ACTIONS(60), 1,
      ts_builtin_sym_end,
    ACTIONS(62), 1,
      anon_sym_field,
    ACTIONS(65), 1,
      sym_comment,
    STATE(20), 2,
      sym_field_decl,
      aux_sym_source_file_repeat1,
  [601] = 3,
    ACTIONS(68), 1,
      sym_identifier,
    STATE(21), 1,
      aux_sym_arg_list_repeat1,
    STATE(68), 1,
      sym_typed_arg,
  [611] = 2,
    ACTIONS(73), 1,
      sym_digit,
    ACTIONS(71), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [619] = 1,
    ACTIONS(75), 3,
      ts_builtin_sym_end,
      anon_sym_field,
      sym_comment,
  [625] = 2,
    ACTIONS(79), 1,
      anon_sym_DOT,
    ACTIONS(77), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [633] = 1,
    ACTIONS(81), 3,
      ts_builtin_sym_end,
      anon_sym_field,
      sym_comment,
  [639] = 3,
    ACTIONS(56), 1,
      sym_identifier,
    STATE(21), 1,
      aux_sym_arg_list_repeat1,
    STATE(35), 1,
      sym_typed_arg,
  [649] = 2,
    ACTIONS(85), 1,
      sym_digit,
    ACTIONS(83), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [657] = 1,
    ACTIONS(87), 3,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [663] = 1,
    ACTIONS(83), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [668] = 1,
    ACTIONS(89), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [673] = 1,
    ACTIONS(91), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [678] = 1,
    ACTIONS(93), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [683] = 1,
    ACTIONS(95), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [688] = 2,
    ACTIONS(97), 1,
      anon_sym_RPAREN,
    ACTIONS(99), 1,
      anon_sym_COMMA,
  [695] = 2,
    ACTIONS(99), 1,
      anon_sym_COMMA,
    ACTIONS(101), 1,
      anon_sym_RPAREN,
  [702] = 2,
    ACTIONS(103), 1,
      anon_sym_RPAREN,
    ACTIONS(105), 1,
      anon_sym_COMMA,
  [709] = 2,
    ACTIONS(105), 1,
      anon_sym_COMMA,
    ACTIONS(107), 1,
      anon_sym_RPAREN,
  [716] = 1,
    ACTIONS(109), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [721] = 1,
    ACTIONS(111), 1,
      sym_identifier,
  [725] = 1,
    ACTIONS(113), 1,
      anon_sym_RBRACE,
  [729] = 1,
    ACTIONS(115), 1,
      anon_sym_RPAREN,
  [733] = 1,
    ACTIONS(117), 1,
      anon_sym_LPAREN,
  [737] = 1,
    ACTIONS(119), 1,
      anon_sym_LPAREN,
  [741] = 1,
    ACTIONS(121), 1,
      anon_sym_LBRACE,
  [745] = 1,
    ACTIONS(123), 1,
      anon_sym_RPAREN,
  [749] = 1,
    ACTIONS(125), 1,
      anon_sym_LBRACE,
  [753] = 1,
    ACTIONS(127), 1,
      anon_sym_RPAREN,
  [757] = 1,
    ACTIONS(129), 1,
      anon_sym_RBRACE,
  [761] = 1,
    ACTIONS(131), 1,
      anon_sym_DOT,
  [765] = 1,
    ACTIONS(133), 1,
      anon_sym_LPAREN,
  [769] = 1,
    ACTIONS(135), 1,
      anon_sym_RBRACE,
  [773] = 1,
    ACTIONS(137), 1,
      anon_sym_LPAREN,
  [777] = 1,
    ACTIONS(139), 1,
      anon_sym_LPAREN,
  [781] = 1,
    ACTIONS(141), 1,
      anon_sym_LPAREN,
  [785] = 1,
    ACTIONS(143), 1,
      anon_sym_RBRACE,
  [789] = 1,
    ACTIONS(145), 1,
      sym_identifier,
  [793] = 1,
    ACTIONS(147), 1,
      anon_sym_LBRACE,
  [797] = 1,
    ACTIONS(149), 1,
      anon_sym_LBRACE,
  [801] = 1,
    ACTIONS(151), 1,
      anon_sym_LBRACE,
  [805] = 1,
    ACTIONS(153), 1,
      sym_digit,
  [809] = 1,
    ACTIONS(155), 1,
      anon_sym_RPAREN,
  [813] = 1,
    ACTIONS(157), 1,
      anon_sym_RPAREN,
  [817] = 1,
    ACTIONS(105), 1,
      anon_sym_COMMA,
  [821] = 1,
    ACTIONS(159), 1,
      anon_sym_RBRACE,
  [825] = 1,
    ACTIONS(161), 1,
      anon_sym_COLON,
  [829] = 1,
    ACTIONS(163), 1,
      anon_sym_RBRACE,
  [833] = 1,
    ACTIONS(165), 1,
      anon_sym_LBRACE,
  [837] = 1,
    ACTIONS(99), 1,
      anon_sym_COMMA,
  [841] = 1,
    ACTIONS(167), 1,
      anon_sym_LPAREN,
  [845] = 1,
    ACTIONS(169), 1,
      anon_sym_RBRACE,
  [849] = 1,
    ACTIONS(171), 1,
      anon_sym_RBRACE,
  [853] = 1,
    ACTIONS(173), 1,
      anon_sym_LBRACE,
  [857] = 1,
    ACTIONS(175), 1,
      anon_sym_RBRACE,
  [861] = 1,
    ACTIONS(177), 1,
      anon_sym_RBRACE,
  [865] = 1,
    ACTIONS(179), 1,
      anon_sym_LPAREN,
  [869] = 1,
    ACTIONS(181), 1,
      anon_sym_LBRACE,
  [873] = 1,
    ACTIONS(183), 1,
      anon_sym_RBRACE,
  [877] = 1,
    ACTIONS(185), 1,
      ts_builtin_sym_end,
  [881] = 1,
    ACTIONS(187), 1,
      anon_sym_RBRACE,
  [885] = 1,
    ACTIONS(189), 1,
      anon_sym_RBRACE,
  [889] = 1,
    ACTIONS(191), 1,
      anon_sym_RBRACE,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 38,
  [SMALL_STATE(4)] = 76,
  [SMALL_STATE(5)] = 114,
  [SMALL_STATE(6)] = 152,
  [SMALL_STATE(7)] = 190,
  [SMALL_STATE(8)] = 228,
  [SMALL_STATE(9)] = 266,
  [SMALL_STATE(10)] = 304,
  [SMALL_STATE(11)] = 345,
  [SMALL_STATE(12)] = 386,
  [SMALL_STATE(13)] = 427,
  [SMALL_STATE(14)] = 465,
  [SMALL_STATE(15)] = 500,
  [SMALL_STATE(16)] = 535,
  [SMALL_STATE(17)] = 547,
  [SMALL_STATE(18)] = 557,
  [SMALL_STATE(19)] = 571,
  [SMALL_STATE(20)] = 587,
  [SMALL_STATE(21)] = 601,
  [SMALL_STATE(22)] = 611,
  [SMALL_STATE(23)] = 619,
  [SMALL_STATE(24)] = 625,
  [SMALL_STATE(25)] = 633,
  [SMALL_STATE(26)] = 639,
  [SMALL_STATE(27)] = 649,
  [SMALL_STATE(28)] = 657,
  [SMALL_STATE(29)] = 663,
  [SMALL_STATE(30)] = 668,
  [SMALL_STATE(31)] = 673,
  [SMALL_STATE(32)] = 678,
  [SMALL_STATE(33)] = 683,
  [SMALL_STATE(34)] = 688,
  [SMALL_STATE(35)] = 695,
  [SMALL_STATE(36)] = 702,
  [SMALL_STATE(37)] = 709,
  [SMALL_STATE(38)] = 716,
  [SMALL_STATE(39)] = 721,
  [SMALL_STATE(40)] = 725,
  [SMALL_STATE(41)] = 729,
  [SMALL_STATE(42)] = 733,
  [SMALL_STATE(43)] = 737,
  [SMALL_STATE(44)] = 741,
  [SMALL_STATE(45)] = 745,
  [SMALL_STATE(46)] = 749,
  [SMALL_STATE(47)] = 753,
  [SMALL_STATE(48)] = 757,
  [SMALL_STATE(49)] = 761,
  [SMALL_STATE(50)] = 765,
  [SMALL_STATE(51)] = 769,
  [SMALL_STATE(52)] = 773,
  [SMALL_STATE(53)] = 777,
  [SMALL_STATE(54)] = 781,
  [SMALL_STATE(55)] = 785,
  [SMALL_STATE(56)] = 789,
  [SMALL_STATE(57)] = 793,
  [SMALL_STATE(58)] = 797,
  [SMALL_STATE(59)] = 801,
  [SMALL_STATE(60)] = 805,
  [SMALL_STATE(61)] = 809,
  [SMALL_STATE(62)] = 813,
  [SMALL_STATE(63)] = 817,
  [SMALL_STATE(64)] = 821,
  [SMALL_STATE(65)] = 825,
  [SMALL_STATE(66)] = 829,
  [SMALL_STATE(67)] = 833,
  [SMALL_STATE(68)] = 837,
  [SMALL_STATE(69)] = 841,
  [SMALL_STATE(70)] = 845,
  [SMALL_STATE(71)] = 849,
  [SMALL_STATE(72)] = 853,
  [SMALL_STATE(73)] = 857,
  [SMALL_STATE(74)] = 861,
  [SMALL_STATE(75)] = 865,
  [SMALL_STATE(76)] = 869,
  [SMALL_STATE(77)] = 873,
  [SMALL_STATE(78)] = 877,
  [SMALL_STATE(79)] = 881,
  [SMALL_STATE(80)] = 885,
  [SMALL_STATE(81)] = 889,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [33] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(38),
  [36] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(60),
  [39] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(28),
  [42] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(28),
  [45] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2), SHIFT_REPEAT(24),
  [48] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_call_params_repeat1, 2),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_params_repeat1, 2),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [62] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(39),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(20),
  [68] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_arg_list_repeat1, 2), SHIFT_REPEAT(65),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 2),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 8),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_integer_literal, 1),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_decl, 7),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 3),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 1),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_constructor, 4),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 4),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_typed_arg, 3),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_list, 1),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_list, 2),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_params, 2),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_params, 1),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_param, 1),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [131] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_op, 1),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim_call, 4),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_op, 1),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim, 1),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prim_call, 3),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arg_list_repeat1, 2),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_call, 6),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_call, 7),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [185] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_call, 9),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [191] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_call, 10),
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
