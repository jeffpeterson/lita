// clang-format off
// sol -c lib/Parser.sol
#include "../chunk.h"
#include "../common.h"
#include "../lib.h"
#include "../memory.h"
#include "../string.h"

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
  c.count = 10;
  c.capacity = 10;
  u8 code[] = {
    14, 0, 14, 1, 17, 0, 7, 14, 0, 40,
  };
  int lines[] = {
    20, 20, 20, 20, 20, 20, 20, 21, 21, 21,
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

static ValueArray lib_Parser_solConstants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  Value values[] = {
    str("Parser"), str("Object"), str("init"), initFn1(),
  };
  vals.values = cloneMemory(values, sizeof(values));
  return vals;
}

static Chunk lib_Parser_solChunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 18;
  c.capacity = 18;
  u8 code[] = {
    34, 0, 0, 14, 0, 44, 1, 35, 9, 1, 37, 3, 36, 2, 7, 7, 1, 40,
  };
  int lines[] = {
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 21, 21, 21, 21, 21, 21, 21, 21,
  };
  c.code = cloneMemory(code, sizeof(code));
  c.lines = cloneMemory(lines, sizeof(lines));
  c.constants = lib_Parser_solConstants0();

  return c;
};

static Value lib_Parser_solFn0() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("lib_Parser_sol");
  f->chunk = lib_Parser_solChunk0();
  return obj(f);
}

ObjFun *Parser_sol() {
  return AS_FUN(lib_Parser_solFn0());
}
