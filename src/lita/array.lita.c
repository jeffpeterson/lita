// clang-format off
// lita -c src/lita/array.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

static ValueArray constants__lt__lt__1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    string("push"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__lt__lt__1() {
  Chunk c;
  initChunk(&c);
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    2, 2, 2, 2, 2, 2, 2, 2, 4, 4,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__lt__lt__1();

  return c;
};

             // <<
static Value fn__lt__lt__1() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("<<");
  f->chunk = chunk__lt__lt__1();
  return obj(f);
}

static ValueArray constants__eq__eq__2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 8;
  Value values[] = {
    string("length"), string("if condition"), string("object_id"), NUMBER_VAL(0.000000), string("while condition"), string("get"), NUMBER_VAL(1.000000), string("falsy while condition"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__eq__eq__2() {
  Chunk c;
  initChunk(&c);
  c.count = 116;
  c.capacity = 116;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 0,
    OP_EQUAL,
    OP_NOT,
    OP_ASSERT_STACK, 1, 3,
    OP_JUMP_IF_FALSE, 0, 7,
    OP_POP,
    OP_FALSE,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 2,
    OP_EQUAL,
    OP_ASSERT_STACK, 1, 3,
    OP_JUMP_IF_FALSE, 0, 7,
    OP_POP,
    OP_TRUE,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_CONSTANT, 3,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_LESS,
    OP_ASSERT_STACK, 4, 4,
    OP_JUMP_IF_FALSE, 0, 45,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 5,
    OP_GET_LOCAL, 2,
    OP_CALL, 1,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 2,
    OP_DEFAULT, 3,
    OP_PEEK, 0,
    OP_CONSTANT, 6,
    OP_ADD,
    OP_SET_LOCAL, 2,
    OP_POP,
    OP_INVOKE, 5, 1,
    OP_EQUAL,
    OP_NOT,
    OP_ASSERT_STACK, 1, 4,
    OP_JUMP_IF_FALSE, 0, 7,
    OP_POP,
    OP_FALSE,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_LOOP, 0, 58,
    OP_ASSERT_STACK, 7, 4,
    OP_POP,
    OP_TRUE,
    OP_RETURN,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 12, 12,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__eq__eq__2();

  return c;
};

             // ==
static Value fn__eq__eq__2() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("==");
  f->chunk = chunk__eq__eq__2();
  return obj(f);
}

static ValueArray constants_each_3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 6;
  Value values[] = {
    NUMBER_VAL(0.000000), string("length"), string("while condition"), string("get"), NUMBER_VAL(1.000000), string("falsy while condition"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_each_3() {
  Chunk c;
  initChunk(&c);
  c.count = 48;
  c.capacity = 48;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_LESS,
    OP_ASSERT_STACK, 2, 4,
    OP_JUMP_IF_FALSE, 0, 27,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 3,
    OP_GET_LOCAL, 2,
    OP_DEFAULT, 0,
    OP_PEEK, 0,
    OP_CONSTANT, 4,
    OP_ADD,
    OP_SET_LOCAL, 2,
    OP_POP,
    OP_CALL, 1,
    OP_CALL, 1,
    OP_POP,
    OP_LOOP, 0, 40,
    OP_ASSERT_STACK, 5, 4,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 17, 17, 17, 17, 17, 17, 17, 17, 17,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_each_3();

  return c;
};

             // each
static Value fn_each_3() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("each");
  f->chunk = chunk_each_3();
  return obj(f);
}

static ValueArray constants_map_4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 7;
  Value values[] = {
    NUMBER_VAL(0.000000), string("length"), string("while condition"), string("get"), NUMBER_VAL(1.000000), string("<<"), string("falsy while condition"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_map_4() {
  Chunk c;
  initChunk(&c);
  c.count = 59;
  c.capacity = 59;
  u8 code[] = {
    OP_ARRAY, 0,
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 3,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_LESS,
    OP_ASSERT_STACK, 2, 5,
    OP_JUMP_IF_FALSE, 0, 32,
    OP_POP,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 3,
    OP_GET_LOCAL, 3,
    OP_DEFAULT, 0,
    OP_PEEK, 0,
    OP_CONSTANT, 4,
    OP_ADD,
    OP_SET_LOCAL, 3,
    OP_POP,
    OP_CALL, 1,
    OP_CALL, 1,
    OP_INVOKE, 5, 1,
    OP_POP,
    OP_LOOP, 0, 45,
    OP_ASSERT_STACK, 6, 5,
    OP_POP,
    OP_GET_LOCAL, 2,
    OP_RETURN,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    18, 18, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 24, 24,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_map_4();

  return c;
};

             // map
static Value fn_map_4() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("map");
  f->chunk = chunk_map_4();
  return obj(f);
}

static ValueArray constants__dot_print_6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    string("print"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__dot_print_6() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_UPVALUE, 0,
    OP_INVOKE, 0, 1,
    OP_RETURN,
  };
  int lines[] = {
    25, 25, 25, 25, 25, 25, 25, 25,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__dot_print_6();

  return c;
};

             // .print
static Value fn__dot_print_6() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 1;
  f->name = newString(".print");
  f->chunk = chunk__dot_print_6();
  return obj(f);
}

static ValueArray constants_print_5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    string("each"), fn__dot_print_6(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_print_5() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CLOSURE, 1,
    OP_CALL, 1,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_print_5();

  return c;
};

             // print
static Value fn_print_5() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");
  f->chunk = chunk_print_5();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_array_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 13;
  Value values[] = {
    string("Array"), string("Object"), string("<<"), fn__lt__lt__1(), string("=="), fn__eq__eq__2(), string("each"), fn_each_3(), string("map"), fn_map_4(), string("print"), fn_print_5(), string("script return value"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_array_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 38;
  c.capacity = 38;
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
    OP_CLOSURE, 7,
    OP_METHOD, 6,
    OP_CLOSURE, 9,
    OP_METHOD, 8,
    OP_CLOSURE, 11,
    OP_METHOD, 10,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 0,
    OP_ASSERT_STACK, 12, 2,
    OP_RETURN,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 12, 12, 12, 12, 17, 17, 17, 17, 24, 24, 24, 24, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_array_dot_lita_0();

  return c;
};

             // src/lita/array.lita
static Value fn_src_slash_lita_slash_array_dot_lita_0() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/array.lita");
  f->chunk = chunk_src_slash_lita_slash_array_dot_lita_0();
  return obj(f);
}

ObjFunction *array_lita() {
  return asFunction(fn_src_slash_lita_slash_array_dot_lita_0());
}
