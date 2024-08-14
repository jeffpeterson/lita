// clang-format off
// lita -c src/lita/lib/core.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

static ValueArray constants_string_1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str(""),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_string_1() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    0, 0, 40, 1, 40,
  };
  int lines[] = {
    2, 2, 2, 3, 3,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_string_1();

  return c;
};

             // string
static Value fn_string_1() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("string");
  f->chunk = chunk_string_1();
  return obj(f);
}

static ValueArray constants_dump_2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("nil"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dump_2() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    0, 0, 40, 1, 40,
  };
  int lines[] = {
    3, 3, 3, 3, 3,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dump_2();

  return c;
};

             // dump
static Value fn_dump_2() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("dump");
  f->chunk = chunk_dump_2();
  return obj(f);
}

static ValueArray constants_dump_3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    str("/*"), str("name"), str("*/fn"), str("id"), str("()"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dump_3() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    0, 0, 14, 0, 44, 1, 0, 2, 14, 0, 44, 3, 0, 4, 33, 4, 40, 1, 40,
  };
  int lines[] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dump_3();

  return c;
};

             // dump
static Value fn_dump_3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("dump");
  f->chunk = chunk_dump_3();
  return obj(f);
}

static ValueArray constants_dump_global_4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 11;
  Value values[] = {
    str("\n"), str("// "), str("name"), str("static ValueArray constants"), str("id"), str("() {\n"), str("  ValueArray vals;\n"), str("  initValueArray(&vals);\n"), str("  vals.count = vals.capacity = "), str(";\n"), str("  Value values[] = {"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dump_global_4() {
  Chunk c;
  initChunk(&c);
  c.count = 43;
  c.capacity = 43;
  u8 code[] = {
    0, 0, 7, 0, 1, 14, 0, 44, 2, 0, 0, 33, 2, 7, 0, 3, 14, 0, 44, 4, 0, 5, 33, 2, 7, 0, 6, 7, 0, 7, 7, 0, 8, 0, 9, 33, 1, 7, 0, 10, 7, 1, 40,
  };
  int lines[] = {
    17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 25, 25,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dump_global_4();

  return c;
};

             // dump_global
static Value fn_dump_global_4() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("dump_global");
  f->chunk = chunk_dump_global_4();
  return obj(f);
}

static ValueArray constants_inspect_5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("true"), str("false"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_inspect_5() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 31, 0, 6, 7, 0, 0, 30, 0, 3, 7, 0, 1, 40, 1, 40,
  };
  int lines[] = {
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_inspect_5();

  return c;
};

             // inspect
static Value fn_inspect_5() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("inspect");
  f->chunk = chunk_inspect_5();
  return obj(f);
}

static ValueArray constants_string_6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("inspect"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_string_6() {
  Chunk c;
  initChunk(&c);
  c.count = 7;
  c.capacity = 7;
  u8 code[] = {
    14, 0, 44, 0, 40, 1, 40,
  };
  int lines[] = {
    31, 31, 31, 31, 31, 32, 32,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_string_6();

  return c;
};

             // string
static Value fn_string_6() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("string");
  f->chunk = chunk_string_6();
  return obj(f);
}

static ValueArray constants_dump_7() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("TRUE_VAL"), str("FALSE_VAL"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dump_7() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 31, 0, 6, 7, 0, 0, 30, 0, 3, 7, 0, 1, 40, 1, 40,
  };
  int lines[] = {
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dump_7();

  return c;
};

             // dump
static Value fn_dump_7() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("dump");
  f->chunk = chunk_dump_7();
  return obj(f);
}

static ValueArray constants_dump_8() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("NUMBER_VAL("), str("string"), str(")"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dump_8() {
  Chunk c;
  initChunk(&c);
  c.count = 13;
  c.capacity = 13;
  u8 code[] = {
    0, 0, 14, 0, 44, 1, 0, 2, 33, 2, 40, 1, 40,
  };
  int lines[] = {
    35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dump_8();

  return c;
};

             // dump
static Value fn_dump_8() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("dump");
  f->chunk = chunk_dump_8();
  return obj(f);
}

static ValueArray constants_inspect_9() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("{"), str("}"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_inspect_9() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    0, 0, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    38, 38, 38, 38, 38, 38, 38, 38,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_inspect_9();

  return c;
};

             // inspect
static Value fn_inspect_9() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("inspect");
  f->chunk = chunk_inspect_9();
  return obj(f);
}

static ValueArray constants_init_10() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("type"), str("value"), str("targets"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_init_10() {
  Chunk c;
  initChunk(&c);
  c.count = 24;
  c.capacity = 24;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 14, 3, 17, 2, 7, 14, 0, 40,
  };
  int lines[] = {
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_init_10();

  return c;
};

             // init
static Value fn_init_10() {
  ObjFun *f = newFunction();  f->arity = 3;
  f->upvalueCount = 0;
  f->name = new_string("init");
  f->chunk = chunk_init_10();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_lib_slash_core_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 28;
  Value values[] = {
    str("Nil"), str("Any"), str("string"), fn_string_1(), str("dump"), fn_dump_2(), str("Object"), str("fn_id"), NUMBER_VAL(0.000000), str("Function"), fn_dump_3(), str("dump_global"), fn_dump_global_4(), str("Method"), str("NativeFunction"), str("Class"), str("Bool"), str("inspect"), fn_inspect_5(), fn_string_6(), fn_dump_7(), str("Number"), fn_dump_8(), str("Table"), fn_inspect_9(), str("Atom"), fn_init_10(), str("init"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_lib_slash_core_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 166;
  c.capacity = 166;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 37, 5, 36, 4, 7, 7, 34, 6, 0, 14, 0, 44, 1, 35, 9, 1, 7, 7, 0, 8, 11, 7, 34, 9, 0, 14, 0, 44, 6, 35, 9, 1, 37, 10, 36, 4, 37, 12, 36, 11, 7, 7, 34, 13, 0, 14, 0, 44, 9, 35, 9, 1, 7, 7, 34, 14, 0, 14, 0, 44, 9, 35, 9, 1, 7, 7, 34, 15, 0, 14, 0, 44, 9, 35, 9, 1, 7, 7, 34, 16, 0, 14, 0, 44, 6, 35, 9, 1, 37, 18, 36, 17, 37, 19, 36, 2, 37, 20, 36, 4, 7, 7, 34, 21, 0, 14, 0, 44, 6, 35, 9, 1, 37, 22, 36, 4, 7, 7, 34, 23, 0, 14, 0, 44, 6, 35, 9, 1, 37, 24, 36, 17, 7, 7, 34, 25, 0, 37, 26, 36, 27, 14, 0, 44, 6, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 16, 16, 16, 16, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_lib_slash_core_dot_lita_0();

  return c;
};

             // src/lita/lib/core.lita
static Value fn_src_slash_lita_slash_lib_slash_core_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src/lita/lib/core.lita");
  f->chunk = chunk_src_slash_lita_slash_lib_slash_core_dot_lita_0();
  return obj(f);
}

ObjFun *core_lita() {
  return AS_FUN(fn_src_slash_lita_slash_lib_slash_core_dot_lita_0());
}
