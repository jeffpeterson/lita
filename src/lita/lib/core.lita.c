// clang-format off
// lita -c src/lita/lib/core.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

static ValueArray constants_string_1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    string(""),
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
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
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
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
  f->chunk = chunk_string_1();
  return obj(f);
}

static ValueArray constants_dump_2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    string("nil"),
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
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
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
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");
  f->chunk = chunk_dump_2();
  return obj(f);
}

static ValueArray constants_dump_3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    string("/*"), string("name"), string("*/fn"), string("id"), string("()"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dump_3() {
  Chunk c;
  initChunk(&c);
  c.count = 25;
  c.capacity = 25;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_CALL, 1,
    OP_CONSTANT, 2,
    OP_CALL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 3,
    OP_CALL, 1,
    OP_CONSTANT, 4,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dump_3();

  return c;
};

             // dump
static Value fn_dump_3() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");
  f->chunk = chunk_dump_3();
  return obj(f);
}

static ValueArray constants_dump_global_4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 11;
  Value values[] = {
    string("\n"), string("// "), string("name"), string("static ValueArray constants"), string("id"), string("() {\n"), string("  ValueArray vals;\n"), string("  initValueArray(&vals);\n"), string("  vals.count = vals.capacity = "), string(";\n"), string("  Value values[] = {"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dump_global_4() {
  Chunk c;
  initChunk(&c);
  c.count = 53;
  c.capacity = 53;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_CALL, 1,
    OP_CONSTANT, 0,
    OP_CALL, 1,
    OP_CONSTANT, 3,
    OP_CALL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 4,
    OP_CALL, 1,
    OP_CONSTANT, 5,
    OP_CALL, 1,
    OP_CONSTANT, 6,
    OP_CALL, 1,
    OP_CONSTANT, 7,
    OP_CALL, 1,
    OP_CONSTANT, 8,
    OP_CALL, 1,
    OP_CONSTANT, 9,
    OP_CALL, 1,
    OP_CONSTANT, 10,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dump_global_4();

  return c;
};

             // dump_global
static Value fn_dump_global_4() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump_global");
  f->chunk = chunk_dump_global_4();
  return obj(f);
}

static ValueArray constants_string_5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    string("true"), string("false"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_string_5() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_JUMP_IF_FALSE, 0, 6,
    OP_POP,
    OP_CONSTANT, 0,
    OP_JUMP, 0, 3,
    OP_POP,
    OP_CONSTANT, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_string_5();

  return c;
};

             // string
static Value fn_string_5() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
  f->chunk = chunk_string_5();
  return obj(f);
}

static ValueArray constants_print_6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    string("write"), string("string"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_print_6() {
  Chunk c;
  initChunk(&c);
  c.count = 12;
  c.capacity = 12;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_print_6();

  return c;
};

             // print
static Value fn_print_6() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");
  f->chunk = chunk_print_6();
  return obj(f);
}

static ValueArray constants_dump_7() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    string("TRUE_VAL"), string("FALSE_VAL"),
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
    OP_GET_LOCAL, 0,
    OP_JUMP_IF_FALSE, 0, 6,
    OP_POP,
    OP_CONSTANT, 0,
    OP_JUMP, 0, 3,
    OP_POP,
    OP_CONSTANT, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
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
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");
  f->chunk = chunk_dump_7();
  return obj(f);
}

static ValueArray constants_dump_8() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    string("NUMBER_VAL("), string("string"), string(")"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dump_8() {
  Chunk c;
  initChunk(&c);
  c.count = 15;
  c.capacity = 15;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_CALL, 1,
    OP_CONSTANT, 2,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dump_8();

  return c;
};

             // dump
static Value fn_dump_8() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dump");
  f->chunk = chunk_dump_8();
  return obj(f);
}

static ValueArray constants_print_9() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    string("write"), string("string"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_print_9() {
  Chunk c;
  initChunk(&c);
  c.count = 12;
  c.capacity = 12;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_print_9();

  return c;
};

             // print
static Value fn_print_9() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");
  f->chunk = chunk_print_9();
  return obj(f);
}

static ValueArray constants__dot__10() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__dot__10() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_MULTIPLY,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    37, 37, 37, 37, 37, 37, 37, 37,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__dot__10();

  return c;
};

             // .
static Value fn__dot__10() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString(".");
  f->chunk = chunk__dot__10();
  return obj(f);
}

static ValueArray constants_inspect_11() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    string("{}"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_inspect_11() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    40, 40, 40, 40, 40,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_inspect_11();

  return c;
};

             // inspect
static Value fn_inspect_11() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
  f->chunk = chunk_inspect_11();
  return obj(f);
}

static ValueArray constants_init_12() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    string("type"), string("value"), string("targets"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_init_12() {
  Chunk c;
  initChunk(&c);
  c.count = 24;
  c.capacity = 24;
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
    OP_RETURN,
  };
  int lines[] = {
    42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_init_12();

  return c;
};

             // init
static Value fn_init_12() {
  ObjFunction *f = newFunction();  f->arity = 3;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->chunk = chunk_init_12();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_lib_slash_core_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 33;
  Value values[] = {
    string("Nil"), string("Any"), string("string"), fn_string_1(), string("dump"), fn_dump_2(), string("Object"), string("fn_id"), NUMBER_VAL(0.000000), string("Function"), fn_dump_3(), string("dump_global"), fn_dump_global_4(), string("Method"), string("NativeFunction"), string("Class"), string("Bool"), fn_string_5(), string("print"), fn_print_6(), fn_dump_7(), string("Number"), fn_dump_8(), fn_print_9(), string(""), fn__dot__10(), string("Table"), string("inspect"), fn_inspect_11(), string("Atom"), fn_init_12(), string("init"), string("script return value"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_lib_slash_core_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 178;
  c.capacity = 178;
  u8 code[] = {
    OP_CLASS, 0, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 3,
    OP_METHOD, 2,
    OP_CLOSURE, 5,
    OP_METHOD, 4,
    OP_POP,
    OP_POP,
    OP_CLASS, 6, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CONSTANT, 8,
    OP_DEFINE_GLOBAL, 7,
    OP_CLASS, 9, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 10,
    OP_METHOD, 4,
    OP_CLOSURE, 12,
    OP_METHOD, 11,
    OP_POP,
    OP_POP,
    OP_CLASS, 13, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 9,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 14, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 9,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 15, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 9,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 16, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 17,
    OP_METHOD, 2,
    OP_CLOSURE, 19,
    OP_METHOD, 18,
    OP_CLOSURE, 20,
    OP_METHOD, 4,
    OP_POP,
    OP_POP,
    OP_CLASS, 21, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 22,
    OP_METHOD, 4,
    OP_CLOSURE, 23,
    OP_METHOD, 18,
    OP_CLOSURE, 25,
    OP_METHOD, 24,
    OP_POP,
    OP_POP,
    OP_CLASS, 26, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 28,
    OP_METHOD, 27,
    OP_POP,
    OP_POP,
    OP_CLASS, 29, 0,
    OP_CLOSURE, 30,
    OP_METHOD, 31,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 29,
    OP_ASSERT_STACK, 32, 2,
    OP_RETURN,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 16, 16, 16, 16, 23, 23, 23, 23, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_lib_slash_core_dot_lita_0();

  return c;
};

             // src/lita/lib/core.lita
static Value fn_src_slash_lita_slash_lib_slash_core_dot_lita_0() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/lib/core.lita");
  f->chunk = chunk_src_slash_lita_slash_lib_slash_core_dot_lita_0();
  return obj(f);
}

ObjFunction *core_lita() {
  return asFunction(fn_src_slash_lita_slash_lib_slash_core_dot_lita_0());
}
