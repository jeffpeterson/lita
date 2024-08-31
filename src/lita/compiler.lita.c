// clang-format off
// lita -c src/lita/compiler.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

static ValueArray constants_compile_1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_compile_1() {
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
  c.constants = constants_compile_1();

  return c;
};

             // compile
static Value fn_compile_1() {
  ObjFun *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = newString("compile");
  f->chunk = chunk_compile_1();
  return obj(f);
}

static ValueArray constants_markCompilerRoots_2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_markCompilerRoots_2() {
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
  c.constants = constants_markCompilerRoots_2();

  return c;
};

             // markCompilerRoots
static Value fn_markCompilerRoots_2() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("markCompilerRoots");
  f->chunk = chunk_markCompilerRoots_2();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_compiler_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 13;
  Value values[] = {
    str("compile"), fn_compile_1(), str("markCompilerRoots"), fn_markCompilerRoots_2(), str("Parser"), str("Object"), str("current"), str("previous"), str("indebt"), str("hadError"), str("panicMode"), str("Context"), str("Compiler"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_compiler_dot_lita_0() {
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
  c.constants = constants_src_slash_lita_slash_compiler_dot_lita_0();

  return c;
};

             // src/lita/compiler.lita
static Value fn_src_slash_lita_slash_compiler_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/compiler.lita");
  f->chunk = chunk_src_slash_lita_slash_compiler_dot_lita_0();
  return obj(f);
}

ObjFun *compiler_lita() {
  return AS_FUN(fn_src_slash_lita_slash_compiler_dot_lita_0());
}
