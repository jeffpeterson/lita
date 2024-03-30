// clang-format off
// lita -c src/lita/tuple.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

// *
static ValueArray constants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("map"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// *
static Chunk chunk1() {
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
                // *
  c.constants = constants1();

  return c;
};

// *
static Value fn1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("*");
             // *
  f->chunk = chunk1();
  return obj(f);
}

// each
static ValueArray constants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    0, str("length"), 0x3ff0000000000000, str("get"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// each
static Chunk chunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 52;
  c.capacity = 52;
  u8 code[] = {
    0, 0, 14, 2, 14, 0, 44, 1, 23, 31, 0, 36, 7, 30, 0, 16, 14, 2, 10, 0, 6, 0, 0, 2, 24, 15, 2, 7, 7, 32, 0, 30, 14, 1, 14, 0, 44, 3, 14, 2, 33, 1, 33, 1, 7, 32, 0, 32, 7, 7, 1, 40,
  };
  int lines[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // each
  c.constants = constants2();

  return c;
};

// each
static Value fn2() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("each");
             // each
  f->chunk = chunk2();
  return obj(f);
}

// src_lita_tuple_lita
static ValueArray constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 6;
  Value values[] = {
    str("Tuple"), str("Object"), str("*"), /***/fn1(), str("each"), /*each*/fn2(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// src_lita_tuple_lita
static Chunk chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 22;
  c.capacity = 22;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 37, 5, 36, 4, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // src_lita_tuple_lita
  c.constants = constants0();

  return c;
};

// src_lita_tuple_lita
static Value fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src_lita_tuple_lita");
             // src_lita_tuple_lita
  f->chunk = chunk0();
  return obj(f);
}

ObjFun *tuple_lita() {
                //src_lita_tuple_lita
  return AS_FUN(fn0());
}
