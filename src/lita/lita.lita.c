// clang-format off
// lita -c src/lita/lita.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

static ValueArray constants_class_1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("classOf"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_class_1() {
  Chunk c;
  initChunk(&c);
  c.count = 12;
  c.capacity = 12;
  u8 code[] = {
    14, 0, 44, 0, 14, 0, 33, 1, 7, 40, 1, 40,
  };
  int lines[] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_class_1();

  return c;
};

             // class
static Value fn_class_1() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("class");
  f->chunk = chunk_class_1();
  return obj(f);
}

static ValueArray constants_hash_2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("hash"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_hash_2() {
  Chunk c;
  initChunk(&c);
  c.count = 12;
  c.capacity = 12;
  u8 code[] = {
    14, 0, 44, 0, 14, 0, 33, 1, 7, 40, 1, 40,
  };
  int lines[] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_hash_2();

  return c;
};

             // hash
static Value fn_hash_2() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("hash");
  f->chunk = chunk_hash_2();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_lita_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 6;
  Value values[] = {
    str("Any"), str("Object"), str("class"), fn_class_1(), str("hash"), fn_hash_2(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_lita_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 34;
  c.capacity = 34;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 37, 5, 36, 4, 7, 7, 34, 1, 0, 14, 0, 44, 0, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 32, 32, 32, 32,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_lita_dot_lita_0();

  return c;
};

             // src/lita/lita.lita
static Value fn_src_slash_lita_slash_lita_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src/lita/lita.lita");
  f->chunk = chunk_src_slash_lita_slash_lita_dot_lita_0();
  return obj(f);
}

ObjFun *lita_lita() {
  return AS_FUN(fn_src_slash_lita_slash_lita_dot_lita_0());
}
