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
  c->version = 0;
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
  c->version = 0;
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
  c->version = 0;
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
  c->version = 0;
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

             // array
static Value fn_array_5() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("array");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 111;
  c->version = 0;
  u8 code[] = {
    OP_ARRAY, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_GREATER,
    OP_NOT,
    OP_ASSERT_STACK, 3, 4,
    OP_JUMP_IF_FALSE, 0, 43,
    OP_POP,
    OP_TRUE,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_GREATER,
    OP_NOT,
    OP_ASSERT_STACK, 4, 5,
    OP_JUMP_IF_FALSE, 0, 16,
    OP_POP,
    OP_FALSE,
    OP_SET_LOCAL, 3,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 2,
    OP_INVOKE, 5, 1,
    OP_POP,
    OP_LOOP, 0, 30,
    OP_ASSERT_STACK, 6, 5,
    OP_POP,
    OP_JUMP_IF_FALSE, 0, 0,
    OP_POP,
    OP_JUMP, 0, 40,
    OP_POP,
    OP_TRUE,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_LESS,
    OP_NOT,
    OP_ASSERT_STACK, 4, 5,
    OP_JUMP_IF_FALSE, 0, 16,
    OP_POP,
    OP_FALSE,
    OP_SET_LOCAL, 3,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 2,
    OP_INVOKE, 5, 1,
    OP_POP,
    OP_LOOP, 0, 30,
    OP_ASSERT_STACK, 6, 5,
    OP_POP,
    OP_JUMP_IF_FALSE, 0, 0,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_RETURN,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 7;
  Value values[] = {
    NUMBER_VAL(0.000000),
    string("start"),
    string("end"),
    string("if condition"),
    string("while condition"),
    string("<<"),
    string("falsey while condition"),
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
  c->count = c->capacity = 38;
  c->version = 0;
  u8 code[] = {
    OP_CLASS, 0, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 3,
    OP_METHOD, 2,
    OP_CONSTANT, 5,
    OP_METHOD, 4,
    OP_CONSTANT, 7,
    OP_METHOD, 6,
    OP_CONSTANT, 9,
    OP_METHOD, 8,
    OP_CONSTANT, 11,
    OP_METHOD, 10,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 0,
    OP_ASSERT_STACK, 12, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 13;
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
    string("array"),
    fn_array_5(),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *range_lita() {
  return asFunction(fn_src_slash_lita_slash_range_dot_lita_0());
}
