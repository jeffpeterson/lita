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
  f->upvalueCount = 0;
  f->name = newString("/");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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

             // bold
static Value fn_bold_2() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bold");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
  int lines[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,};
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
static Value fn_dim_3() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dim");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[2m"),
    string("\e[22m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // italic
static Value fn_italic_4() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("italic");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[3m"),
    string("\e[23m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // underline
static Value fn_underline_5() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("underline");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[4m"),
    string("\e[24m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // invert
static Value fn_invert_6() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("invert");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[7m"),
    string("\e[27m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // hide
static Value fn_hide_7() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("hide");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[8m"),
    string("\e[28m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // strike
static Value fn_strike_8() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("strike");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[9m"),
    string("\e[29m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // black
static Value fn_black_9() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("black");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
  int lines[] = { 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,};
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
static Value fn_red_10() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("red");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[31m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // green
static Value fn_green_11() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("green");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[32m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // yellow
static Value fn_yellow_12() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("yellow");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[33m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // blue
static Value fn_blue_13() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("blue");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[34m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // magenta
static Value fn_magenta_14() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("magenta");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[35m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // cyan
static Value fn_cyan_15() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("cyan");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[36m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // white
static Value fn_white_16() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("white");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[37m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_black
static Value fn_bg_black_17() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_black");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
  int lines[] = { 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,};
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
static Value fn_bg_red_18() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_red");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[41m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_green
static Value fn_bg_green_19() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_green");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[42m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_yellow
static Value fn_bg_yellow_20() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_yellow");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[43m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_blue
static Value fn_bg_blue_21() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_blue");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[44m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_magenta
static Value fn_bg_magenta_22() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_magenta");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[45m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_cyan
static Value fn_bg_cyan_23() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_cyan");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[46m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // bg_white
static Value fn_bg_white_24() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_white");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\e[47m"),
    string("\e[39m"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // uppercase
static Value fn_uppercase_25() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("uppercase");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
  int lines[] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,};
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
static Value fn_lowercase_26() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("lowercase");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    string("\\L$0"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // capitalize
static Value fn_capitalize_27() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("capitalize");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    regex("^(\\W*?)([a-z])"),
    string("$1\\u$2"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // decapitalize
static Value fn_decapitalize_28() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("decapitalize");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    regex("^(\\W*?)([A-Z])"),
    string("$1\\l$2"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // camelize
static Value fn_camelize_29() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("camelize");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 13;
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
    regex("_(\\w)"),
    string("\\u$1"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

             // underscore
static Value fn_underscore_30() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("underscore");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 22;
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
  int lines[] = { 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,};
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
static Value fn_dasherize_31() {
  ObjFunction *f = newFunction();
  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dasherize");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 14;
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
  int lines[] = { 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,};
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
static Value fn_print_32() {
  ObjFunction *f = newFunction();
  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("print");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 10;
  u8 code[] = {
    OP_GET_LOCAL, 1,
    OP_GET_LOCAL, 0,
    OP_INVOKE, 0, 1,
    OP_RETURN,
    OP_NIL,
    OP_RETURN,
  };
  int lines[] = { 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,};
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
  f->upvalueCount = 0;
  f->name = newString("src/lita/string.lita");

  Chunk *c = &f->chunk;
  initChunk(c);
  c->count = c->capacity = 146;
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
    OP_CLOSURE, 11,
    OP_METHOD, 10,
    OP_CLOSURE, 13,
    OP_METHOD, 12,
    OP_CLOSURE, 15,
    OP_METHOD, 14,
    OP_CLOSURE, 17,
    OP_METHOD, 16,
    OP_CLOSURE, 19,
    OP_METHOD, 18,
    OP_CLOSURE, 21,
    OP_METHOD, 20,
    OP_CLOSURE, 23,
    OP_METHOD, 22,
    OP_CLOSURE, 25,
    OP_METHOD, 24,
    OP_CLOSURE, 27,
    OP_METHOD, 26,
    OP_CLOSURE, 29,
    OP_METHOD, 28,
    OP_CLOSURE, 31,
    OP_METHOD, 30,
    OP_CLOSURE, 33,
    OP_METHOD, 32,
    OP_CLOSURE, 35,
    OP_METHOD, 34,
    OP_CLOSURE, 37,
    OP_METHOD, 36,
    OP_CLOSURE, 39,
    OP_METHOD, 38,
    OP_CLOSURE, 41,
    OP_METHOD, 40,
    OP_CLOSURE, 43,
    OP_METHOD, 42,
    OP_CLOSURE, 45,
    OP_METHOD, 44,
    OP_CLOSURE, 47,
    OP_METHOD, 46,
    OP_CLOSURE, 49,
    OP_METHOD, 48,
    OP_CLOSURE, 51,
    OP_METHOD, 50,
    OP_CLOSURE, 53,
    OP_METHOD, 52,
    OP_CLOSURE, 55,
    OP_METHOD, 54,
    OP_CLOSURE, 57,
    OP_METHOD, 56,
    OP_CLOSURE, 59,
    OP_METHOD, 58,
    OP_CLOSURE, 61,
    OP_METHOD, 60,
    OP_CLOSURE, 63,
    OP_METHOD, 62,
    OP_CLOSURE, 65,
    OP_METHOD, 64,
    OP_POP,
    OP_POP,
    OP_GET_GLOBAL, 0,
    OP_ASSERT_STACK, 66, 2,
    OP_RETURN,
  };
  int lines[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39,};
  c->code = cloneMemory(code, sizeof(code));
  c->lines = cloneMemory(lines, sizeof(lines));

  c->constants.count = c->constants.capacity = 67;
  Value values[] = {
    string("String"),
    string("Object"),
    string("/"),
    fn__slash__1(),
    string("bold"),
    fn_bold_2(),
    string("dim"),
    fn_dim_3(),
    string("italic"),
    fn_italic_4(),
    string("underline"),
    fn_underline_5(),
    string("invert"),
    fn_invert_6(),
    string("hide"),
    fn_hide_7(),
    string("strike"),
    fn_strike_8(),
    string("black"),
    fn_black_9(),
    string("red"),
    fn_red_10(),
    string("green"),
    fn_green_11(),
    string("yellow"),
    fn_yellow_12(),
    string("blue"),
    fn_blue_13(),
    string("magenta"),
    fn_magenta_14(),
    string("cyan"),
    fn_cyan_15(),
    string("white"),
    fn_white_16(),
    string("bg_black"),
    fn_bg_black_17(),
    string("bg_red"),
    fn_bg_red_18(),
    string("bg_green"),
    fn_bg_green_19(),
    string("bg_yellow"),
    fn_bg_yellow_20(),
    string("bg_blue"),
    fn_bg_blue_21(),
    string("bg_magenta"),
    fn_bg_magenta_22(),
    string("bg_cyan"),
    fn_bg_cyan_23(),
    string("bg_white"),
    fn_bg_white_24(),
    string("uppercase"),
    fn_uppercase_25(),
    string("lowercase"),
    fn_lowercase_26(),
    string("capitalize"),
    fn_capitalize_27(),
    string("decapitalize"),
    fn_decapitalize_28(),
    string("camelize"),
    fn_camelize_29(),
    string("underscore"),
    fn_underscore_30(),
    string("dasherize"),
    fn_dasherize_31(),
    string("print"),
    fn_print_32(),
    string("script return value"),
  };
  c->constants.values = cloneMemory(values, sizeof(values));
  return obj(f);
}

ObjFunction *string_lita() {
  return asFunction(fn_src_slash_lita_slash_string_dot_lita_0());
}
