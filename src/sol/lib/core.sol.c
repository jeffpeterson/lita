// clang-format off
// sol -c src/sol/lib/core.sol
#include "sol/chunk.h"
#include "sol/common.h"
#include "sol/lib.h"
#include "sol/memory.h"
#include "sol/string.h"

static ValueArray existsConstants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 0;
  Value values[] = {};
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk existsChunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 4;
  c.capacity = 4;
  u8 code[] = {
    2, 40, 1, 40,
  };
  int lines[] = {
    2, 2, 2, 2,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = existsConstants1();

  return c;
};

static Value existsFn1() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("exists");
  f->chunk = existsChunk1();
  return obj(f);
}

static ValueArray _script_Constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("Core"), str("Object"), str("exists"), existsFn1(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk _script_Chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  u8 code[] = {
    34, 0, 11, 0, 12, 1, 12, 0, 35, 12, 0, 37, 3, 36, 2, 7, 7, 1, 40,
  };
  int lines[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
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
