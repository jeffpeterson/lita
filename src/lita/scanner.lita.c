// clang-format off
// lita -c src/lita/scanner.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

             // reset_scanner
static Value fn_reset_scanner_1() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("reset_scanner");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 3, 4));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_GLOBAL, 1,
    OP_GET_GLOBAL, 0,
    OP_GET_PROPERTY, 2,
    OP_CALL, 1,
    OP_SET_GLOBAL, 0,
    OP_POP,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("scanner"),
    string("Scanner"),
    string("source"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // init
static Value fn_init_2() {
  ObjFunction *f = newFunction();
  f->arity = 4;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 6, 7));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 31;
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
    OP_GET_LOCAL, 4,
    OP_SET_PROPERTY, 3,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
  };
  int lines[] = { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 4;
  Value values[] = {
    string("type"),
    string("escaped"),
    string("source"),
    string("line"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // previous
static Value fn_previous_3() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("previous");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 13, 15));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_SET_PROPERTY, 8,
    OP_RETURN,
  };
  int lines[] = { 13, 13, 13, 13, 13,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    NUMBER_VAL(0.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // current
static Value fn_current_4() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("current");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 14, 14));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_SET_PROPERTY, 10,
    OP_RETURN,
  };
  int lines[] = { 14, 14, 14, 14, 14,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    NUMBER_VAL(0.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // inside
static Value fn_inside_5() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("inside");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 15, 13));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 4;
  c->version = 1;
  u8 code[] = {
    OP_TRUE,
    OP_SET_PROPERTY, 12,
    OP_RETURN,
  };
  int lines[] = { 15, 15, 15, 15,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 0;
  Value values[] = {
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // position
static Value fn_position_6() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("position");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 19, 15));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 8;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_CONSTANT, 0,
    OP_RANGE,
    OP_SET_PROPERTY, 15,
    OP_RETURN,
  };
  int lines[] = { 19, 19, 19, 19, 19, 19, 19, 19,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    NUMBER_VAL(0.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // line
static Value fn_line_7() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("line");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 20, 11));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 5;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_SET_PROPERTY, 17,
    OP_RETURN,
  };
  int lines[] = { 20, 20, 20, 20, 20,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    NUMBER_VAL(1.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // indent
static Value fn_indent_8() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("indent");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 21, 13));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 9;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CALL, 0,
    OP_SET_PROPERTY, 19,
    OP_RETURN,
  };
  int lines[] = { 21, 21, 21, 21, 21, 21, 21, 21, 21,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("Indent"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // init
static Value fn_init_9() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 24, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 20;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_LOCAL, 1,
    OP_SET_VAR, 0,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 2,
    OP_POP,
    OP_GET_LOCAL, 0,
    OP_RETURN,
  };
  int lines[] = { 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("source"),
    string("skip_shebang"),
    string("skip_whitespace"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // current
static Value fn_current_10() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("current");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 29, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 17;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 1,
    OP_GET_PROPERTY, 2,
    OP_ARRAY, 3,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 4;
  Value values[] = {
    string("source"),
    string("span"),
    string("end"),
    NUMBER_VAL(1.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // is_at_end
static Value fn_is_at_end_11() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("is_at_end");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 30, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 24;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_PROPERTY, 1,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_PROPERTY, 2,
    OP_ADD,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 3,
    OP_GET_PROPERTY, 4,
    OP_LESS,
    OP_NOT,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 5;
  Value values[] = {
    string("position"),
    string("start"),
    string("end"),
    string("source"),
    string("length"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // isAlpha
static Value fn_isAlpha_12() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("isAlpha");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 32, 4));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 43;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_RANGE,
    OP_INVOKE, 0, 1,
    OP_JUMP_IF_FALSE, 0, 3,
    OP_JUMP, 0, 12,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 0,
    OP_CONSTANT, 3,
    OP_CONSTANT, 4,
    OP_RANGE,
    OP_CALL, 1,
    OP_JUMP_IF_FALSE, 0, 3,
    OP_JUMP, 0, 6,
    OP_POP,
    OP_GET_LOCAL, 1,
    OP_CONSTANT, 5,
    OP_EQUAL,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 6;
  Value values[] = {
    string("in"),
    string("a"),
    string("z"),
    string("A"),
    string("Z"),
    string("_'"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // isDigit
static Value fn_isDigit_13() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("isDigit");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 33, 4));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 14;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_RANGE,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("in"),
    string("0"),
    string("9"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // isSubscript
static Value fn_isSubscript_14() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("isSubscript");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 34, 4));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 14;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_PROPERTY, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_RANGE,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("in"),
    NUMBER_VAL(8320.000000),
    NUMBER_VAL(8329.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // src/lita/scanner.lita
static Value fn_src_slash_lita_slash_scanner_dot_lita_0() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/scanner.lita");
  f->location = asSourceLocation(sourceLocation("src/lita/scanner.lita", 1, 1));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 101;
  c->version = 1;
  u8 code[] = {
    OP_NIL,
    OP_DEFINE_GLOBAL, 0,
    OP_CONSTANT, 2,
    OP_DEFINE_GLOBAL, 1,
    OP_CLASS, 3, 0,
    OP_CONSTANT, 4,
    OP_METHOD, 5,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_POP,
    OP_POP,
    OP_CLASS, 7, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 9,
    OP_METHOD, 8,
    OP_CONSTANT, 11,
    OP_METHOD, 10,
    OP_CONSTANT, 13,
    OP_METHOD, 12,
    OP_POP,
    OP_POP,
    OP_CLASS, 14, 0,
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 6,
    OP_INHERIT,
    OP_SWAP, 1,
    OP_CONSTANT, 16,
    OP_METHOD, 15,
    OP_CONSTANT, 18,
    OP_METHOD, 17,
    OP_CONSTANT, 20,
    OP_METHOD, 19,
    OP_CONSTANT, 21,
    OP_METHOD, 5,
    OP_CONSTANT, 22,
    OP_METHOD, 10,
    OP_CONSTANT, 24,
    OP_METHOD, 23,
    OP_POP,
    OP_POP,
    OP_CONSTANT, 26,
    OP_DEFINE_GLOBAL, 25,
    OP_CONSTANT, 28,
    OP_DEFINE_GLOBAL, 27,
    OP_CONSTANT, 30,
    OP_PEEK, 0,
    OP_DEFINE_GLOBAL, 29,
    OP_ASSERT_STACK, 31, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10, 10, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 27, 27, 27, 27, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 54, 54, 54, 54,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 32;
  Value values[] = {
    string("scanner"),
    string("reset_scanner"),
    fn_reset_scanner_1(),
    string("Token"),
    fn_init_2(),
    string("init"),
    string("Object"),
    string("Indent"),
    string("previous"),
    fn_previous_3(),
    string("current"),
    fn_current_4(),
    string("inside"),
    fn_inside_5(),
    string("Scanner"),
    string("position"),
    fn_position_6(),
    string("line"),
    fn_line_7(),
    string("indent"),
    fn_indent_8(),
    fn_init_9(),
    fn_current_10(),
    string("is_at_end"),
    fn_is_at_end_11(),
    string("isAlpha"),
    fn_isAlpha_12(),
    string("isDigit"),
    fn_isDigit_13(),
    string("isSubscript"),
    fn_isSubscript_14(),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *scanner_lita() {
  return asFunction(fn_src_slash_lita_slash_scanner_dot_lita_0());
}
