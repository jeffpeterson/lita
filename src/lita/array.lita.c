// clang-format off
// lita -c src/lita/array.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

             // <<
static Value fn__lt__lt__1() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("<<");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 2, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 10;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("push"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // ==
static Value fn__eq__eq__2() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("==");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 4, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 125;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 0,
    OP_EQUAL,
    OP_NOT,
    OP_ASSERT_STACK, 1, 3,
    OP_JUMP_IF_FALSE, 0, 7,
    OP_POP,
    OP_FALSE,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 2,
    OP_EQUAL,
    OP_ASSERT_STACK, 1, 3,
    OP_JUMP_IF_FALSE, 0, 7,
    OP_POP,
    OP_TRUE,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_CONSTANT, 3,
    OP_TRUE,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_LESS,
    OP_ASSERT_STACK, 4, 5,
    OP_JUMP_IF_FALSE, 0, 49,
    OP_POP,
    OP_FALSE,
    OP_SET_LOCAL, 3,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 5,
    OP_GET_LOCAL, 2,
    OP_CALL, 1,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 2,
    OP_DEFAULT, 3,
    OP_PEEK, 0,
    OP_CONSTANT, 6,
    OP_ADD,
    OP_SET_LOCAL, 2,
    OP_POP,
    OP_INVOKE, 5, 1,
    OP_EQUAL,
    OP_NOT,
    OP_ASSERT_STACK, 1, 5,
    OP_JUMP_IF_FALSE, 0, 7,
    OP_POP,
    OP_FALSE,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_LOOP, 0, 62,
    OP_ASSERT_STACK, 7, 5,
    OP_POP,
    OP_JUMP_IF_FALSE, 0, 0,
    OP_POP,
    OP_TRUE,
    OP_RETURN,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 8;
  Value values[] = {
    string("length"),
    string("if condition"),
    string("object_id"),
    NUMBER_VAL(0.000000),
    string("while condition"),
    string("get"),
    NUMBER_VAL(1.000000),
    string("falsey while condition"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // <=>
static Value fn__lt__eq__gt__3() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("<=>");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 12, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 144;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_TRUE,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_LESS,
    OP_ASSERT_STACK, 2, 5,
    OP_JUMP_IF_FALSE, 0, 89,
    OP_POP,
    OP_FALSE,
    OP_SET_LOCAL, 3,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 1,
    OP_GET_LOCAL, 2,
    OP_GREATER,
    OP_NOT,
    OP_ASSERT_STACK, 3, 5,
    OP_JUMP_IF_FALSE, 0, 8,
    OP_POP,
    OP_CONSTANT, 4,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 5,
    OP_GET_LOCAL, 2,
    OP_CALL, 1,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 2,
    OP_DEFAULT, 0,
    OP_PEEK, 0,
    OP_CONSTANT, 4,
    OP_ADD,
    OP_SET_LOCAL, 2,
    OP_POP,
    OP_INVOKE, 5, 1,
    OP_GET_LOCAL, 4,
    OP_GET_LOCAL, 5,
    OP_INVOKE, 6, 1,
    OP_CONSTANT, 0,
    OP_EQUAL,
    OP_NOT,
    OP_ASSERT_STACK, 3, 7,
    OP_JUMP_IF_FALSE, 0, 13,
    OP_POP,
    OP_GET_LOCAL, 4,
    OP_GET_LOCAL, 5,
    OP_INVOKE, 6, 1,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_POP,
    OP_POP,
    OP_LOOP, 0, 102,
    OP_ASSERT_STACK, 7, 5,
    OP_POP,
    OP_JUMP_IF_FALSE, 0, 0,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GREATER,
    OP_ASSERT_STACK, 3, 4,
    OP_JUMP_IF_FALSE, 0, 9,
    OP_POP,
    OP_CONSTANT, 4,
    OP_NEGATE,
    OP_RETURN,
    OP_POP,
    OP_JUMP, 0, 1,
    OP_POP,
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 8;
  Value values[] = {
    NUMBER_VAL(0.000000),
    string("length"),
    string("while condition"),
    string("if condition"),
    NUMBER_VAL(1.000000),
    string("get"),
    string("<=>"),
    string("falsey while condition"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // each
static Value fn_each_4() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("each");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 22, 3));

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
  int lines[] = { 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 27, 27,};
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

             // map
static Value fn_map_5() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("map");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 27, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 68;
  c->version = 1;
  u8 code[] = {
    OP_ARRAY, 0,
    OP_CONSTANT, 0,
    OP_TRUE,
    OP_GET_LOCAL, 3,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_LESS,
    OP_ASSERT_STACK, 2, 6,
    OP_JUMP_IF_FALSE, 0, 36,
    OP_POP,
    OP_FALSE,
    OP_SET_LOCAL, 4,
    OP_POP,
    OP_GET_LOCAL, 2,
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 3,
    OP_GET_LOCAL, 3,
    OP_DEFAULT, 0,
    OP_PEEK, 0,
    OP_CONSTANT, 4,
    OP_ADD,
    OP_SET_LOCAL, 3,
    OP_POP,
    OP_CALL, 1,
    OP_CALL, 1,
    OP_INVOKE, 5, 1,
    OP_POP,
    OP_LOOP, 0, 49,
    OP_ASSERT_STACK, 6, 6,
    OP_POP,
    OP_JUMP_IF_FALSE, 0, 0,
    OP_POP,
    OP_GET_LOCAL, 2,
    OP_RETURN,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 28, 28, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 7;
  Value values[] = {
    NUMBER_VAL(0.000000),
    string("length"),
    string("while condition"),
    string("get"),
    NUMBER_VAL(1.000000),
    string("<<"),
    string("falsey while condition"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // .print
static Value fn__dot_print_7() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 1;
  f->name = newString(".print");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 35, 8));

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
  int lines[] = { 35, 35, 35, 35, 35, 35, 35, 35,};
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
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("print");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 34, 3));

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
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,};
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

             // sample
static Value fn_sample_8() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("sample");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 37, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 19;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_CALL, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("get"),
    string("random"),
    string("length"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // src/lita/array.lita
static Value fn_src_slash_lita_slash_array_dot_lita_0() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/array.lita");
  f->location = asSourceLocation(sourceLocation("src/lita/array.lita", 1, 1));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 46;
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
    OP_CONSTANT, 13,
    OP_METHOD, 12,
    OP_CONSTANT, 15,
    OP_METHOD, 14,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 0,
    OP_ASSERT_STACK, 16, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 10, 10, 10, 10, 20, 20, 20, 20, 27, 27, 27, 27, 32, 32, 32, 32, 35, 35, 35, 35, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 17;
  Value values[] = {
    string("Array"),
    string("Object"),
    string("<<"),
    fn__lt__lt__1(),
    string("=="),
    fn__eq__eq__2(),
    string("<=>"),
    fn__lt__eq__gt__3(),
    string("each"),
    fn_each_4(),
    string("map"),
    fn_map_5(),
    string("print"),
    fn_print_6(),
    string("sample"),
    fn_sample_8(),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *array_lita() {
  return asFunction(fn_src_slash_lita_slash_array_dot_lita_0());
}
