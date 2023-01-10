// clang-format off
// sol -c src/sol/lib/Parser.sol
#include "sol/chunk.h"
#include "sol/common.h"
#include "sol/lib.h"
#include "sol/memory.h"
#include "sol/string.h"

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
    20, 20, 20, 20, 20, 20, 20, 21, 21, 21,
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
  f->name = newString("init");
             // init
  f->chunk = chunk1();
  return obj(f);
}

// src_sol_lib_Parser_sol
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

// src_sol_lib_Parser_sol
static Chunk chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 18;
  c.capacity = 18;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 7, 7, 1, 40,
  };
  int lines[] = {
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 21, 21, 21, 21, 21, 21, 21, 21,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // src_sol_lib_Parser_sol
  c.constants = constants0();

  return c;
};

// src_sol_lib_Parser_sol
static Value fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src_sol_lib_Parser_sol");
             // src_sol_lib_Parser_sol
  f->chunk = chunk0();
  return obj(f);
}

ObjFun *Parser_sol() {
                //src_sol_lib_Parser_sol
  return AS_FUN(fn0());
}
