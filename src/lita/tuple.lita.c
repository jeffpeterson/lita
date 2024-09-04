// clang-format off
// lita -c src/lita/tuple.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

static ValueArray constants__star__1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    string("map"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__star__1() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__star__1();

  return c;
};

             // *
static Value fn__star__1() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("*");
  f->chunk = chunk__star__1();
  return obj(f);
}

static ValueArray constants_head_2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    string("get"), NUMBER_VAL(0.000000),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_head_2() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_head_2();

  return c;
};

             // head
static Value fn_head_2() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("head");
  f->chunk = chunk_head_2();
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
    5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9,
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

static ValueArray constants_zipEach_5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    string("get"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_zipEach_5() {
  Chunk c;
  initChunk(&c);
  c.count = 16;
  c.capacity = 16;
  u8 code[] = {
    OP_GET_UPVALUE, 0,
    OP_GET_LOCAL, 1,
    OP_GET_UPVALUE, 1,
    OP_GET_LOCAL, 2,
    OP_INVOKE, 0, 1,
    OP_CALL, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_zipEach_5();

  return c;
};

             // zipEach
static Value fn_zipEach_5() {
  ObjFunction *f = newFunction();  f->arity = 2;
  f->upvalueCount = 2;
  f->name = newString("zipEach");
  f->chunk = chunk_zipEach_5();
  return obj(f);
}

static ValueArray constants_zip_4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    fn_zipEach_5(), string("map"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_zip_4() {
  Chunk c;
  initChunk(&c);
  c.count = 18;
  c.capacity = 18;
  u8 code[] = {
    OP_CLOSURE, 0,
    OP_NIL,
    OP_TRUE,
    OP_NIL,
    OP_NIL,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_LOCAL, 3,
    OP_CALL, 1,
    OP_RETURN,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 13, 13,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_zip_4();

  return c;
};

             // zip
static Value fn_zip_4() {
  ObjFunction *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = newString("zip");
  f->chunk = chunk_zip_4();
  return obj(f);
}

static ValueArray constants__dot_print_7() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    string("print"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__dot_print_7() {
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
    13, 13, 13, 13, 13, 13, 13, 13,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__dot_print_7();

  return c;
};

             // .print
static Value fn__dot_print_7() {
  ObjFunction *f = newFunction();  f->arity = 1;
  f->upvalueCount = 1;
  f->name = newString(".print");
  f->chunk = chunk__dot_print_7();
  return obj(f);
}

static ValueArray constants_print_6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    string("each"), fn__dot_print_7(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_print_6() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CLOSURE, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = {
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
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

static ValueArray constants_src_slash_lita_slash_tuple_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 13;
  Value values[] = {
    string("Tuple"), string("Object"), string("*"), fn__star__1(), string("head"), fn_head_2(), string("each"), fn_each_3(), string("zip"), fn_zip_4(), string("print"), fn_print_6(), string("script return value"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_tuple_dot_lita_0() {
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
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 4, 4, 4, 4, 9, 9, 9, 9, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_tuple_dot_lita_0();

  return c;
};

             // src/lita/tuple.lita
static Value fn_src_slash_lita_slash_tuple_dot_lita_0() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/tuple.lita");
  f->chunk = chunk_src_slash_lita_slash_tuple_dot_lita_0();
  return obj(f);
}

ObjFunction *tuple_lita() {
  return asFunction(fn_src_slash_lita_slash_tuple_dot_lita_0());
}
