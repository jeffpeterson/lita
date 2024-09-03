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
    12, 1, 12, 0, 16, 2, 33, 1, 13, 0, 7, 1, 40,
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
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 14, 3, 17, 2, 7, 14, 0, 14, 4, 17, 3, 7, 14, 0, 40,
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
    0, 0, 17, 8, 40,
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
    0, 0, 17, 10, 40,
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
    2, 17, 12, 40,
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
    0, 0, 0, 0, 4, 17, 15, 40,
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
    0, 0, 17, 17, 40,
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
    14, 0, 44, 0, 33, 0, 17, 19, 40,
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
    14, 0, 14, 1, 45, 0, 7, 14, 0, 44, 1, 7, 14, 0, 44, 2, 7, 14, 0, 40,
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
    14, 0, 44, 0, 14, 0, 44, 1, 16, 2, 46, 3, 33, 1, 40, 1, 40,
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
    14, 0, 44, 0, 16, 1, 14, 0, 44, 0, 16, 2, 24, 14, 0, 44, 3, 16, 4, 23, 28, 40, 1, 40,
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

static ValueArray constants_is_alpha_12() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_is_alpha_12() {
  Chunk c;
  initChunk(&c);
  c.count = 2;
  c.capacity = 2;
  u8 code[] = {
    1, 40,
  };
  int lines[] = {
    32, 32,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_is_alpha_12();

  return c;
};

             // is_alpha
static Value fn_is_alpha_12() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("is_alpha");
  f->chunk = chunk_is_alpha_12();
  return obj(f);
}

static ValueArray constants_is_digit_13() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("in"), str("0"), str("9"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_is_digit_13() {
  Chunk c;
  initChunk(&c);
  c.count = 14;
  c.capacity = 14;
  u8 code[] = {
    14, 1, 16, 0, 0, 1, 0, 2, 4, 33, 1, 40, 1, 40,
  };
  int lines[] = {
    33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_is_digit_13();

  return c;
};

             // is_digit
static Value fn_is_digit_13() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("is_digit");
  f->chunk = chunk_is_digit_13();
  return obj(f);
}

static ValueArray constants_is_subscript_14() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("in"), NUMBER_VAL(8320.000000), NUMBER_VAL(8329.000000),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_is_subscript_14() {
  Chunk c;
  initChunk(&c);
  c.count = 14;
  c.capacity = 14;
  u8 code[] = {
    14, 1, 16, 0, 0, 1, 0, 2, 4, 33, 1, 40, 1, 40,
  };
  int lines[] = {
    34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 54, 54,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_is_subscript_14();

  return c;
};

             // is_subscript
static Value fn_is_subscript_14() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("is_subscript");
  f->chunk = chunk_is_subscript_14();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_scanner_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 39;
  Value values[] = {
    str("scanner"), str("reset_scanner"), fn_reset_scanner_1(), str("Token"), fn_init_2(), str("init"), str("Object"), str("Indent"), str("previous"), fn_previous_3(), str("current"), fn_current_4(), str("inside"), fn_inside_5(), str("Scanner"), str("position"), fn_position_6(), str("line"), fn_line_7(), str("indent"), fn_indent_8(), fn_init_9(), fn_current_10(), str("is_at_end"), fn_is_at_end_11(), str("is_alpha"), fn_is_alpha_12(), str("c"), str("in"), str("a"), str("z"), str("A"), str("Z"), str("_'"), str("is_digit"), fn_is_digit_13(), str("is_subscript"), fn_is_subscript_14(), str("script return value"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_scanner_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 143;
  c.capacity = 143;
  u8 code[] = {
    1, 11, 0, 37, 2, 11, 1, 34, 3, 0, 37, 4, 36, 5, 14, 0, 44, 6, 35, 9, 1, 7, 7, 34, 7, 0, 14, 0, 44, 6, 35, 9, 1, 37, 9, 36, 8, 37, 11, 36, 10, 37, 13, 36, 12, 7, 7, 34, 14, 0, 14, 0, 44, 6, 35, 9, 1, 37, 16, 36, 15, 37, 18, 36, 17, 37, 20, 36, 19, 37, 21, 36, 5, 37, 22, 36, 10, 37, 24, 36, 23, 7, 7, 37, 26, 11, 25, 12, 27, 16, 28, 0, 29, 0, 30, 4, 33, 1, 13, 27, 31, 0, 3, 30, 0, 12, 7, 12, 27, 16, 28, 0, 31, 0, 32, 4, 33, 1, 31, 0, 3, 30, 0, 6, 7, 12, 27, 0, 33, 21, 7, 37, 35, 11, 34, 37, 37, 11, 36, 49, 38, 2, 40,
  };
  int lines[] = {
    1, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 34, 54, 54, 54, 54, 54, 54, 54, 54,
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
