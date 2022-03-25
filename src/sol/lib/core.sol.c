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
  c.count = 15;
  c.capacity = 15;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 14, 0, 14, 2, 17, 1, 14, 0, 40,
  };
  int lines[] = {
    20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 23, 23, 23,
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
  c.count = 21;
  c.capacity = 21;
  u8 code[] = {
    14, 0, 16, 0, 41, 1, 0, 0, 2, 24, 14, 0, 16, 3, 41, 1, 0, 24, 40, 1, 40,
  };
  int lines[] = {
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 26, 26, 26,
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
  c.count = 21;
  c.capacity = 21;
  u8 code[] = {
    14, 0, 16, 0, 41, 1, 0, 0, 2, 24, 14, 0, 16, 3, 41, 1, 0, 24, 40, 1, 40,
  };
  int lines[] = {
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 29,
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

static ValueArray _script_Constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 20;
  Value values[] = {
    str("Nil"), str("Any"), str("Object"), str("Bool"), str("Error"), str("Number"), str("Range"), str("init"), initFn1(), str("inspect"), inspectFn2(), str("string"), stringFn3(), str("String"), str("Table"), str("Tuple"), str("Function"), str("Method"), str("NativeFunction"), str("Class"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk _script_Chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 183;
  c.capacity = 183;
  u8 code[] = {
    34, 0, 11, 0, 12, 1, 12, 0, 35, 12, 0, 7, 7, 34, 2, 11, 2, 12, 1, 12, 2, 35, 12, 2, 7, 7, 34, 3, 11, 3, 12, 2, 12, 3, 35, 12, 3, 7, 7, 34, 4, 11, 4, 12, 2, 12, 4, 35, 12, 4, 7, 7, 34, 5, 11, 5, 12, 2, 12, 5, 35, 12, 5, 7, 7, 34, 6, 11, 6, 12, 2, 12, 6, 35, 12, 6, 37, 8, 36, 7, 37, 10, 36, 9, 37, 12, 36, 11, 7, 7, 34, 13, 11, 13, 12, 2, 12, 13, 35, 12, 13, 7, 7, 34, 14, 11, 14, 12, 2, 12, 14, 35, 12, 14, 7, 7, 34, 15, 11, 15, 12, 2, 12, 15, 35, 12, 15, 7, 7, 34, 16, 11, 16, 12, 2, 12, 16, 35, 12, 16, 7, 7, 34, 17, 11, 17, 12, 16, 12, 17, 35, 12, 17, 7, 7, 34, 18, 11, 18, 12, 16, 12, 18, 35, 12, 18, 7, 7, 34, 19, 11, 19, 12, 16, 12, 19, 35, 12, 19, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 23, 23, 23, 23, 26, 26, 26, 26, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39,
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
