// clang-format off
// sol -c lib/Parser.sol
#include "sol/chunk.h"
#include "sol/common.h"
#include "sol/lib.h"
#include "sol/memory.h"
#include "sol/string.h"

static ValueArray initConstants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  Value values[] = {
    str("source"),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk initChunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 9;
  c.capacity = 9;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 14, 0, 40,
  };
  int lines[] = {
    3, 3, 3, 3, 3, 3, 21, 21, 21,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = initConstants1();

  return c;
};

static Value initFn1() {
  ObjFun *f = newFunction();  f->arity = 1;
  f->upvalueCount = 0;
  f->name = newString("init");
  f->chunk = initChunk1();
  return obj(f);
}

static ValueArray _script_Constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("Parser"), str("Object"), str("init"), initFn1(),
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
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 21, 21, 21, 21, 21, 21, 21, 21,
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

ObjFun *Parser_sol() {
  return AS_FUN(_script_Fn0());
}
