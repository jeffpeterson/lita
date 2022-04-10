// clang-format off
// sol -c lib/core.sol
#include "sol/chunk.h"
#include "sol/common.h"
#include "sol/lib.h"
#include "sol/memory.h"
#include "sol/string.h"

static ValueArray initConstants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("start"), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk initChunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 17;
  c.capacity = 17;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 14, 2, 17, 1, 7, 14, 0, 40,
  };
  int lines[] = {
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = initConstants1();

  return c;
};

static Value initFn1() {
  ObjFun *f = newFunction();  f->arity = 2;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->chunk = initChunk1();
  return obj(f);
}

static ValueArray inspectConstants2() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("start"), str("inspect"), str(".."), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk inspectChunk2() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 16, 0, 16, 1, 0, 2, 24, 14, 0, 16, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 22, 22, 22,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = inspectConstants2();

  return c;
};

static Value inspectFn2() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
  f->chunk = inspectChunk2();
  return obj(f);
}

static ValueArray stringConstants3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("start"), str("string"), str(".."), str("end"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk stringChunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    14, 0, 16, 0, 16, 1, 0, 2, 24, 14, 0, 16, 3, 16, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 25, 25, 25,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = stringConstants3();

  return c;
};

static Value stringFn3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("string");
  f->chunk = stringChunk3();
  return obj(f);
}

static ValueArray inspectConstants4() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 2;
  Value values[] = {
    str("{"), str("}"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk inspectChunk4() {
  Chunk c;
  initChunk(&c);
  c.count = 8;
  c.capacity = 8;
  u8 code[] = {
    0, 0, 0, 1, 24, 40, 1, 40,
  };
  int lines[] = {
    28, 28, 28, 28, 28, 30, 30, 30,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = inspectConstants4();

  return c;
};

static Value inspectFn4() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("inspect");
  f->chunk = inspectChunk4();
  return obj(f);
}

static ValueArray _script_Constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 21;
  Value values[] = {
    str("Nil"), str("Any"), str("Object"), str("Function"), str("Method"), str("NativeFunction"), str("Class"), str("Bool"), str("Error"), str("Number"), str("Range"), initFn1(), str("init"), str("inspect"), inspectFn2(), str("string"), stringFn3(), str("String"), str("Table"), inspectFn4(), str("Tuple"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk _script_Chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 148;
  c.capacity = 148;
  u8 code[] = {
    34, 0, 0, 12, 1, 35, 9, 1, 7, 7, 34, 2, 0, 12, 1, 35, 9, 1, 7, 7, 34, 3, 0, 12, 2, 35, 9, 1, 7, 7, 34, 4, 0, 12, 3, 35, 9, 1, 7, 7, 34, 5, 0, 12, 3, 35, 9, 1, 7, 7, 34, 6, 0, 12, 3, 35, 9, 1, 7, 7, 34, 7, 0, 12, 2, 35, 9, 1, 7, 7, 34, 8, 0, 12, 2, 35, 9, 1, 7, 7, 34, 9, 0, 12, 2, 35, 9, 1, 7, 7, 34, 10, 0, 37, 11, 36, 12, 12, 2, 35, 9, 1, 37, 14, 36, 13, 37, 16, 36, 15, 7, 7, 34, 17, 0, 12, 2, 35, 9, 1, 7, 7, 34, 18, 0, 12, 2, 35, 9, 1, 37, 19, 36, 13, 7, 7, 34, 20, 0, 12, 2, 35, 9, 1, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 22, 22, 22, 22, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = _script_Constants0();

  return c;
};

static Value _script_Fn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("_script_");
  f->chunk = _script_Chunk0();
  return obj(f);
}

ObjFun *core_sol() {
  return AS_FUN(_script_Fn0());
}
