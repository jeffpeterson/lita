// clang-format off
// lita -c src/lita/string.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

// string
static ValueArray constants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// string
static Chunk chunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    14, 0, 40, 1, 40,
  };
  int lines[] = {
    2, 2, 2, 3, 3,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // string
  c.constants = constants1();

  return c;
};

// string
static Value fn1() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("string");
             // string
  f->chunk = chunk1();
  return obj(f);
}

// +
static ValueArray constants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("concat"), str("string"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// +
static Chunk chunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 13;
  c.capacity = 13;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 16, 1, 33, 1, 40, 1, 40,
  };
  int lines[] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // +
  c.constants = constants2();

  return c;
};

// +
static Value fn2() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("+");
             // +
  f->chunk = chunk2();
  return obj(f);
}

// *
static ValueArray constants3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("concat"), str("string"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// *
static Chunk chunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 13;
  c.capacity = 13;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 16, 1, 33, 1, 40, 1, 40,
  };
  int lines[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // *
  c.constants = constants3();

  return c;
};

// *
static Value fn3() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("*");
             // *
  f->chunk = chunk3();
  return obj(f);
}

// /
static ValueArray constants4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("/"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// /
static Chunk chunk4() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    14, 0, 0, 0, 24, 14, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // /
  c.constants = constants4();

  return c;
};

// /
static Value fn4() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = new_string("/");
             // /
  f->chunk = chunk4();
  return obj(f);
}

// bold
static ValueArray constants5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[1m"), str("\e[21m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bold
static Chunk chunk5() {
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
                // bold
  c.constants = constants5();

  return c;
};

// bold
static Value fn5() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bold");
             // bold
  f->chunk = chunk5();
  return obj(f);
}

// dim
static ValueArray constants6() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[2m"), str("\e[22m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// dim
static Chunk chunk6() {
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
                // dim
  c.constants = constants6();

  return c;
};

// dim
static Value fn6() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("dim");
             // dim
  f->chunk = chunk6();
  return obj(f);
}

// italic
static ValueArray constants7() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[3m"), str("\e[23m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// italic
static Chunk chunk7() {
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
                // italic
  c.constants = constants7();

  return c;
};

// italic
static Value fn7() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("italic");
             // italic
  f->chunk = chunk7();
  return obj(f);
}

// underline
static ValueArray constants8() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[4m"), str("\e[24m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// underline
static Chunk chunk8() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // underline
  c.constants = constants8();

  return c;
};

// underline
static Value fn8() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("underline");
             // underline
  f->chunk = chunk8();
  return obj(f);
}

// invert
static ValueArray constants9() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[7m"), str("\e[27m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// invert
static Chunk chunk9() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // invert
  c.constants = constants9();

  return c;
};

// invert
static Value fn9() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("invert");
             // invert
  f->chunk = chunk9();
  return obj(f);
}

// hide
static ValueArray constants10() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[8m"), str("\e[28m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// hide
static Chunk chunk10() {
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
                // hide
  c.constants = constants10();

  return c;
};

// hide
static Value fn10() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("hide");
             // hide
  f->chunk = chunk10();
  return obj(f);
}

// strike
static ValueArray constants11() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[9m"), str("\e[29m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// strike
static Chunk chunk11() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    13, 13, 13, 13, 13, 13, 13, 13, 13, 15, 15,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // strike
  c.constants = constants11();

  return c;
};

// strike
static Value fn11() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("strike");
             // strike
  f->chunk = chunk11();
  return obj(f);
}

// black
static ValueArray constants12() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[30m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// black
static Chunk chunk12() {
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
                // black
  c.constants = constants12();

  return c;
};

// black
static Value fn12() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("black");
             // black
  f->chunk = chunk12();
  return obj(f);
}

// red
static ValueArray constants13() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[31m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// red
static Chunk chunk13() {
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
                // red
  c.constants = constants13();

  return c;
};

// red
static Value fn13() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("red");
             // red
  f->chunk = chunk13();
  return obj(f);
}

// green
static ValueArray constants14() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[32m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// green
static Chunk chunk14() {
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
                // green
  c.constants = constants14();

  return c;
};

// green
static Value fn14() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("green");
             // green
  f->chunk = chunk14();
  return obj(f);
}

// yellow
static ValueArray constants15() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[33m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// yellow
static Chunk chunk15() {
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
                // yellow
  c.constants = constants15();

  return c;
};

// yellow
static Value fn15() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("yellow");
             // yellow
  f->chunk = chunk15();
  return obj(f);
}

// blue
static ValueArray constants16() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[34m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// blue
static Chunk chunk16() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // blue
  c.constants = constants16();

  return c;
};

// blue
static Value fn16() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("blue");
             // blue
  f->chunk = chunk16();
  return obj(f);
}

// magenta
static ValueArray constants17() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[35m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// magenta
static Chunk chunk17() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // magenta
  c.constants = constants17();

  return c;
};

// magenta
static Value fn17() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("magenta");
             // magenta
  f->chunk = chunk17();
  return obj(f);
}

// cyan
static ValueArray constants18() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[36m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// cyan
static Chunk chunk18() {
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
                // cyan
  c.constants = constants18();

  return c;
};

// cyan
static Value fn18() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("cyan");
             // cyan
  f->chunk = chunk18();
  return obj(f);
}

// white
static ValueArray constants19() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[37m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// white
static Chunk chunk19() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    22, 22, 22, 22, 22, 22, 22, 22, 22, 24, 24,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // white
  c.constants = constants19();

  return c;
};

// white
static Value fn19() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("white");
             // white
  f->chunk = chunk19();
  return obj(f);
}

// bg_black
static ValueArray constants20() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[40m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bg_black
static Chunk chunk20() {
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
                // bg_black
  c.constants = constants20();

  return c;
};

// bg_black
static Value fn20() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_black");
             // bg_black
  f->chunk = chunk20();
  return obj(f);
}

// bg_red
static ValueArray constants21() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[41m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bg_red
static Chunk chunk21() {
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
                // bg_red
  c.constants = constants21();

  return c;
};

// bg_red
static Value fn21() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_red");
             // bg_red
  f->chunk = chunk21();
  return obj(f);
}

// bg_green
static ValueArray constants22() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[42m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bg_green
static Chunk chunk22() {
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
                // bg_green
  c.constants = constants22();

  return c;
};

// bg_green
static Value fn22() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_green");
             // bg_green
  f->chunk = chunk22();
  return obj(f);
}

// bg_yellow
static ValueArray constants23() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[43m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bg_yellow
static Chunk chunk23() {
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
                // bg_yellow
  c.constants = constants23();

  return c;
};

// bg_yellow
static Value fn23() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_yellow");
             // bg_yellow
  f->chunk = chunk23();
  return obj(f);
}

// bg_blue
static ValueArray constants24() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[44m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bg_blue
static Chunk chunk24() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_blue
  c.constants = constants24();

  return c;
};

// bg_blue
static Value fn24() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_blue");
             // bg_blue
  f->chunk = chunk24();
  return obj(f);
}

// bg_magenta
static ValueArray constants25() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[45m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bg_magenta
static Chunk chunk25() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_magenta
  c.constants = constants25();

  return c;
};

// bg_magenta
static Value fn25() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_magenta");
             // bg_magenta
  f->chunk = chunk25();
  return obj(f);
}

// bg_cyan
static ValueArray constants26() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[46m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bg_cyan
static Chunk chunk26() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_cyan
  c.constants = constants26();

  return c;
};

// bg_cyan
static Value fn26() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_cyan");
             // bg_cyan
  f->chunk = chunk26();
  return obj(f);
}

// bg_white
static ValueArray constants27() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("\e[47m"), str("\e[39m"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// bg_white
static Chunk chunk27() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_white
  c.constants = constants27();

  return c;
};

// bg_white
static Value fn27() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("bg_white");
             // bg_white
  f->chunk = chunk27();
  return obj(f);
}

// src_lita_string_lita
static ValueArray constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 56;
  Value values[] = {
    str("String"), str("Object"), str("string"), /*string*/fn1(), str("+"), /*+*/fn2(), str("*"), /***/fn3(), str("/"), /*/*/fn4(), str("bold"), /*bold*/fn5(), str("dim"), /*dim*/fn6(), str("italic"), /*italic*/fn7(), str("underline"), /*underline*/fn8(), str("invert"), /*invert*/fn9(), str("hide"), /*hide*/fn10(), str("strike"), /*strike*/fn11(), str("black"), /*black*/fn12(), str("red"), /*red*/fn13(), str("green"), /*green*/fn14(), str("yellow"), /*yellow*/fn15(), str("blue"), /*blue*/fn16(), str("magenta"), /*magenta*/fn17(), str("cyan"), /*cyan*/fn18(), str("white"), /*white*/fn19(), str("bg_black"), /*bg_black*/fn20(), str("bg_red"), /*bg_red*/fn21(), str("bg_green"), /*bg_green*/fn22(), str("bg_yellow"), /*bg_yellow*/fn23(), str("bg_blue"), /*bg_blue*/fn24(), str("bg_magenta"), /*bg_magenta*/fn25(), str("bg_cyan"), /*bg_cyan*/fn26(), str("bg_white"), /*bg_white*/fn27(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// src_lita_string_lita
static Chunk chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 122;
  c.capacity = 122;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 37, 5, 36, 4, 37, 7, 36, 6, 37, 9, 36, 8, 37, 11, 36, 10, 37, 13, 36, 12, 37, 15, 36, 14, 37, 17, 36, 16, 37, 19, 36, 18, 37, 21, 36, 20, 37, 23, 36, 22, 37, 25, 36, 24, 37, 27, 36, 26, 37, 29, 36, 28, 37, 31, 36, 30, 37, 33, 36, 32, 37, 35, 36, 34, 37, 37, 36, 36, 37, 39, 36, 38, 37, 41, 36, 40, 37, 43, 36, 42, 37, 45, 36, 44, 37, 47, 36, 46, 37, 49, 36, 48, 37, 51, 36, 50, 37, 53, 36, 52, 37, 55, 36, 54, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 24, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // src_lita_string_lita
  c.constants = constants0();

  return c;
};

// src_lita_string_lita
static Value fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src_lita_string_lita");
             // src_lita_string_lita
  f->chunk = chunk0();
  return obj(f);
}

ObjFun *string_lita() {
                //src_lita_string_lita
  return AS_FUN(fn0());
}
