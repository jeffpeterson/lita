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
    str("map"),
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
    14, 0, 44, 0, 14, 1, 33, 1, 40, 1, 40,
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
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("*");
  f->chunk = chunk__star__1();
  return obj(f);
}

static ValueArray constants_head_2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("get"), NUMBER_VAL(0.000000),
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
    14, 0, 44, 0, 0, 1, 33, 1, 40, 1, 40,
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
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("head");
  f->chunk = chunk_head_2();
  return obj(f);
}

static ValueArray constants_each_3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    NUMBER_VAL(0.000000), str("length"), NUMBER_VAL(1.000000), str("get"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_each_3() {
  Chunk c;
  initChunk(&c);
  c.count = 52;
  c.capacity = 52;
  u8 code[] = {
    0, 0, 14, 2, 14, 0, 44, 1, 23, 31, 0, 36, 7, 30, 0, 16, 14, 2, 10, 0, 6, 0, 0, 2, 24, 15, 2, 7, 7, 32, 0, 30, 14, 1, 14, 0, 44, 3, 14, 2, 33, 1, 33, 1, 7, 32, 0, 32, 7, 7, 1, 40,
  };
  int lines[] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 8, 8, 8, 8, 8, 8,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_each_3();

  return c;
};

             // each
static Value fn_each_3() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("each");
  f->chunk = chunk_each_3();
  return obj(f);
}

static ValueArray constants__dot_print_5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("print"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__dot_print_5() {
  Chunk c;
  initChunk(&c);
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    14, 1, 18, 0, 41, 0, 1, 40, 1, 40,
  };
  int lines[] = {
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__dot_print_5();

  return c;
};

             // .print
static Value fn__dot_print_5() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 1;
  f->name = new_string(".print");
  f->chunk = chunk__dot_print_5();
  return obj(f);
}

static ValueArray constants_print_4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("each"), fn__dot_print_5(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_print_4() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    14, 0, 44, 0, 37, 1, 33, 1, 7, 1, 40,
  };
  int lines[] = {
    9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_print_4();

  return c;
};

             // print
static Value fn_print_4() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("print");
  f->chunk = chunk_print_4();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_tuple_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 10;
  Value values[] = {
    str("Tuple"), str("Object"), str("*"), fn__star__1(), str("head"), fn_head_2(), str("each"), fn_each_3(), str("print"), fn_print_4(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_tuple_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 30;
  c.capacity = 30;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 37, 5, 36, 4, 37, 7, 36, 6, 37, 9, 36, 8, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 4, 4, 4, 4, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_tuple_dot_lita_0();

  return c;
};

             // src/lita/tuple.lita
static Value fn_src_slash_lita_slash_tuple_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src/lita/tuple.lita");
  f->chunk = chunk_src_slash_lita_slash_tuple_dot_lita_0();
  return obj(f);
}

ObjFun *tuple_lita() {
  return AS_FUN(fn_src_slash_lita_slash_tuple_dot_lita_0());
}
