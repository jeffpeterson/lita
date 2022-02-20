// clang-format off
// sol -c src/sol/lib/core.sol
#include "sol/chunk.h"
#include "sol/common.h"
#include "sol/lib.h"
#include "sol/string.h"

static ValueArray barConstants1() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 1;
  vals.values = (Value[]){
    num(1), 
  };
  return vals;
}

static Chunk barChunk1() {
  Chunk c;
  initChunk(&c);
  c.count = 5;
  c.capacity = 5;
  c.code = (u8[]){
    0, 0, 40, 1, 40, 
  };
  c.lines = (int[]){
    2, 2, 2, 2, 2, 
  };
  c.constants = barConstants1();

  return c;
};

static Value barFn1() {
  ObjFun *f = newFunction();  f->arity = 0;
  f->upvalueCount = 0;
  f->name = newString("bar");
  f->chunk = barChunk1();
  return obj(f);
}

static ValueArray _script_Constants0() {
  ValueArray vals;
  initValueArray(&vals);
  vals.count = vals.capacity = 4;
  vals.values = (Value[]){
    str("Foo"), str("Object"), str("bar"), barFn1(), 
  };
  return vals;
}

static Chunk _script_Chunk0() {
  Chunk c;
  initChunk(&c);
  c.count = 19;
  c.capacity = 19;
  c.code = (u8[]){
    34, 0, 11, 0, 12, 1, 12, 0, 35, 12, 0, 37, 3, 36, 2, 7, 7, 1, 40, 
  };
  c.lines = (int[]){
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 
  };
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

