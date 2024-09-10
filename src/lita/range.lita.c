// clang-format off
// lita -c src/lita/range.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

             // inspect
static Value fn_inspect_1() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 25;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_PROPERTY, 2,
    OP_CALL, 1,
    OP_CONSTANT, 3,
    OP_CALL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 4,
    OP_GET_PROPERTY, 2,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 5;
  Value values[] = {
    string(""),
    string("start"),
    string("inspect"),
    string(".."),
    string("end"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // string
static Value fn_string_2() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 25;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_PROPERTY, 2,
    OP_CALL, 1,
    OP_CONSTANT, 3,
    OP_CALL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 4,
    OP_GET_PROPERTY, 2,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 5;
  Value values[] = {
    string(""),
    string("start"),
    string("string"),
    string(".."),
    string("end"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // length
static Value fn_length_3() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("length");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 12;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_SUBTRACT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("end"),
    string("start"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // map
static Value fn_map_4() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("map");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 20;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CALL, 1,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_CALL, 1,
    OP_RANGE,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("start"),
    string("end"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // src/lita/range.lita
static Value fn_src_slash_lita_slash_range_dot_lita_0() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/range.lita");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 34;
  u8 code[] = {
    OP_CLASS, 0, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CLOSURE, 3,
    OP_METHOD, 2,
    OP_CLOSURE, 5,
    OP_METHOD, 4,
    OP_CLOSURE, 7,
    OP_METHOD, 6,
    OP_CLOSURE, 9,
    OP_METHOD, 8,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 0,
    OP_ASSERT_STACK, 10, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 11;
  Value values[] = {
    string("Range"),
    string("Object"),
    string("inspect"),
    fn_inspect_1(),
    string("string"),
    fn_string_2(),
    string("length"),
    fn_length_3(),
    string("map"),
    fn_map_4(),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *range_lita() {
  return asFunction(fn_src_slash_lita_slash_range_dot_lita_0());
}
