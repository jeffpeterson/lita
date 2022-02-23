// clang-format off
// sol -c lib/Range.sol
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
    3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 6, 6, 6,
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
  c.count = 20;
  c.capacity = 20;
  u8 code[] = {
    14, 0, 16, 0, 41, 1, 0, 0, 2, 24, 14, 0, 16, 3, 41, 1, 0, 24, 1, 40,
  };
  int lines[] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9,
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

static ValueArray toStringConstants3() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("inspect"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk toStringChunk3() {
  Chunk c;
  initChunk(&c);
  c.count = 7;
  c.capacity = 7;
  u8 code[] = {
    14, 0, 41, 0, 0, 1, 40,
  };
  int lines[] = {
    10, 10, 10, 10, 10, 11, 11,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = toStringConstants3();

  return c;
};

static Value toStringFn3() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("toString");
  f->chunk = toStringChunk3();
  return obj(f);
}

static ValueArray _script_Constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 8;
  Value values[] = {
    str("Range"), str("Object"), str("init"), initFn1(), str("inspect"), inspectFn2(), str("toString"), toStringFn3(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk _script_Chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 27;
  c.capacity = 27;
  u8 code[] = {
    34, 0, 11, 0, 12, 1, 12, 0, 35, 12, 0, 37, 3, 36, 2, 37, 5, 36, 4, 37, 7, 36, 6, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11,
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

ObjFun *Range_sol() {
  return AS_FUN(_script_Fn0());
}
