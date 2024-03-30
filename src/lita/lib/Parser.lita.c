// clang-format off
// lita -c src/lita/lib/Parser.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

// init
static ValueArray constants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("source"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// init
static Chunk chunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 40,
  };
  int lines[] = {
    21, 21, 21, 21, 21, 21, 21, 22, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // init
  c.constants = constants1();

  return c;
};

// init
static Value fn1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("init");
             // init
  f->chunk = chunk1();
  return obj(f);
}

// src_lita_lib_Parser_lita
static ValueArray constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("Parser"), str("Object"), str("init"), /*init*/fn1(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// src_lita_lib_Parser_lita
static Chunk chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 18;
  c.capacity = 18;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 7, 7, 1, 40,
  };
  int lines[] = {
    19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 22, 22, 22, 22, 22, 22, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // src_lita_lib_Parser_lita
  c.constants = constants0();

  return c;
};

// src_lita_lib_Parser_lita
static Value fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src_lita_lib_Parser_lita");
             // src_lita_lib_Parser_lita
  f->chunk = chunk0();
  return obj(f);
}

ObjFun *Parser_lita() {
                //src_lita_lib_Parser_lita
  return AS_FUN(fn0());
}
