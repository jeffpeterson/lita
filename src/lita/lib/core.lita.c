// clang-format off
// lita -c src/lita/lib/core.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

             // !=
static Value fn__not__eq__1() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("!=");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 2, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 9;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_EQUAL,
    OP_NOT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 0;
  Value values[] = {
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // self
static Value fn_self_2() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("self");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 3, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 3, 3, 3, 3, 3,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 0;
  Value values[] = {
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // string
static Value fn_string_3() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 4, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 7;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 4, 4, 4, 4, 4, 4, 4,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("inspect"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // <
static Value fn__lt__4() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("<");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 6, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_INVOKE, 0, 1,
    OP_CONSTANT, 1,
    OP_LESS,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("<=>"),
    NUMBER_VAL(0.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // >
static Value fn__gt__5() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString(">");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 7, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_INVOKE, 0, 1,
    OP_CONSTANT, 1,
    OP_GREATER,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("<=>"),
    NUMBER_VAL(0.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // <=
static Value fn__lt__eq__6() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("<=");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 8, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 14;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_INVOKE, 0, 1,
    OP_CONSTANT, 1,
    OP_GREATER,
    OP_NOT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("<=>"),
    NUMBER_VAL(0.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // >=
static Value fn__gt__eq__7() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString(">=");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 9, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 14;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_INVOKE, 0, 1,
    OP_CONSTANT, 1,
    OP_LESS,
    OP_NOT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("<=>"),
    NUMBER_VAL(0.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // clamp
static Value fn_clamp_8() {
  ObjFunction *f = newFunction();
  f->arity = 2;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("clamp");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 15, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 35;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_LESS,
    OP_JUMP_IF_FALSE, 0, 6,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_JUMP, 0, 18,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 2,
    OP_GREATER,
    OP_JUMP_IF_FALSE, 0, 6,
    OP_POP,
    OP_GET_LOCAL, 2,
    OP_JUMP, 0, 3,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 0;
  Value values[] = {
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // string
static Value fn_string_9() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 18, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 18, 18, 18, 18, 18,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string(""),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // string
static Value fn_string_10() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 27, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 17;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_JUMP_IF_FALSE, 0, 6,
    OP_POP,
    OP_CONSTANT, 0,
    OP_JUMP, 0, 3,
    OP_POP,
    OP_CONSTANT, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("true"),
    string("false"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // print
static Value fn_print_11() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("print");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 28, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 12;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("write"),
    string("string"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // inc
static Value fn_inc_12() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("inc");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 31, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_CONSTANT, 0,
    OP_ADD,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 31, 31, 31, 31, 31, 31, 31, 31,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    NUMBER_VAL(1.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dec
static Value fn_dec_13() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("dec");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 32, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_CONSTANT, 0,
    OP_SUBTRACT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 32, 32, 32, 32, 32, 32, 32, 32,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    NUMBER_VAL(1.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // print
static Value fn_print_14() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("print");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 33, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 12;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("write"),
    string("string"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // .
static Value fn__dot__15() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString(".");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 34, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_MULTIPLY,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 34, 34, 34, 34, 34, 34, 34, 34,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 0;
  Value values[] = {
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // inspect
static Value fn_inspect_16() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 37, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 37, 37, 37, 37, 37,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("{}"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // init
static Value fn_init_17() {
  ObjFunction *f = newFunction();
  f->arity = 3;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 39, 7));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 24;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_SET_PROPERTY, 0,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 2,
    OP_SET_PROPERTY, 1,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 3,
    OP_SET_PROPERTY, 2,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
  };
  int lines[] = { 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("type"),
    string("value"),
    string("targets"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // src/lita/lib/core.lita
static Value fn_src_slash_lita_slash_lib_slash_core_dot_lita_0() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/lib/core.lita");
  f->location = asSourceLocation(sourceLocation("src/lita/lib/core.lita", 1, 1));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 203;
  c->version = 1;
  u8 code[] = {
    OP_CLASS, 0, 0,
    OP_NIL,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 2,
    OP_METHOD, 1,
    OP_CONSTANT, 4,
    OP_METHOD, 3,
    OP_CONSTANT, 6,
    OP_METHOD, 5,
    OP_CONSTANT, 8,
    OP_METHOD, 7,
    OP_CONSTANT, 10,
    OP_METHOD, 9,
    OP_CONSTANT, 12,
    OP_METHOD, 11,
    OP_CONSTANT, 14,
    OP_METHOD, 13,
    OP_CONSTANT, 16,
    OP_METHOD, 15,
    OP_POP,
    OP_POP,
    OP_CLASS, 17, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 18,
    OP_METHOD, 5,
    OP_POP,
    OP_POP,
    OP_CLASS, 19, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 20, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 19,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 21, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 20,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 22, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 20,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 23, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 20,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 24, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 19,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 25,
    OP_METHOD, 5,
    OP_CONSTANT, 27,
    OP_METHOD, 26,
    OP_POP,
    OP_POP,
    OP_CLASS, 28, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 19,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 30,
    OP_METHOD, 29,
    OP_CONSTANT, 32,
    OP_METHOD, 31,
    OP_CONSTANT, 33,
    OP_METHOD, 26,
    OP_CONSTANT, 35,
    OP_METHOD, 34,
    OP_POP,
    OP_POP,
    OP_CLASS, 36, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 19,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 38,
    OP_METHOD, 37,
    OP_POP,
    OP_POP,
    OP_CLASS, 39, 0,
    OP_CONSTANT, 40,
    OP_METHOD, 41,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 19,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 39,
    OP_ASSERT_STACK, 42, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 15, 15, 15, 15, 15, 15, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 43, 43, 43, 43,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 43;
  Value values[] = {
    string("Any"),
    string("!="),
    fn__not__eq__1(),
    string("self"),
    fn_self_2(),
    string("string"),
    fn_string_3(),
    string("<"),
    fn__lt__4(),
    string(">"),
    fn__gt__5(),
    string("<="),
    fn__lt__eq__6(),
    string(">="),
    fn__gt__eq__7(),
    string("clamp"),
    fn_clamp_8(),
    string("Nil"),
    fn_string_9(),
    string("Object"),
    string("Function"),
    string("Method"),
    string("NativeFunction"),
    string("Class"),
    string("Bool"),
    fn_string_10(),
    string("print"),
    fn_print_11(),
    string("Number"),
    string("inc"),
    fn_inc_12(),
    string("dec"),
    fn_dec_13(),
    fn_print_14(),
    string(""),
    fn__dot__15(),
    string("Table"),
    string("inspect"),
    fn_inspect_16(),
    string("Atom"),
    fn_init_17(),
    string("init"),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *core_lita() {
  return asFunction(fn_src_slash_lita_slash_lib_slash_core_dot_lita_0());
}
