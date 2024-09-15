// clang-format off
// lita -c src/lita/tuple.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

             // *
static Value fn__star__1() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("*");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 11;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("map"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // head
static Value fn_head_2() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("head");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 11;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("get"),
    NUMBER_VAL(0.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // each
static Value fn_each_3() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("each");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 57;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_TRUE,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_LESS,
    OP_ASSERT_STACK, 2, 5,
    OP_JUMP_IF_FALSE, 0, 31,
    OP_POP,
    OP_FALSE,
    OP_SET_LOCAL, 3,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 3,
    OP_GET_LOCAL, 2,
    OP_DEFAULT, 0,
    OP_PEEK, 0,
    OP_CONSTANT, 4,
    OP_ADD,
    OP_SET_LOCAL, 2,
    OP_POP,
    OP_CALL, 1,
    OP_CALL, 1,
    OP_POP,
    OP_LOOP, 0, 44,
    OP_ASSERT_STACK, 5, 5,
    OP_POP,
    OP_JUMP_IF_FALSE, 0, 0,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 6;
  Value values[] = {
    NUMBER_VAL(0.000000),
    string("length"),
    string("while condition"),
    string("get"),
    NUMBER_VAL(1.000000),
    string("falsey while condition"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // zipEach
static Value fn_zipEach_5() {
  ObjFunction *f = newFunction();
  f->arity = 2;
  f->upvalueCount = 2;
  f->name = newString("zipEach");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 16;
  c->version = 1;
  u8 code[] = {
    OP_GET_UPVALUE, 0,
    OP_GET_LOCAL, 1,
    OP_GET_UPVALUE, 1,
    OP_GET_LOCAL, 2,
    OP_INVOKE, 0, 1,
    OP_CALL, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("get"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // zip
static Value fn_zip_4() {
  ObjFunction *f = newFunction();
  f->arity = 2;
  f->upvalueCount = 0;
  f->name = newString("zip");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 18;
  c->version = 1;
  u8 code[] = {
    OP_CLOSURE, 0,
    OP_NIL,
    OP_TRUE,
    OP_NIL,
    OP_NIL,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_LOCAL, 3,
    OP_CALL, 1,
    OP_RETURN,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    fn_zipEach_5(),
    string("map"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // .print
static Value fn__dot_print_7() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 1;
  f->name = newString(".print");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_UPVALUE, 0,
    OP_INVOKE, 0, 1,
    OP_RETURN,
  };
  int lines[] = { 13, 13, 13, 13, 13, 13, 13, 13,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("print"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // print
static Value fn_print_6() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CLOSURE, 1,
    OP_NIL,
    OP_NIL,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("each"),
    fn__dot_print_7(),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // src/lita/tuple.lita
static Value fn_src_slash_lita_slash_tuple_dot_lita_0() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/tuple.lita");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 38;
  c->version = 1;
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
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 9, 9, 9, 9, 11, 11, 11, 11, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 13;
  Value values[] = {
    string("Tuple"),
    string("Object"),
    string("*"),
    fn__star__1(),
    string("head"),
    fn_head_2(),
    string("each"),
    fn_each_3(),
    string("zip"),
    fn_zip_4(),
    string("print"),
    fn_print_6(),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *tuple_lita() {
  return asFunction(fn_src_slash_lita_slash_tuple_dot_lita_0());
}
