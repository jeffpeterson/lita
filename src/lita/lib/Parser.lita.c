// clang-format off
// lita -c src/lita/lib/Parser.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

static ValueArray constants_init_1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("source"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_init_1() {
  Chunk c;
  initChunk(&c);
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_SET_PROPERTY, 0,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
  };
  int lines[] = {
    21, 21, 21, 21, 21, 21, 21, 22, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_init_1();

  return c;
};

             // init
static Value fn_init_1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->chunk = chunk_init_1();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_lib_slash_Parser_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    str("Parser"), str("Object"), str("init"), fn_init_1(), str("script return value"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_lib_slash_Parser_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 22;
  c.capacity = 22;
  u8 code[] = {
    OP_CLASS, 0, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 3,
    OP_METHOD, 2,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 0,
    OP_ASSERT_STACK, 4, 2,
    OP_RETURN,
  };
  int lines[] = {
    19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_lib_slash_Parser_dot_lita_0();

  return c;
};

             // src/lita/lib/Parser.lita
static Value fn_src_slash_lita_slash_lib_slash_Parser_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/lib/Parser.lita");
  f->chunk = chunk_src_slash_lita_slash_lib_slash_Parser_dot_lita_0();
  return obj(f);
}

ObjFun *Parser_lita() {
  return AS_FUN(fn_src_slash_lita_slash_lib_slash_Parser_dot_lita_0());
}
