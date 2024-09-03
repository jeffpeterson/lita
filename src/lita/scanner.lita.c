// clang-format off
// lita -c src/lita/scanner.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

static ValueArray constants_reset_scanner_1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("scanner"), str("Scanner"), str("source"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_reset_scanner_1() {
  Chunk c;
  initChunk(&c);
  c.count = 13;
  c.capacity = 13;
  u8 code[] = {
    OP_GET_GLOBAL, 1,
    OP_GET_GLOBAL, 0,
    OP_GET_PROPERTY, 2,
    OP_CALL, 1,
    OP_SET_GLOBAL, 0,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 6,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_reset_scanner_1();

  return c;
};

             // reset_scanner
static Value fn_reset_scanner_1() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("reset_scanner");
  f->chunk = chunk_reset_scanner_1();
  return obj(f);
}

static ValueArray constants_init_2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("type"), str("escaped"), str("source"), str("line"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_init_2() {
  Chunk c;
  initChunk(&c);
  c.count = 31;
  c.capacity = 31;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_SET_PROPERTY, 0,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 2,
    OP_SET_PROPERTY, 1,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 3,
    OP_SET_PROPERTY, 2,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 4,
    OP_SET_PROPERTY, 3,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
  };
  int lines[] = {
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_init_2();

  return c;
};

             // init
static Value fn_init_2() {
  ObjFun *f = newFunction();  f->arity = 4;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->chunk = chunk_init_2();
  return obj(f);
}

static ValueArray constants_previous_3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    NUMBER_VAL(0.000000),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_previous_3() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_SET_PROPERTY, 8,
    OP_RETURN,
  };
  int lines[] = {
    13, 13, 13, 13, 13,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_previous_3();

  return c;
};

             // previous
static Value fn_previous_3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("previous");
  f->chunk = chunk_previous_3();
  return obj(f);
}

static ValueArray constants_current_4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    NUMBER_VAL(0.000000),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_current_4() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_SET_PROPERTY, 10,
    OP_RETURN,
  };
  int lines[] = {
    14, 14, 14, 14, 14,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_current_4();

  return c;
};

             // current
static Value fn_current_4() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("current");
  f->chunk = chunk_current_4();
  return obj(f);
}

static ValueArray constants_inside_5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_inside_5() {
  Chunk c;
  initChunk(&c);
  c.count = 4;
  c.capacity = 4;
  u8 code[] = {
    OP_TRUE,
    OP_SET_PROPERTY, 12,
    OP_RETURN,
  };
  int lines[] = {
    15, 15, 15, 15,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_inside_5();

  return c;
};

             // inside
static Value fn_inside_5() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inside");
  f->chunk = chunk_inside_5();
  return obj(f);
}

static ValueArray constants_position_6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    NUMBER_VAL(0.000000),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_position_6() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_CONSTANT, 0,
    OP_RANGE,
    OP_SET_PROPERTY, 15,
    OP_RETURN,
  };
  int lines[] = {
    19, 19, 19, 19, 19, 19, 19, 19,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_position_6();

  return c;
};

             // position
static Value fn_position_6() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("position");
  f->chunk = chunk_position_6();
  return obj(f);
}

static ValueArray constants_line_7() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    NUMBER_VAL(1.000000),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_line_7() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_SET_PROPERTY, 17,
    OP_RETURN,
  };
  int lines[] = {
    20, 20, 20, 20, 20,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_line_7();

  return c;
};

             // line
static Value fn_line_7() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("line");
  f->chunk = chunk_line_7();
  return obj(f);
}

static ValueArray constants_indent_8() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("Indent"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_indent_8() {
  Chunk c;
  initChunk(&c);
  c.count = 9;
  c.capacity = 9;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CALL, 0,
    OP_SET_PROPERTY, 19,
    OP_RETURN,
  };
  int lines[] = {
    21, 21, 21, 21, 21, 21, 21, 21, 21,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_indent_8();

  return c;
};

             // indent
static Value fn_indent_8() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("indent");
  f->chunk = chunk_indent_8();
  return obj(f);
}

static ValueArray constants_init_9() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("source"), str("skip_shebang"), str("skip_whitespace"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_init_9() {
  Chunk c;
  initChunk(&c);
  c.count = 20;
  c.capacity = 20;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_SET_VAR, 0,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
  };
  int lines[] = {
    25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 29, 29, 29,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_init_9();

  return c;
};

             // init
static Value fn_init_9() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->chunk = chunk_init_9();
  return obj(f);
}

static ValueArray constants_current_10() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("source"), str("span"), str("end"), NUMBER_VAL(1.000000),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_current_10() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_PROPERTY, 2,
    OP_ARRAY, 3,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_current_10();

  return c;
};

             // current
static Value fn_current_10() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("current");
  f->chunk = chunk_current_10();
  return obj(f);
}

static ValueArray constants_is_at_end_11() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    str("position"), str("start"), str("end"), str("source"), str("length"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_is_at_end_11() {
  Chunk c;
  initChunk(&c);
  c.count = 24;
  c.capacity = 24;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_PROPERTY, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_PROPERTY, 2,
    OP_ADD,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 3,
    OP_GET_PROPERTY, 4,
    OP_LESS,
    OP_NOT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_is_at_end_11();

  return c;
};

             // is_at_end
static Value fn_is_at_end_11() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("is_at_end");
  f->chunk = chunk_is_at_end_11();
  return obj(f);
}

static ValueArray constants_isAlpha_12() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 6;
  Value values[] = {
    str("in"), str("a"), str("z"), str("A"), str("Z"), str("_'"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_isAlpha_12() {
  Chunk c;
  initChunk(&c);
  c.count = 43;
  c.capacity = 43;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_RANGE,
    OP_INVOKE, 0, 1,
    OP_JUMP_IF_FALSE, 0, 3,
    OP_JUMP, 0, 12,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 0,
    OP_CONSTANT, 3,
    OP_CONSTANT, 4,
    OP_RANGE,
    OP_CALL, 1,
    OP_JUMP_IF_FALSE, 0, 3,
    OP_JUMP, 0, 6,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_CONSTANT, 5,
    OP_EQUAL,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_isAlpha_12();

  return c;
};

             // isAlpha
static Value fn_isAlpha_12() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("isAlpha");
  f->chunk = chunk_isAlpha_12();
  return obj(f);
}

static ValueArray constants_isDigit_13() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("in"), str("0"), str("9"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_isDigit_13() {
  Chunk c;
  initChunk(&c);
  c.count = 14;
  c.capacity = 14;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_RANGE,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_isDigit_13();

  return c;
};

             // isDigit
static Value fn_isDigit_13() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("isDigit");
  f->chunk = chunk_isDigit_13();
  return obj(f);
}

static ValueArray constants_isSubscript_14() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("in"), NUMBER_VAL(8320.000000), NUMBER_VAL(8329.000000),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_isSubscript_14() {
  Chunk c;
  initChunk(&c);
  c.count = 14;
  c.capacity = 14;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_RANGE,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 54, 54,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_isSubscript_14();

  return c;
};

             // isSubscript
static Value fn_isSubscript_14() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("isSubscript");
  f->chunk = chunk_isSubscript_14();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_scanner_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 32;
  Value values[] = {
    str("scanner"), str("reset_scanner"), fn_reset_scanner_1(), str("Token"), fn_init_2(), str("init"), str("Object"), str("Indent"), str("previous"), fn_previous_3(), str("current"), fn_current_4(), str("inside"), fn_inside_5(), str("Scanner"), str("position"), fn_position_6(), str("line"), fn_line_7(), str("indent"), fn_indent_8(), fn_init_9(), fn_current_10(), str("is_at_end"), fn_is_at_end_11(), str("isAlpha"), fn_isAlpha_12(), str("isDigit"), fn_isDigit_13(), str("isSubscript"), fn_isSubscript_14(), str("script return value"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_scanner_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 99;
  c.capacity = 99;
  u8 code[] = {
    OP_NIL,
    OP_DEFINE_GLOBAL, 0,
    OP_CLOSURE, 2,
    OP_DEFINE_GLOBAL, 1,
    OP_CLASS, 3, 0,
    OP_CLOSURE, 4,
    OP_METHOD, 5,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 7, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 9,
    OP_METHOD, 8,
    OP_CLOSURE, 11,
    OP_METHOD, 10,
    OP_CLOSURE, 13,
    OP_METHOD, 12,
    OP_POP,
    OP_POP,
    OP_CLASS, 14, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 16,
    OP_METHOD, 15,
    OP_CLOSURE, 18,
    OP_METHOD, 17,
    OP_CLOSURE, 20,
    OP_METHOD, 19,
    OP_CLOSURE, 21,
    OP_METHOD, 5,
    OP_CLOSURE, 22,
    OP_METHOD, 10,
    OP_CLOSURE, 24,
    OP_METHOD, 23,
    OP_POP,
    OP_POP,
    OP_CLOSURE, 26,
    OP_DEFINE_GLOBAL, 25,
    OP_CLOSURE, 28,
    OP_DEFINE_GLOBAL, 27,
    OP_CLOSURE, 30,
    OP_DEFINE_GLOBAL, 29,
    OP_ASSERT_STACK, 31, 2,
    OP_RETURN,
  };
  int lines[] = {
    1, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 54, 54, 54, 54, 54, 54, 54, 54,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_scanner_dot_lita_0();

  return c;
};

             // src/lita/scanner.lita
static Value fn_src_slash_lita_slash_scanner_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/scanner.lita");
  f->chunk = chunk_src_slash_lita_slash_scanner_dot_lita_0();
  return obj(f);
}

ObjFun *scanner_lita() {
  return AS_FUN(fn_src_slash_lita_slash_scanner_dot_lita_0());
}
