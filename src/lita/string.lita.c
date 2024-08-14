// clang-format off
// lita -c src/lita/string.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

static ValueArray constants__slash__1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("/"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk__slash__1() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    14, 0, 0, 0, 24, 14, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants__slash__1();

  return c;
};

             // /
static Value fn__slash__1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("/");
  f->chunk = chunk__slash__1();
  return obj(f);
}

static ValueArray constants_bold_2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[1m"), str("\e[21m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bold_2() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bold_2();

  return c;
};

             // bold
static Value fn_bold_2() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bold");
  f->chunk = chunk_bold_2();
  return obj(f);
}

static ValueArray constants_dim_3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[2m"), str("\e[22m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_dim_3() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_dim_3();

  return c;
};

             // dim
static Value fn_dim_3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("dim");
  f->chunk = chunk_dim_3();
  return obj(f);
}

static ValueArray constants_italic_4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[3m"), str("\e[23m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_italic_4() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_italic_4();

  return c;
};

             // italic
static Value fn_italic_4() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("italic");
  f->chunk = chunk_italic_4();
  return obj(f);
}

static ValueArray constants_underline_5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[4m"), str("\e[24m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_underline_5() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_underline_5();

  return c;
};

             // underline
static Value fn_underline_5() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("underline");
  f->chunk = chunk_underline_5();
  return obj(f);
}

static ValueArray constants_invert_6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[7m"), str("\e[27m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_invert_6() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_invert_6();

  return c;
};

             // invert
static Value fn_invert_6() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("invert");
  f->chunk = chunk_invert_6();
  return obj(f);
}

static ValueArray constants_hide_7() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[8m"), str("\e[28m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_hide_7() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_hide_7();

  return c;
};

             // hide
static Value fn_hide_7() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("hide");
  f->chunk = chunk_hide_7();
  return obj(f);
}

static ValueArray constants_strike_8() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[9m"), str("\e[29m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_strike_8() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    10, 10, 10, 10, 10, 10, 10, 10, 10, 12, 12,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_strike_8();

  return c;
};

             // strike
static Value fn_strike_8() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("strike");
  f->chunk = chunk_strike_8();
  return obj(f);
}

static ValueArray constants_black_9() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[30m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_black_9() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_black_9();

  return c;
};

             // black
static Value fn_black_9() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("black");
  f->chunk = chunk_black_9();
  return obj(f);
}

static ValueArray constants_red_10() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[31m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_red_10() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_red_10();

  return c;
};

             // red
static Value fn_red_10() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("red");
  f->chunk = chunk_red_10();
  return obj(f);
}

static ValueArray constants_green_11() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[32m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_green_11() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_green_11();

  return c;
};

             // green
static Value fn_green_11() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("green");
  f->chunk = chunk_green_11();
  return obj(f);
}

static ValueArray constants_yellow_12() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[33m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_yellow_12() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_yellow_12();

  return c;
};

             // yellow
static Value fn_yellow_12() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("yellow");
  f->chunk = chunk_yellow_12();
  return obj(f);
}

static ValueArray constants_blue_13() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[34m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_blue_13() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_blue_13();

  return c;
};

             // blue
static Value fn_blue_13() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("blue");
  f->chunk = chunk_blue_13();
  return obj(f);
}

static ValueArray constants_magenta_14() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[35m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_magenta_14() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_magenta_14();

  return c;
};

             // magenta
static Value fn_magenta_14() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("magenta");
  f->chunk = chunk_magenta_14();
  return obj(f);
}

static ValueArray constants_cyan_15() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[36m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_cyan_15() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_cyan_15();

  return c;
};

             // cyan
static Value fn_cyan_15() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("cyan");
  f->chunk = chunk_cyan_15();
  return obj(f);
}

static ValueArray constants_white_16() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[37m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_white_16() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    19, 19, 19, 19, 19, 19, 19, 19, 19, 21, 21,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_white_16();

  return c;
};

             // white
static Value fn_white_16() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("white");
  f->chunk = chunk_white_16();
  return obj(f);
}

static ValueArray constants_bg_black_17() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[40m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bg_black_17() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bg_black_17();

  return c;
};

             // bg_black
static Value fn_bg_black_17() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_black");
  f->chunk = chunk_bg_black_17();
  return obj(f);
}

static ValueArray constants_bg_red_18() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[41m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bg_red_18() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bg_red_18();

  return c;
};

             // bg_red
static Value fn_bg_red_18() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_red");
  f->chunk = chunk_bg_red_18();
  return obj(f);
}

static ValueArray constants_bg_green_19() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[42m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bg_green_19() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bg_green_19();

  return c;
};

             // bg_green
static Value fn_bg_green_19() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_green");
  f->chunk = chunk_bg_green_19();
  return obj(f);
}

static ValueArray constants_bg_yellow_20() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[43m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bg_yellow_20() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bg_yellow_20();

  return c;
};

             // bg_yellow
static Value fn_bg_yellow_20() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_yellow");
  f->chunk = chunk_bg_yellow_20();
  return obj(f);
}

static ValueArray constants_bg_blue_21() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[44m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bg_blue_21() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bg_blue_21();

  return c;
};

             // bg_blue
static Value fn_bg_blue_21() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_blue");
  f->chunk = chunk_bg_blue_21();
  return obj(f);
}

static ValueArray constants_bg_magenta_22() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[45m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bg_magenta_22() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bg_magenta_22();

  return c;
};

             // bg_magenta
static Value fn_bg_magenta_22() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_magenta");
  f->chunk = chunk_bg_magenta_22();
  return obj(f);
}

static ValueArray constants_bg_cyan_23() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[46m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bg_cyan_23() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bg_cyan_23();

  return c;
};

             // bg_cyan
static Value fn_bg_cyan_23() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_cyan");
  f->chunk = chunk_bg_cyan_23();
  return obj(f);
}

static ValueArray constants_bg_white_24() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[47m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_bg_white_24() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_bg_white_24();

  return c;
};

             // bg_white
static Value fn_bg_white_24() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_white");
  f->chunk = chunk_bg_white_24();
  return obj(f);
}

static ValueArray constants_src_slash_lita_slash_string_dot_lita_0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 50;
  Value values[] = {
    str("String"), str("Object"), str("/"), fn__slash__1(), str("bold"), fn_bold_2(), str("dim"), fn_dim_3(), str("italic"), fn_italic_4(), str("underline"), fn_underline_5(), str("invert"), fn_invert_6(), str("hide"), fn_hide_7(), str("strike"), fn_strike_8(), str("black"), fn_black_9(), str("red"), fn_red_10(), str("green"), fn_green_11(), str("yellow"), fn_yellow_12(), str("blue"), fn_blue_13(), str("magenta"), fn_magenta_14(), str("cyan"), fn_cyan_15(), str("white"), fn_white_16(), str("bg_black"), fn_bg_black_17(), str("bg_red"), fn_bg_red_18(), str("bg_green"), fn_bg_green_19(), str("bg_yellow"), fn_bg_yellow_20(), str("bg_blue"), fn_bg_blue_21(), str("bg_magenta"), fn_bg_magenta_22(), str("bg_cyan"), fn_bg_cyan_23(), str("bg_white"), fn_bg_white_24(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk chunk_src_slash_lita_slash_string_dot_lita_0() {
  Chunk c;
  initChunk(&c);
  c.count = 110;
  c.capacity = 110;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 37, 5, 36, 4, 37, 7, 36, 6, 37, 9, 36, 8, 37, 11, 36, 10, 37, 13, 36, 12, 37, 15, 36, 14, 37, 17, 36, 16, 37, 19, 36, 18, 37, 21, 36, 20, 37, 23, 36, 22, 37, 25, 36, 24, 37, 27, 36, 26, 37, 29, 36, 28, 37, 31, 36, 30, 37, 33, 36, 32, 37, 35, 36, 34, 37, 37, 36, 36, 37, 39, 36, 38, 37, 41, 36, 40, 37, 43, 36, 42, 37, 45, 36, 44, 37, 47, 36, 46, 37, 49, 36, 48, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = constants_src_slash_lita_slash_string_dot_lita_0();

  return c;
};

             // src/lita/string.lita
static Value fn_src_slash_lita_slash_string_dot_lita_0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src/lita/string.lita");
  f->chunk = chunk_src_slash_lita_slash_string_dot_lita_0();
  return obj(f);
}

ObjFun *string_lita() {
  return AS_FUN(fn_src_slash_lita_slash_string_dot_lita_0());
}
