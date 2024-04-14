// clang-format off
// lita -c src/lita/compiler.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

// compile
static ValueArray constants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// compile
static Chunk chunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 2;
  c.capacity = 2;
  u8 code[] = {
    1, 40,
  };
  int lines[] = {
    1, 1,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // compile
  c.constants = constants1();

  return c;
};

// compile
static Value fn1() {
  ObjFun *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = new_string("compile");
             // compile
  f->chunk = chunk1();
  return obj(f);
}

// markCompilerRoots
static ValueArray constants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// markCompilerRoots
static Chunk chunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 2;
  c.capacity = 2;
  u8 code[] = {
    1, 40,
  };
  int lines[] = {
    3, 3,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // markCompilerRoots
  c.constants = constants2();

  return c;
};

// markCompilerRoots
static Value fn2() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("markCompilerRoots");
             // markCompilerRoots
  f->chunk = chunk2();
  return obj(f);
}

// src_lita_compiler_lita
static ValueArray constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 13;
  Value values[] = {
    str("compile"), /*compile*/fn1(), str("markCompilerRoots"), /*markCompilerRoots*/fn2(), str("Parser"), str("Object"), str("current"), str("previous"), str("indebt"), str("hadError"), str("panicMode"), str("Context"), str("Compiler"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// src_lita_compiler_lita
static Chunk chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 61;
  c.capacity = 61;
  u8 code[] = {
    37, 1, 11, 0, 37, 3, 11, 2, 34, 4, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 1, 11, 6, 1, 11, 7, 1, 11, 8, 1, 11, 9, 1, 11, 10, 34, 11, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 34, 12, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 72, 72, 72, 72,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // src_lita_compiler_lita
  c.constants = constants0();

  return c;
};

// src_lita_compiler_lita
static Value fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src_lita_compiler_lita");
             // src_lita_compiler_lita
  f->chunk = chunk0();
  return obj(f);
}

ObjFun *compiler_lita() {
                //src_lita_compiler_lita
  return AS_FUN(fn0());
}
