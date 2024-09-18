// clang-format off
// lita -c src/lita/string.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"
#include "lita/vm.h"

#if ENABLE_REGEX
#include "lita/regex.h"
#endif

             // /
static Value fn__slash__1() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("/");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 2, 2));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_CONSTANT, 0,
    OP_CALL, 1,
    OP_GET_LOCAL, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("/"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // byte
static Value fn_byte_2() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("byte");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 3, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_GET_LOCAL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("slice"),
    NUMBER_VAL(1.000000),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bold
static Value fn_bold_3() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bold");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 5, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[1m"),
    string("\e[21m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dim
static Value fn_dim_4() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("dim");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 6, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[2m"),
    string("\e[22m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // italic
static Value fn_italic_5() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("italic");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 7, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[3m"),
    string("\e[23m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // underline
static Value fn_underline_6() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("underline");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 8, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[4m"),
    string("\e[24m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // invert
static Value fn_invert_7() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("invert");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 9, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[7m"),
    string("\e[27m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // hide
static Value fn_hide_8() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("hide");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 10, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[8m"),
    string("\e[28m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // strike
static Value fn_strike_9() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("strike");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 11, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[9m"),
    string("\e[29m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // black
static Value fn_black_10() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("black");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 13, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
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
    string("\e[30m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // red
static Value fn_red_11() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("red");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 14, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[31m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // green
static Value fn_green_12() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("green");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 15, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[32m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // yellow
static Value fn_yellow_13() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("yellow");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 16, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[33m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // blue
static Value fn_blue_14() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("blue");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 17, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[34m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // magenta
static Value fn_magenta_15() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("magenta");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 18, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[35m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // cyan
static Value fn_cyan_16() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("cyan");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 19, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[36m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // white
static Value fn_white_17() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("white");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 20, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[37m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_black
static Value fn_bg_black_18() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_black");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 22, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[40m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_red
static Value fn_bg_red_19() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_red");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 23, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[41m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_green
static Value fn_bg_green_20() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_green");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 24, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[42m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_yellow
static Value fn_bg_yellow_21() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_yellow");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 25, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[43m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_blue
static Value fn_bg_blue_22() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_blue");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 26, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[44m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_magenta
static Value fn_bg_magenta_23() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_magenta");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 27, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[45m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_cyan
static Value fn_bg_cyan_24() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_cyan");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 28, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[46m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_white
static Value fn_bg_white_25() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_white");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 29, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_CONSTANT, 0,
    OP_GET_LOCAL, 0,
    OP_CALL, 1,
    OP_CONSTANT, 1,
    OP_CALL, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 2;
  Value values[] = {
    string("\e[47m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // uppercase
static Value fn_uppercase_26() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("uppercase");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 31, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_CALL, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("replace"),
    regex("\\w+"),
    string("\\U$0"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // lowercase
static Value fn_lowercase_27() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("lowercase");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 32, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_CALL, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("replace"),
    regex("\\w+"),
    string("\\L$0"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // capitalize
static Value fn_capitalize_28() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("capitalize");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 33, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_CALL, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("replace"),
    regex("^(\\W*?)([a-z])"),
    string("$1\\u$2"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // decapitalize
static Value fn_decapitalize_29() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("decapitalize");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 34, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_CALL, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("replace"),
    regex("^(\\W*?)([A-Z])"),
    string("$1\\l$2"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // camelize
static Value fn_camelize_30() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("camelize");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 35, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_CALL, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 3;
  Value values[] = {
    string("replace"),
    regex("_(\\w)"),
    string("\\u$1"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // underscore
static Value fn_underscore_31() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("underscore");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 36, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 22;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 1,
    OP_CONSTANT, 2,
    OP_CALL, 2,
    OP_CONSTANT, 3,
    OP_CONSTANT, 4,
    OP_INVOKE, 0, 2,
    OP_GET_PROPERTY, 5,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 6;
  Value values[] = {
    string("replace"),
    regex("([a-zA-Z])([A-Z][a-z])"),
    string("$1_\\l$2"),
    regex("-"),
    string("_"),
    string("lowercase"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // dasherize
static Value fn_dasherize_32() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("dasherize");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 37, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 14;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 0,
    OP_GET_VAR, 0,
    OP_CONSTANT, 2,
    OP_CONSTANT, 3,
    OP_INVOKE, 1, 2,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 4;
  Value values[] = {
    string("underscore"),
    string("replace"),
    regex("_"),
    string("-"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // print
static Value fn_print_33() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("print");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 39, 3));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 10;
  c->version = 1;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 1;
  Value values[] = {
    string("write"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // src/lita/string.lita
static Value fn_src_slash_lita_slash_string_dot_lita_0() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->variadic = 0;
  f->upvalueCount = 0;
  f->name = newString("src/lita/string.lita");
  f->location = asSourceLocation(sourceLocation("src/lita/string.lita", 1, 1));

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 150;
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
    OP_CONSTANT, 17,
    OP_METHOD, 16,
    OP_CONSTANT, 19,
    OP_METHOD, 18,
    OP_CONSTANT, 21,
    OP_METHOD, 20,
    OP_CONSTANT, 23,
    OP_METHOD, 22,
    OP_CONSTANT, 25,
    OP_METHOD, 24,
    OP_CONSTANT, 27,
    OP_METHOD, 26,
    OP_CONSTANT, 29,
    OP_METHOD, 28,
    OP_CONSTANT, 31,
    OP_METHOD, 30,
    OP_CONSTANT, 33,
    OP_METHOD, 32,
    OP_CONSTANT, 35,
    OP_METHOD, 34,
    OP_CONSTANT, 37,
    OP_METHOD, 36,
    OP_CONSTANT, 39,
    OP_METHOD, 38,
    OP_CONSTANT, 41,
    OP_METHOD, 40,
    OP_CONSTANT, 43,
    OP_METHOD, 42,
    OP_CONSTANT, 45,
    OP_METHOD, 44,
    OP_CONSTANT, 47,
    OP_METHOD, 46,
    OP_CONSTANT, 49,
    OP_METHOD, 48,
    OP_CONSTANT, 51,
    OP_METHOD, 50,
    OP_CONSTANT, 53,
    OP_METHOD, 52,
    OP_CONSTANT, 55,
    OP_METHOD, 54,
    OP_CONSTANT, 57,
    OP_METHOD, 56,
    OP_CONSTANT, 59,
    OP_METHOD, 58,
    OP_CONSTANT, 61,
    OP_METHOD, 60,
    OP_CONSTANT, 63,
    OP_METHOD, 62,
    OP_CONSTANT, 65,
    OP_METHOD, 64,
    OP_CONSTANT, 67,
    OP_METHOD, 66,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 0,
    OP_ASSERT_STACK, 68, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 31, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 69;
  Value values[] = {
    string("String"),
    string("Object"),
    string("/"),
    fn__slash__1(),
    string("byte"),
    fn_byte_2(),
    string("bold"),
    fn_bold_3(),
    string("dim"),
    fn_dim_4(),
    string("italic"),
    fn_italic_5(),
    string("underline"),
    fn_underline_6(),
    string("invert"),
    fn_invert_7(),
    string("hide"),
    fn_hide_8(),
    string("strike"),
    fn_strike_9(),
    string("black"),
    fn_black_10(),
    string("red"),
    fn_red_11(),
    string("green"),
    fn_green_12(),
    string("yellow"),
    fn_yellow_13(),
    string("blue"),
    fn_blue_14(),
    string("magenta"),
    fn_magenta_15(),
    string("cyan"),
    fn_cyan_16(),
    string("white"),
    fn_white_17(),
    string("bg_black"),
    fn_bg_black_18(),
    string("bg_red"),
    fn_bg_red_19(),
    string("bg_green"),
    fn_bg_green_20(),
    string("bg_yellow"),
    fn_bg_yellow_21(),
    string("bg_blue"),
    fn_bg_blue_22(),
    string("bg_magenta"),
    fn_bg_magenta_23(),
    string("bg_cyan"),
    fn_bg_cyan_24(),
    string("bg_white"),
    fn_bg_white_25(),
    string("uppercase"),
    fn_uppercase_26(),
    string("lowercase"),
    fn_lowercase_27(),
    string("capitalize"),
    fn_capitalize_28(),
    string("decapitalize"),
    fn_decapitalize_29(),
    string("camelize"),
    fn_camelize_30(),
    string("underscore"),
    fn_underscore_31(),
    string("dasherize"),
    fn_dasherize_32(),
    string("print"),
    fn_print_33(),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *string_lita() {
  return asFunction(fn_src_slash_lita_slash_string_dot_lita_0());
}
