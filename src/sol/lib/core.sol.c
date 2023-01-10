// clang-format off
// sol -c src/sol/lib/core.sol
#include "sol/chunk.h"
#include "sol/common.h"
#include "sol/lib.h"
#include "sol/memory.h"
#include "sol/string.h"

// ==
static ValueArray constants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 5;
  Value values[] = {
    str("length"), str("objectId"), 0, 0x3ff0000000000000, str("get"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// ==
static Chunk chunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 107;
  c.capacity = 107;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 16, 0, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 14, 0, 44, 1, 14, 1, 16, 1, 21, 31, 0, 6, 7, 2, 40, 30, 0, 1, 7, 0, 2, 14, 2, 14, 0, 44, 0, 23, 31, 0, 50, 7, 30, 0, 16, 14, 2, 10, 2, 6, 0, 0, 3, 24, 15, 2, 7, 7, 32, 0, 30, 14, 0, 44, 4, 14, 2, 33, 1, 14, 1, 14, 2, 41, 4, 1, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 32, 0, 46, 7, 7, 2, 40, 1, 40,
  };
  int lines[] = {
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 22, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // ==
  c.constants = constants1();

  return c;
};

// ==
static Value fn1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("==");
             // ==
  f->chunk = chunk1();
  return obj(f);
}

// init
static ValueArray constants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("start"), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// init
static Chunk chunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 40,
  };
  int lines[] = {
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // init
  c.constants = constants2();

  return c;
};

// init
static Value fn2() {
  ObjFun *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = newString("init");
             // init
  f->chunk = chunk2();
  return obj(f);
}

// inspect
static ValueArray constants3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("start"), str("inspect"), str(".."), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// inspect
static Chunk chunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 44, 0, 16, 1, 0, 2, 24, 14, 0, 44, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // inspect
  c.constants = constants3();

  return c;
};

// inspect
static Value fn3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
             // inspect
  f->chunk = chunk3();
  return obj(f);
}

// string
static ValueArray constants4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("start"), str("string"), str(".."), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// string
static Chunk chunk4() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 44, 0, 16, 1, 0, 2, 24, 14, 0, 44, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 30, 30,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // string
  c.constants = constants4();

  return c;
};

// string
static Value fn4() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
             // string
  f->chunk = chunk4();
  return obj(f);
}

// string
static ValueArray constants5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// string
static Chunk chunk5() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    14, 0, 40, 1, 40,
  };
  int lines[] = {
    31, 31, 31, 33, 33,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // string
  c.constants = constants5();

  return c;
};

// string
static Value fn5() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
             // string
  f->chunk = chunk5();
  return obj(f);
}

// /
static ValueArray constants6() {
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
static Chunk chunk6() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    14, 0, 0, 0, 24, 14, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    33, 33, 33, 33, 33, 33, 33, 33, 33, 35, 35,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // /
  c.constants = constants6();

  return c;
};

// /
static Value fn6() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("/");
             // /
  f->chunk = chunk6();
  return obj(f);
}

// bold
static ValueArray constants7() {
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
static Chunk chunk7() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bold
  c.constants = constants7();

  return c;
};

// bold
static Value fn7() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bold");
             // bold
  f->chunk = chunk7();
  return obj(f);
}

// dim
static ValueArray constants8() {
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
static Chunk chunk8() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // dim
  c.constants = constants8();

  return c;
};

// dim
static Value fn8() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dim");
             // dim
  f->chunk = chunk8();
  return obj(f);
}

// italic
static ValueArray constants9() {
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
static Chunk chunk9() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // italic
  c.constants = constants9();

  return c;
};

// italic
static Value fn9() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("italic");
             // italic
  f->chunk = chunk9();
  return obj(f);
}

// underline
static ValueArray constants10() {
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
static Chunk chunk10() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // underline
  c.constants = constants10();

  return c;
};

// underline
static Value fn10() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("underline");
             // underline
  f->chunk = chunk10();
  return obj(f);
}

// invert
static ValueArray constants11() {
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
static Chunk chunk11() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // invert
  c.constants = constants11();

  return c;
};

// invert
static Value fn11() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("invert");
             // invert
  f->chunk = chunk11();
  return obj(f);
}

// hide
static ValueArray constants12() {
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
static Chunk chunk12() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // hide
  c.constants = constants12();

  return c;
};

// hide
static Value fn12() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("hide");
             // hide
  f->chunk = chunk12();
  return obj(f);
}

// strike
static ValueArray constants13() {
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
static Chunk chunk13() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    41, 41, 41, 41, 41, 41, 41, 41, 41, 43, 43,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // strike
  c.constants = constants13();

  return c;
};

// strike
static Value fn13() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("strike");
             // strike
  f->chunk = chunk13();
  return obj(f);
}

// black
static ValueArray constants14() {
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
static Chunk chunk14() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    43, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // black
  c.constants = constants14();

  return c;
};

// black
static Value fn14() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("black");
             // black
  f->chunk = chunk14();
  return obj(f);
}

// red
static ValueArray constants15() {
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
static Chunk chunk15() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // red
  c.constants = constants15();

  return c;
};

// red
static Value fn15() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("red");
             // red
  f->chunk = chunk15();
  return obj(f);
}

// green
static ValueArray constants16() {
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
static Chunk chunk16() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    45, 45, 45, 45, 45, 45, 45, 45, 45, 46, 46,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // green
  c.constants = constants16();

  return c;
};

// green
static Value fn16() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("green");
             // green
  f->chunk = chunk16();
  return obj(f);
}

// yellow
static ValueArray constants17() {
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
static Chunk chunk17() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // yellow
  c.constants = constants17();

  return c;
};

// yellow
static Value fn17() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("yellow");
             // yellow
  f->chunk = chunk17();
  return obj(f);
}

// blue
static ValueArray constants18() {
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
static Chunk chunk18() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // blue
  c.constants = constants18();

  return c;
};

// blue
static Value fn18() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("blue");
             // blue
  f->chunk = chunk18();
  return obj(f);
}

// magenta
static ValueArray constants19() {
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
static Chunk chunk19() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // magenta
  c.constants = constants19();

  return c;
};

// magenta
static Value fn19() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("magenta");
             // magenta
  f->chunk = chunk19();
  return obj(f);
}

// cyan
static ValueArray constants20() {
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
static Chunk chunk20() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // cyan
  c.constants = constants20();

  return c;
};

// cyan
static Value fn20() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("cyan");
             // cyan
  f->chunk = chunk20();
  return obj(f);
}

// white
static ValueArray constants21() {
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
static Chunk chunk21() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    50, 50, 50, 50, 50, 50, 50, 50, 50, 52, 52,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // white
  c.constants = constants21();

  return c;
};

// white
static Value fn21() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("white");
             // white
  f->chunk = chunk21();
  return obj(f);
}

// bg_black
static ValueArray constants22() {
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
static Chunk chunk22() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_black
  c.constants = constants22();

  return c;
};

// bg_black
static Value fn22() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_black");
             // bg_black
  f->chunk = chunk22();
  return obj(f);
}

// bg_red
static ValueArray constants23() {
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
static Chunk chunk23() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_red
  c.constants = constants23();

  return c;
};

// bg_red
static Value fn23() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_red");
             // bg_red
  f->chunk = chunk23();
  return obj(f);
}

// bg_green
static ValueArray constants24() {
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
static Chunk chunk24() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_green
  c.constants = constants24();

  return c;
};

// bg_green
static Value fn24() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_green");
             // bg_green
  f->chunk = chunk24();
  return obj(f);
}

// bg_yellow
static ValueArray constants25() {
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
static Chunk chunk25() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_yellow
  c.constants = constants25();

  return c;
};

// bg_yellow
static Value fn25() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_yellow");
             // bg_yellow
  f->chunk = chunk25();
  return obj(f);
}

// bg_blue
static ValueArray constants26() {
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
static Chunk chunk26() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_blue
  c.constants = constants26();

  return c;
};

// bg_blue
static Value fn26() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_blue");
             // bg_blue
  f->chunk = chunk26();
  return obj(f);
}

// bg_magenta
static ValueArray constants27() {
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
static Chunk chunk27() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_magenta
  c.constants = constants27();

  return c;
};

// bg_magenta
static Value fn27() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_magenta");
             // bg_magenta
  f->chunk = chunk27();
  return obj(f);
}

// bg_cyan
static ValueArray constants28() {
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
static Chunk chunk28() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    58, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_cyan
  c.constants = constants28();

  return c;
};

// bg_cyan
static Value fn28() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_cyan");
             // bg_cyan
  f->chunk = chunk28();
  return obj(f);
}

// bg_white
static ValueArray constants29() {
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
static Chunk chunk29() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    59, 59, 59, 59, 59, 59, 59, 59, 59, 61, 61,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_white
  c.constants = constants29();

  return c;
};

// bg_white
static Value fn29() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_white");
             // bg_white
  f->chunk = chunk29();
  return obj(f);
}

// inspect
static ValueArray constants30() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("{"), str("}"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// inspect
static Chunk chunk30() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    0, 0, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    62, 62, 62, 62, 62, 62, 64, 64,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // inspect
  c.constants = constants30();

  return c;
};

// inspect
static Value fn30() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
             // inspect
  f->chunk = chunk30();
  return obj(f);
}

// init
static ValueArray constants31() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 3;
  Value values[] = {
    str("type"), str("value"), str("targets"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// init
static Chunk chunk31() {
  Chunk c;
  initChunk(&c);
  c.count = 24;
  c.capacity = 24;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 14, 3, 17, 2, 7, 14, 0, 40,
  };
  int lines[] = {
    66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // init
  c.constants = constants31();

  return c;
};

// init
static Value fn31() {
  ObjFun *f = newFunction();  f->arity = 3;
  f->upvalueCount = 0;
  f->name = newString("init");
             // init
  f->chunk = chunk31();
  return obj(f);
}

// src_sol_lib_core_sol
static ValueArray constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 75;
  Value values[] = {
    str("Nil"), str("Any"), str("Object"), str("Function"), str("Method"), str("NativeFunction"), str("Class"), str("Array"), str("=="), /*==*/fn1(), str("Bool"), str("Error"), str("Number"), str("Range"), /*init*/fn2(), str("init"), str("inspect"), /*inspect*/fn3(), str("string"), /*string*/fn4(), str("String"), /*string*/fn5(), str("/"), /*/*/fn6(), str("bold"), /*bold*/fn7(), str("dim"), /*dim*/fn8(), str("italic"), /*italic*/fn9(), str("underline"), /*underline*/fn10(), str("invert"), /*invert*/fn11(), str("hide"), /*hide*/fn12(), str("strike"), /*strike*/fn13(), str("black"), /*black*/fn14(), str("red"), /*red*/fn15(), str("green"), /*green*/fn16(), str("yellow"), /*yellow*/fn17(), str("blue"), /*blue*/fn18(), str("magenta"), /*magenta*/fn19(), str("cyan"), /*cyan*/fn20(), str("white"), /*white*/fn21(), str("bg_black"), /*bg_black*/fn22(), str("bg_red"), /*bg_red*/fn23(), str("bg_green"), /*bg_green*/fn24(), str("bg_yellow"), /*bg_yellow*/fn25(), str("bg_blue"), /*bg_blue*/fn26(), str("bg_magenta"), /*bg_magenta*/fn27(), str("bg_cyan"), /*bg_cyan*/fn28(), str("bg_white"), /*bg_white*/fn29(), str("Table"), /*inspect*/fn30(), str("Tuple"), str("Atom"), /*init*/fn31(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// src_sol_lib_core_sol
static Chunk chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 306;
  c.capacity = 306;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 7, 7, 34, 2, 0, 14, 0, 44, 1, 35, 9, 1, 7, 7, 34, 3, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 4, 0, 14, 0, 44, 3, 35, 9, 1, 7, 7, 34, 5, 0, 14, 0, 44, 3, 35, 9, 1, 7, 7, 34, 6, 0, 14, 0, 44, 3, 35, 9, 1, 7, 7, 34, 7, 0, 14, 0, 44, 2, 35, 9, 1, 37, 9, 36, 8, 7, 7, 34, 10, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 11, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 12, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 13, 0, 37, 14, 36, 15, 14, 0, 44, 2, 35, 9, 1, 37, 17, 36, 16, 37, 19, 36, 18, 7, 7, 34, 20, 0, 14, 0, 44, 2, 35, 9, 1, 37, 21, 36, 18, 37, 23, 36, 22, 37, 25, 36, 24, 37, 27, 36, 26, 37, 29, 36, 28, 37, 31, 36, 30, 37, 33, 36, 32, 37, 35, 36, 34, 37, 37, 36, 36, 37, 39, 36, 38, 37, 41, 36, 40, 37, 43, 36, 42, 37, 45, 36, 44, 37, 47, 36, 46, 37, 49, 36, 48, 37, 51, 36, 50, 37, 53, 36, 52, 37, 55, 36, 54, 37, 57, 36, 56, 37, 59, 36, 58, 37, 61, 36, 60, 37, 63, 36, 62, 37, 65, 36, 64, 37, 67, 36, 66, 37, 69, 36, 68, 7, 7, 34, 70, 0, 14, 0, 44, 2, 35, 9, 1, 37, 71, 36, 16, 7, 7, 34, 72, 0, 14, 0, 44, 2, 35, 9, 1, 7, 7, 34, 73, 0, 37, 74, 36, 15, 14, 0, 44, 2, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 28, 28, 28, 28, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 33, 33, 33, 33, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 43, 43, 43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 52, 52, 52, 52, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 57, 57, 57, 57, 58, 58, 58, 58, 59, 59, 59, 59, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // src_sol_lib_core_sol
  c.constants = constants0();

  return c;
};

// src_sol_lib_core_sol
static Value fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("src_sol_lib_core_sol");
             // src_sol_lib_core_sol
  f->chunk = chunk0();
  return obj(f);
}

ObjFun *core_sol() {
                //src_sol_lib_core_sol
  return AS_FUN(fn0());
}
