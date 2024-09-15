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

             // init
static Value fn_init_1() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("init");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 10;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_SET_PROPERTY, 0,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
  };
  int lines[] = { 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("source"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // src/lita/lib/Parser.lita
static Value fn_src_slash_lita_slash_lib_slash_Parser_dot_lita_0() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/lib/Parser.lita");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 22;
  c->version = 1;
  u8 code[] = {
    OP_CLASS, 0, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 3,
    OP_METHOD, 2,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 0,
    OP_ASSERT_STACK, 4, 2,
    OP_RETURN,
  };
  int lines[] = { 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 5;
  Value values[] = {
    string("Parser"),
    string("Object"),
    string("init"),
    fn_init_1(),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *Parser_lita() {
  return asFunction(fn_src_slash_lita_slash_lib_slash_Parser_dot_lita_0());
}
