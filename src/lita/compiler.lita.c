// clang-format off
// lita -c src/lita/compiler.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

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
    OP_NIL,
    OP_RETURN,
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
  ObjFunction *f = newFunction();  f->arity = 2;
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
    OP_NIL,
    OP_RETURN,
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
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("markCompilerRoots");
  f->chunk = chunk_markCompilerRoots_2();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_compiler_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 14;
  Value values[] = {
    string("compile"), fn_compile_1(), string("markCompilerRoots"), fn_markCompilerRoots_2(), string("Parser"), string("Object"), string("current"), string("previous"), string("indebt"), string("hadError"), string("panicMode"), string("Context"), string("Compiler"), string("script return value"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_compiler_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 65;
  c.capacity = 65;
  u8 code[] = {
    OP_CLOSURE, 1,
    OP_DEFINE_GLOBAL, 0,
    OP_CLOSURE, 3,
    OP_DEFINE_GLOBAL, 2,
    OP_CLASS, 4, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 5,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_NIL,
    OP_DEFINE_GLOBAL, 6,
    OP_NIL,
    OP_DEFINE_GLOBAL, 7,
    OP_NIL,
    OP_DEFINE_GLOBAL, 8,
    OP_NIL,
    OP_DEFINE_GLOBAL, 9,
    OP_NIL,
    OP_DEFINE_GLOBAL, 10,
    OP_CLASS, 11, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 5,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 12, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 5,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 12,
    OP_ASSERT_STACK, 13, 2,
    OP_RETURN,
  };
  int lines[] = {
    1, 1, 1, 1, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 72, 72, 72, 72, 72, 72, 72, 72,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_compiler_dot_lita_0();

  return c;
};

             // src/lita/compiler.lita
static Value fn_src_slash_lita_slash_compiler_dot_lita_0() {
  ObjFunction *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/compiler.lita");
  f->chunk = chunk_src_slash_lita_slash_compiler_dot_lita_0();
  return obj(f);
}

ObjFunction *compiler_lita() {
  return asFunction(fn_src_slash_lita_slash_compiler_dot_lita_0());
}
