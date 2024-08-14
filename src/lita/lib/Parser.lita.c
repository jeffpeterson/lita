// clang-format off
// lita -c src/lita/lib/Parser.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

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
    14, 0, 14, 1, 17, 0, 7, 14, 0, 40,
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
  f->name = new_string("init");
  f->chunk = chunk_init_1();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_lib_slash_Parser_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("Parser"), str("Object"), str("init"), fn_init_1(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_lib_slash_Parser_dot_lita_0() {
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
  c.constants = constants_src_slash_lita_slash_lib_slash_Parser_dot_lita_0();

  return c;
};

             // src/lita/lib/Parser.lita
static Value fn_src_slash_lita_slash_lib_slash_Parser_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src/lita/lib/Parser.lita");
  f->chunk = chunk_src_slash_lita_slash_lib_slash_Parser_dot_lita_0();
  return obj(f);
}

ObjFun *Parser_lita() {
  return AS_FUN(fn_src_slash_lita_slash_lib_slash_Parser_dot_lita_0());
}
