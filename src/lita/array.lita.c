// clang-format off
// lita -c src/lita/array.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

// <<
static ValueArray constants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("push"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// <<
static Chunk chunk1() {
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
                // <<
  c.constants = constants1();

  return c;
};

// <<
static Value fn1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("<<");
             // <<
  f->chunk = chunk1();
  return obj(f);
}

// ==
static ValueArray constants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    str("length"), str("objectId"), NUMBER_VAL(0.000000), NUMBER_VAL(1.000000), str("get"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// ==
static Chunk chunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 107;
  c.capacity = 107;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 16, 0, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 14, 0, 44, 1, 14, 1, 16, 1, 21, 31, 0, 6, 7, 2, 40, 30, 0, 1, 7, 0, 2, 14, 2, 14, 0, 44, 0, 23, 31, 0, 50, 7, 30, 0, 16, 14, 2, 10, 2, 6, 0, 0, 3, 24, 15, 2, 7, 7, 32, 0, 30, 14, 0, 44, 4, 14, 2, 33, 1, 14, 1, 14, 2, 41, 4, 1, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 32, 0, 46, 7, 7, 2, 40, 1, 40,
  };
  int lines[] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // ==
  c.constants = constants2();

  return c;
};

// ==
static Value fn2() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("==");
             // ==
  f->chunk = chunk2();
  return obj(f);
}

// map
static ValueArray constants3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    NUMBER_VAL(0.000000), str("length"), NUMBER_VAL(1.000000), str("get"), str("<<"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// map
static Chunk chunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 62;
  c.capacity = 62;
  u8 code[] = {
    46, 0, 0, 0, 14, 3, 14, 0, 44, 1, 23, 31, 0, 41, 7, 30, 0, 16, 14, 3, 10, 0, 6, 0, 0, 2, 24, 15, 3, 7, 7, 32, 0, 30, 14, 2, 14, 1, 14, 0, 44, 3, 14, 3, 33, 1, 33, 1, 41, 4, 1, 7, 32, 0, 37, 7, 7, 14, 2, 40, 1, 40,
  };
  int lines[] = {
    12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // map
  c.constants = constants3();

  return c;
};

// map
static Value fn3() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("map");
             // map
  f->chunk = chunk3();
  return obj(f);
}

// src_lita_array_lita
static ValueArray constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 8;
  Value values[] = {
    str("Array"), str("Object"), str("<<"), /*<<*/fn1(), str("=="), /*==*/fn2(), str("map"), /*map*/fn3(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// src_lita_array_lita
static Chunk chunk0() {
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
                // src_lita_array_lita
  c.constants = constants0();

  return c;
};

// src_lita_array_lita
static Value fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src_lita_array_lita");
             // src_lita_array_lita
  f->chunk = chunk0();
  return obj(f);
}

ObjFun *array_lita() {
                //src_lita_array_lita
  return AS_FUN(fn0());
}
