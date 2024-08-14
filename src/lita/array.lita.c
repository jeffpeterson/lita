// clang-format off
// lita -c src/lita/array.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

static ValueArray constants__lt__lt__1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("push"),
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
    14, 0, 14, 1, 41, 0, 1, 40, 1, 40,
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
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("<<");
  f->chunk = chunk__lt__lt__1();
  return obj(f);
}

static ValueArray constants__eq__eq__2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    str("length"), str("object_id"), NUMBER_VAL(0.000000), NUMBER_VAL(1.000000), str("get"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__eq__eq__2() {
  Chunk c;
  initChunk(&c);
  c.count = 107;
  c.capacity = 107;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 16, 0, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 14, 0, 44, 1, 14, 1, 16, 1, 21, 31, 0, 6, 7, 2, 40, 30, 0, 1, 7, 0, 2, 14, 2, 14, 0, 44, 0, 23, 31, 0, 50, 7, 30, 0, 16, 14, 2, 10, 2, 6, 0, 0, 3, 24, 15, 2, 7, 7, 32, 0, 30, 14, 0, 44, 4, 14, 2, 33, 1, 14, 1, 14, 2, 41, 4, 1, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 32, 0, 46, 7, 7, 2, 40, 1, 40,
  };
  int lines[] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 11, 11,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__eq__eq__2();

  return c;
};

             // ==
static Value fn__eq__eq__2() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("==");
  f->chunk = chunk__eq__eq__2();
  return obj(f);
}

static ValueArray constants_map_3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    NUMBER_VAL(0.000000), str("length"), NUMBER_VAL(1.000000), str("get"), str("<<"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_map_3() {
  Chunk c;
  initChunk(&c);
  c.count = 62;
  c.capacity = 62;
  u8 code[] = {
    46, 0, 0, 0, 14, 3, 14, 0, 44, 1, 23, 31, 0, 41, 7, 30, 0, 16, 14, 3, 10, 0, 6, 0, 0, 2, 24, 15, 3, 7, 7, 32, 0, 30, 14, 2, 14, 1, 14, 0, 44, 3, 14, 3, 33, 1, 33, 1, 41, 4, 1, 7, 32, 0, 37, 7, 7, 14, 2, 40, 1, 40,
  };
  int lines[] = {
    12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_map_3();

  return c;
};

             // map
static Value fn_map_3() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("map");
  f->chunk = chunk_map_3();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_array_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 8;
  Value values[] = {
    str("Array"), str("Object"), str("<<"), fn__lt__lt__1(), str("=="), fn__eq__eq__2(), str("map"), fn_map_3(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_array_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 26;
  c.capacity = 26;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 37, 5, 36, 4, 37, 7, 36, 6, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 11, 11, 11, 11, 16, 16, 16, 16, 16, 16, 16, 16,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_array_dot_lita_0();

  return c;
};

             // src/lita/array.lita
static Value fn_src_slash_lita_slash_array_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src/lita/array.lita");
  f->chunk = chunk_src_slash_lita_slash_array_dot_lita_0();
  return obj(f);
}

ObjFun *array_lita() {
  return AS_FUN(fn_src_slash_lita_slash_array_dot_lita_0());
}
