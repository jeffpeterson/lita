// clang-format off
// sol -c src/sol/lib/core.sol
#include "sol/chunk.h"
#include "sol/common.h"
#include "sol/lib.h"
#include "sol/memory.h"
#include "sol/string.h"

// string
static ValueArray constants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str(""),
  };
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
    0, 0, 40, 1, 40,
  };
  int lines[] = {
    2, 2, 2, 4, 4,
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
  f->name = newString("string");
             // string
  f->chunk = chunk1();
  return obj(f);
}

// <<
static ValueArray constants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("push"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// <<
static Chunk chunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    14, 0, 14, 1, 41, 0, 1, 40, 1, 40,
  };
  int lines[] = {
    17, 17, 17, 17, 17, 17, 17, 17, 19, 19,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // <<
  c.constants = constants2();

  return c;
};

// <<
static Value fn2() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("<<");
             // <<
  f->chunk = chunk2();
  return obj(f);
}

// ==
static ValueArray constants3() {
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
static Chunk chunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 107;
  c.capacity = 107;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 16, 0, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 14, 0, 44, 1, 14, 1, 16, 1, 21, 31, 0, 6, 7, 2, 40, 30, 0, 1, 7, 0, 2, 14, 2, 14, 0, 44, 0, 23, 31, 0, 50, 7, 30, 0, 16, 14, 2, 10, 2, 6, 0, 0, 3, 24, 15, 2, 7, 7, 32, 0, 30, 14, 0, 44, 4, 14, 2, 33, 1, 14, 1, 14, 2, 41, 4, 1, 21, 28, 31, 0, 6, 7, 3, 40, 30, 0, 1, 7, 32, 0, 46, 7, 7, 2, 40, 1, 40,
  };
  int lines[] = {
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 26, 26, 26,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // ==
  c.constants = constants3();

  return c;
};

// ==
static Value fn3() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("==");
             // ==
  f->chunk = chunk3();
  return obj(f);
}

// inspect
static ValueArray constants4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("true"), str("false"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// inspect
static Chunk chunk4() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 31, 0, 6, 7, 0, 0, 30, 0, 3, 7, 0, 1, 40, 1, 40,
  };
  int lines[] = {
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // inspect
  c.constants = constants4();

  return c;
};

// inspect
static Value fn4() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
             // inspect
  f->chunk = chunk4();
  return obj(f);
}

// string
static ValueArray constants5() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("inspect"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// string
static Chunk chunk5() {
  Chunk c;
  initChunk(&c);
  c.count = 7;
  c.capacity = 7;
  u8 code[] = {
    14, 0, 44, 0, 40, 1, 40,
  };
  int lines[] = {
    28, 28, 28, 28, 28, 30, 30,
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

// init
static ValueArray constants6() {
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
static Chunk chunk6() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 40,
  };
  int lines[] = {
    33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // init
  c.constants = constants6();

  return c;
};

// init
static Value fn6() {
  ObjFun *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = newString("init");
             // init
  f->chunk = chunk6();
  return obj(f);
}

// inspect
static ValueArray constants7() {
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
static Chunk chunk7() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 44, 0, 16, 1, 0, 2, 24, 14, 0, 44, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // inspect
  c.constants = constants7();

  return c;
};

// inspect
static Value fn7() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
             // inspect
  f->chunk = chunk7();
  return obj(f);
}

// string
static ValueArray constants8() {
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
static Chunk chunk8() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 44, 0, 16, 1, 0, 2, 24, 14, 0, 44, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 37, 37,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // string
  c.constants = constants8();

  return c;
};

// string
static Value fn8() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
             // string
  f->chunk = chunk8();
  return obj(f);
}

// string
static ValueArray constants9() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// string
static Chunk chunk9() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  u8 code[] = {
    14, 0, 40, 1, 40,
  };
  int lines[] = {
    38, 38, 38, 40, 40,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // string
  c.constants = constants9();

  return c;
};

// string
static Value fn9() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
             // string
  f->chunk = chunk9();
  return obj(f);
}

// *
static ValueArray constants10() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("string"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// *
static Chunk chunk10() {
  Chunk c;
  initChunk(&c);
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    14, 0, 14, 1, 16, 0, 24, 40, 1, 40,
  };
  int lines[] = {
    40, 40, 40, 40, 40, 40, 40, 40, 41, 41,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // *
  c.constants = constants10();

  return c;
};

// *
static Value fn10() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("*");
             // *
  f->chunk = chunk10();
  return obj(f);
}

// /
static ValueArray constants11() {
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
static Chunk chunk11() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    14, 0, 0, 0, 24, 14, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    41, 41, 41, 41, 41, 41, 41, 41, 41, 43, 43,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // /
  c.constants = constants11();

  return c;
};

// /
static Value fn11() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("/");
             // /
  f->chunk = chunk11();
  return obj(f);
}

// bold
static ValueArray constants12() {
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
static Chunk chunk12() {
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
                // bold
  c.constants = constants12();

  return c;
};

// bold
static Value fn12() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bold");
             // bold
  f->chunk = chunk12();
  return obj(f);
}

// dim
static ValueArray constants13() {
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
static Chunk chunk13() {
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
                // dim
  c.constants = constants13();

  return c;
};

// dim
static Value fn13() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("dim");
             // dim
  f->chunk = chunk13();
  return obj(f);
}

// italic
static ValueArray constants14() {
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
static Chunk chunk14() {
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
                // italic
  c.constants = constants14();

  return c;
};

// italic
static Value fn14() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("italic");
             // italic
  f->chunk = chunk14();
  return obj(f);
}

// underline
static ValueArray constants15() {
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
static Chunk chunk15() {
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
                // underline
  c.constants = constants15();

  return c;
};

// underline
static Value fn15() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("underline");
             // underline
  f->chunk = chunk15();
  return obj(f);
}

// invert
static ValueArray constants16() {
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
static Chunk chunk16() {
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
                // invert
  c.constants = constants16();

  return c;
};

// invert
static Value fn16() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("invert");
             // invert
  f->chunk = chunk16();
  return obj(f);
}

// hide
static ValueArray constants17() {
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
static Chunk chunk17() {
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
                // hide
  c.constants = constants17();

  return c;
};

// hide
static Value fn17() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("hide");
             // hide
  f->chunk = chunk17();
  return obj(f);
}

// strike
static ValueArray constants18() {
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
static Chunk chunk18() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    49, 49, 49, 49, 49, 49, 49, 49, 49, 51, 51,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // strike
  c.constants = constants18();

  return c;
};

// strike
static Value fn18() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("strike");
             // strike
  f->chunk = chunk18();
  return obj(f);
}

// black
static ValueArray constants19() {
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
static Chunk chunk19() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // black
  c.constants = constants19();

  return c;
};

// black
static Value fn19() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("black");
             // black
  f->chunk = chunk19();
  return obj(f);
}

// red
static ValueArray constants20() {
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
static Chunk chunk20() {
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
                // red
  c.constants = constants20();

  return c;
};

// red
static Value fn20() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("red");
             // red
  f->chunk = chunk20();
  return obj(f);
}

// green
static ValueArray constants21() {
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
static Chunk chunk21() {
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
                // green
  c.constants = constants21();

  return c;
};

// green
static Value fn21() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("green");
             // green
  f->chunk = chunk21();
  return obj(f);
}

// yellow
static ValueArray constants22() {
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
static Chunk chunk22() {
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
                // yellow
  c.constants = constants22();

  return c;
};

// yellow
static Value fn22() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("yellow");
             // yellow
  f->chunk = chunk22();
  return obj(f);
}

// blue
static ValueArray constants23() {
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
static Chunk chunk23() {
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
                // blue
  c.constants = constants23();

  return c;
};

// blue
static Value fn23() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("blue");
             // blue
  f->chunk = chunk23();
  return obj(f);
}

// magenta
static ValueArray constants24() {
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
static Chunk chunk24() {
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
                // magenta
  c.constants = constants24();

  return c;
};

// magenta
static Value fn24() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("magenta");
             // magenta
  f->chunk = chunk24();
  return obj(f);
}

// cyan
static ValueArray constants25() {
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
static Chunk chunk25() {
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
                // cyan
  c.constants = constants25();

  return c;
};

// cyan
static Value fn25() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("cyan");
             // cyan
  f->chunk = chunk25();
  return obj(f);
}

// white
static ValueArray constants26() {
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
static Chunk chunk26() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    58, 58, 58, 58, 58, 58, 58, 58, 58, 60, 60,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // white
  c.constants = constants26();

  return c;
};

// white
static Value fn26() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("white");
             // white
  f->chunk = chunk26();
  return obj(f);
}

// bg_black
static ValueArray constants27() {
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
static Chunk chunk27() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_black
  c.constants = constants27();

  return c;
};

// bg_black
static Value fn27() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_black");
             // bg_black
  f->chunk = chunk27();
  return obj(f);
}

// bg_red
static ValueArray constants28() {
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
static Chunk chunk28() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_red
  c.constants = constants28();

  return c;
};

// bg_red
static Value fn28() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_red");
             // bg_red
  f->chunk = chunk28();
  return obj(f);
}

// bg_green
static ValueArray constants29() {
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
static Chunk chunk29() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_green
  c.constants = constants29();

  return c;
};

// bg_green
static Value fn29() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_green");
             // bg_green
  f->chunk = chunk29();
  return obj(f);
}

// bg_yellow
static ValueArray constants30() {
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
static Chunk chunk30() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_yellow
  c.constants = constants30();

  return c;
};

// bg_yellow
static Value fn30() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_yellow");
             // bg_yellow
  f->chunk = chunk30();
  return obj(f);
}

// bg_blue
static ValueArray constants31() {
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
static Chunk chunk31() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_blue
  c.constants = constants31();

  return c;
};

// bg_blue
static Value fn31() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_blue");
             // bg_blue
  f->chunk = chunk31();
  return obj(f);
}

// bg_magenta
static ValueArray constants32() {
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
static Chunk chunk32() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_magenta
  c.constants = constants32();

  return c;
};

// bg_magenta
static Value fn32() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_magenta");
             // bg_magenta
  f->chunk = chunk32();
  return obj(f);
}

// bg_cyan
static ValueArray constants33() {
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
static Chunk chunk33() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_cyan
  c.constants = constants33();

  return c;
};

// bg_cyan
static Value fn33() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_cyan");
             // bg_cyan
  f->chunk = chunk33();
  return obj(f);
}

// bg_white
static ValueArray constants34() {
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
static Chunk chunk34() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    0, 0, 14, 0, 24, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 69,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // bg_white
  c.constants = constants34();

  return c;
};

// bg_white
static Value fn34() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bg_white");
             // bg_white
  f->chunk = chunk34();
  return obj(f);
}

// inspect
static ValueArray constants35() {
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
static Chunk chunk35() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    0, 0, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    70, 70, 70, 70, 70, 70, 72, 72,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // inspect
  c.constants = constants35();

  return c;
};

// inspect
static Value fn35() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
             // inspect
  f->chunk = chunk35();
  return obj(f);
}

// *
static ValueArray constants36() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("map"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// *
static Chunk chunk36() {
  Chunk c;
  initChunk(&c);
  c.count = 11;
  c.capacity = 11;
  u8 code[] = {
    14, 0, 44, 0, 14, 1, 33, 1, 40, 1, 40,
  };
  int lines[] = {
    73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // *
  c.constants = constants36();

  return c;
};

// *
static Value fn36() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("*");
             // *
  f->chunk = chunk36();
  return obj(f);
}

// each
static ValueArray constants37() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    0, str("length"), 0x3ff0000000000000, str("get"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// each
static Chunk chunk37() {
  Chunk c;
  initChunk(&c);
  c.count = 52;
  c.capacity = 52;
  u8 code[] = {
    0, 0, 14, 2, 14, 0, 44, 1, 23, 31, 0, 36, 7, 30, 0, 16, 14, 2, 10, 0, 6, 0, 0, 2, 24, 15, 2, 7, 7, 32, 0, 30, 14, 1, 14, 0, 44, 3, 14, 2, 33, 1, 33, 1, 7, 32, 0, 32, 7, 7, 1, 40,
  };
  int lines[] = {
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 78, 78, 78, 78, 78, 78, 78,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // each
  c.constants = constants37();

  return c;
};

// each
static Value fn37() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("each");
             // each
  f->chunk = chunk37();
  return obj(f);
}

// init
static ValueArray constants38() {
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
static Chunk chunk38() {
  Chunk c;
  initChunk(&c);
  c.count = 24;
  c.capacity = 24;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 14, 3, 17, 2, 7, 14, 0, 40,
  };
  int lines[] = {
    78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // init
  c.constants = constants38();

  return c;
};

// init
static Value fn38() {
  ObjFun *f = newFunction();  f->arity = 3;
  f->upvalueCount = 0;
  f->name = newString("init");
             // init
  f->chunk = chunk38();
  return obj(f);
}

// src_sol_lib_core_sol
static ValueArray constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 85;
  Value values[] = {
    str("Nil"), str("Any"), str("string"), /*string*/fn1(), str("Object"), str("Function"), str("Method"), str("NativeFunction"), str("Class"), str("Array"), str("<<"), /*<<*/fn2(), str("=="), /*==*/fn3(), str("Bool"), str("inspect"), /*inspect*/fn4(), /*string*/fn5(), str("Error"), str("Number"), str("Range"), /*init*/fn6(), str("init"), /*inspect*/fn7(), /*string*/fn8(), str("String"), /*string*/fn9(), str("*"), /***/fn10(), str("/"), /*/*/fn11(), str("bold"), /*bold*/fn12(), str("dim"), /*dim*/fn13(), str("italic"), /*italic*/fn14(), str("underline"), /*underline*/fn15(), str("invert"), /*invert*/fn16(), str("hide"), /*hide*/fn17(), str("strike"), /*strike*/fn18(), str("black"), /*black*/fn19(), str("red"), /*red*/fn20(), str("green"), /*green*/fn21(), str("yellow"), /*yellow*/fn22(), str("blue"), /*blue*/fn23(), str("magenta"), /*magenta*/fn24(), str("cyan"), /*cyan*/fn25(), str("white"), /*white*/fn26(), str("bg_black"), /*bg_black*/fn27(), str("bg_red"), /*bg_red*/fn28(), str("bg_green"), /*bg_green*/fn29(), str("bg_yellow"), /*bg_yellow*/fn30(), str("bg_blue"), /*bg_blue*/fn31(), str("bg_magenta"), /*bg_magenta*/fn32(), str("bg_cyan"), /*bg_cyan*/fn33(), str("bg_white"), /*bg_white*/fn34(), str("Table"), /*inspect*/fn35(), str("Tuple"), /***/fn36(), str("each"), /*each*/fn37(), str("Atom"), /*init*/fn38(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// src_sol_lib_core_sol
static Chunk chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 334;
  c.capacity = 334;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 7, 7, 34, 4, 0, 14, 0, 44, 1, 35, 9, 1, 7, 7, 34, 5, 0, 14, 0, 44, 4, 35, 9, 1, 7, 7, 34, 6, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 34, 7, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 34, 8, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 34, 9, 0, 14, 0, 44, 4, 35, 9, 1, 37, 11, 36, 10, 37, 13, 36, 12, 7, 7, 34, 14, 0, 14, 0, 44, 4, 35, 9, 1, 37, 16, 36, 15, 37, 17, 36, 2, 7, 7, 34, 18, 0, 14, 0, 44, 4, 35, 9, 1, 7, 7, 34, 19, 0, 14, 0, 44, 4, 35, 9, 1, 7, 7, 34, 20, 0, 37, 21, 36, 22, 14, 0, 44, 4, 35, 9, 1, 37, 23, 36, 15, 37, 24, 36, 2, 7, 7, 34, 25, 0, 14, 0, 44, 4, 35, 9, 1, 37, 26, 36, 2, 37, 28, 36, 27, 37, 30, 36, 29, 37, 32, 36, 31, 37, 34, 36, 33, 37, 36, 36, 35, 37, 38, 36, 37, 37, 40, 36, 39, 37, 42, 36, 41, 37, 44, 36, 43, 37, 46, 36, 45, 37, 48, 36, 47, 37, 50, 36, 49, 37, 52, 36, 51, 37, 54, 36, 53, 37, 56, 36, 55, 37, 58, 36, 57, 37, 60, 36, 59, 37, 62, 36, 61, 37, 64, 36, 63, 37, 66, 36, 65, 37, 68, 36, 67, 37, 70, 36, 69, 37, 72, 36, 71, 37, 74, 36, 73, 37, 76, 36, 75, 7, 7, 34, 77, 0, 14, 0, 44, 4, 35, 9, 1, 37, 78, 36, 15, 7, 7, 34, 79, 0, 14, 0, 44, 4, 35, 9, 1, 37, 80, 36, 27, 37, 82, 36, 81, 7, 7, 34, 83, 0, 37, 84, 36, 22, 14, 0, 44, 4, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 19, 19, 19, 19, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 28, 28, 28, 28, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 35, 35, 35, 35, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 40, 40, 40, 40, 41, 41, 41, 41, 43, 43, 43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 49, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 57, 57, 57, 57, 58, 58, 58, 58, 60, 60, 60, 60, 61, 61, 61, 61, 62, 62, 62, 62, 63, 63, 63, 63, 64, 64, 64, 64, 65, 65, 65, 65, 66, 66, 66, 66, 67, 67, 67, 67, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 74, 74, 74, 74, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79,
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
