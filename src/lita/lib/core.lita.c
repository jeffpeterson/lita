// clang-format off
// lita -c src/lita/lib/core.lita
#include "lita/chunk.h"
#include "lita/common.h"
#include "lita/lib.h"
#include "lita/memory.h"
#include "lita/string.h"

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
  f->name = new_string("string");
             // string
  f->chunk = chunk1();
  return obj(f);
}

// inspect
static ValueArray constants2() {
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
static Chunk chunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 31, 0, 6, 7, 0, 0, 30, 0, 3, 7, 0, 1, 40, 1, 40,
  };
  int lines[] = {
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // inspect
  c.constants = constants2();

  return c;
};

// inspect
static Value fn2() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("inspect");
             // inspect
  f->chunk = chunk2();
  return obj(f);
}

// string
static ValueArray constants3() {
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
static Chunk chunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 7;
  c.capacity = 7;
  u8 code[] = {
    14, 0, 44, 0, 40, 1, 40,
  };
  int lines[] = {
    18, 18, 18, 18, 18, 20, 20,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // string
  c.constants = constants3();

  return c;
};

// string
static Value fn3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("string");
             // string
  f->chunk = chunk3();
  return obj(f);
}

// init
static ValueArray constants4() {
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
static Chunk chunk4() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 40,
  };
  int lines[] = {
    23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // init
  c.constants = constants4();

  return c;
};

// init
static Value fn4() {
  ObjFun *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = new_string("init");
             // init
  f->chunk = chunk4();
  return obj(f);
}

// inspect
static ValueArray constants5() {
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
static Chunk chunk5() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 44, 0, 16, 1, 0, 2, 24, 14, 0, 44, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // inspect
  c.constants = constants5();

  return c;
};

// inspect
static Value fn5() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("inspect");
             // inspect
  f->chunk = chunk5();
  return obj(f);
}

// string
static ValueArray constants6() {
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
static Chunk chunk6() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 44, 0, 16, 1, 0, 2, 24, 14, 0, 44, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 27, 27,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // string
  c.constants = constants6();

  return c;
};

// string
static Value fn6() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("string");
             // string
  f->chunk = chunk6();
  return obj(f);
}

// inspect
static ValueArray constants7() {
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
static Chunk chunk7() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    0, 0, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    28, 28, 28, 28, 28, 28, 30, 30,
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
  f->name = new_string("inspect");
             // inspect
  f->chunk = chunk7();
  return obj(f);
}

// init
static ValueArray constants8() {
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
static Chunk chunk8() {
  Chunk c;
  initChunk(&c);
  c.count = 24;
  c.capacity = 24;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 14, 3, 17, 2, 7, 14, 0, 40,
  };
  int lines[] = {
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // init
  c.constants = constants8();

  return c;
};

// init
static Value fn8() {
  ObjFun *f = newFunction();  f->arity = 3;
  f->upvalueCount = 0;
  f->name = new_string("init");
             // init
  f->chunk = chunk8();
  return obj(f);
}

// src_lita_lib_core_lita
static ValueArray constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 24;
  Value values[] = {
    str("Nil"), str("Any"), str("string"), /*string*/fn1(), str("Object"), str("Function"), str("Method"), str("NativeFunction"), str("Class"), str("Bool"), str("inspect"), /*inspect*/fn2(), /*string*/fn3(), str("Error"), str("Number"), str("Range"), /*init*/fn4(), str("init"), /*inspect*/fn5(), /*string*/fn6(), str("Table"), /*inspect*/fn7(), str("Atom"), /*init*/fn8(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

// src_lita_lib_core_lita
static Chunk chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 178;
  c.capacity = 178;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 7, 7, 34, 4, 0, 14, 0, 44, 1, 35, 9, 1, 7, 7, 34, 5, 0, 14, 0, 44, 4, 35, 9, 1, 7, 7, 34, 6, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 34, 7, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 34, 8, 0, 14, 0, 44, 5, 35, 9, 1, 7, 7, 34, 9, 0, 14, 0, 44, 4, 35, 9, 1, 37, 11, 36, 10, 37, 12, 36, 2, 7, 7, 34, 13, 0, 14, 0, 44, 4, 35, 9, 1, 7, 7, 34, 14, 0, 14, 0, 44, 4, 35, 9, 1, 7, 7, 34, 15, 0, 37, 16, 36, 17, 14, 0, 44, 4, 35, 9, 1, 37, 18, 36, 10, 37, 19, 36, 2, 7, 7, 34, 20, 0, 14, 0, 44, 4, 35, 9, 1, 37, 21, 36, 10, 7, 7, 34, 22, 0, 37, 23, 36, 17, 14, 0, 44, 4, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 18, 18, 18, 18, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 25, 25, 25, 25, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
                // src_lita_lib_core_lita
  c.constants = constants0();

  return c;
};

// src_lita_lib_core_lita
static Value fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = new_string("src_lita_lib_core_lita");
             // src_lita_lib_core_lita
  f->chunk = chunk0();
  return obj(f);
}

ObjFun *core_lita() {
                //src_lita_lib_core_lita
  return AS_FUN(fn0());
}
