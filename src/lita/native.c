#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#include "array.h"
#include "debug.h"
#include "lib.h"
#include "memory.h"
#include "native.h"
#include "term.h"
#include "tuple.h"
#include "vm.h"

// # Native global functions

NATIVE_FUNCTION(clock, 0) { return num((double)clock() / CLOCKS_PER_SEC); }
NATIVE_FUNCTION(hash, 1) {
  return OBJ_VAL(stringf("%#x", hash_value(args[0])));
}
NATIVE_FUNCTION(pp, 1) { return argc > 1 ? pp(t(argc, args)) : pp(args[0]); }
NATIVE_FUNCTION(read, 0) { return read(argc ? args[0] : str("/dev/stdin")); }
NATIVE_FUNCTION(mkdir, 1) { return mkdir(as_string(args[0])->chars, 0777); }
NATIVE_FUNCTION(write, 1) {
  let path = argc == 1 ? str("/dev/stdout") : args[0];
  return write(path, args[argc - 1]);
}
NATIVE_FUNCTION(append, 1) {
  let path = argc == 1 ? str("/dev/stdout") : args[0];
  return append(path, args[argc - 1]);
}
NATIVE_FUNCTION(repl, 0) {
  repl();
  return nil;
}

// # Native methods

// # Any
NATIVE_METHOD(Any, self, 0) { return this; }
NATIVE_METHOD(Any, class, 0) { return classOf(this); }
NATIVE_METHOD_NAMED(Any, eql, "==", 1) {
  return BOOL_VAL(valuesEqual(this, args[0]));
}
NATIVE_METHOD_NAMED(Any, not_eql, "!=", 1) {
  return BOOL_VAL(!valuesEqual(this, args[0]));
}
NATIVE_METHOD(Any, hash, 0) {
  return OBJ_VAL(stringf("%#x", hash_value(this)));
}
NATIVE_METHOD(Any, inspect, 0) { return inspect(this); }
NATIVE_METHOD(Any, object_id, 0) { return NUMBER_VAL((u64)AS_OBJ(this)); }
NATIVE_METHOD(Any, string, 0) { return inspect(this); }

// # Function
NATIVE_METHOD(Function, arity, 0) { return NUMBER_VAL(arity(this)); }
NATIVE_METHOD(Function, name, 0) {
  return OBJ_VAL(asClosure(this)->function->name);
}
NATIVE_METHOD(Function, bytes, 0) {
  if (!isClosure(this)) return crash("Only Functions have bytes.");
  ObjFunction *fn = asFunction(this);
  return memory(fn->chunk.code, fn->chunk.count);
}
NATIVE_METHOD(Function, byte_count, 0) {
  if (!isClosure(this)) return crash("Only Functions have bytes.");
  ObjFunction *fn = asFunction(this);
  return num(fn->chunk.count);
}

// # Number
NATIVE_METHOD_NAMED(Number, gt, ">", 1) {
  return BOOL_VAL(as_num(this) > as_num(args[0]));
}
NATIVE_METHOD_NAMED(Number, gte, ">=", 1) {
  return BOOL_VAL(as_num(this) >= as_num(args[0]));
}
NATIVE_METHOD_NAMED(Number, lt, "<", 1) {
  return BOOL_VAL(as_num(this) < as_num(args[0]));
}
NATIVE_METHOD_NAMED(Number, lte, "<=", 1) {
  return BOOL_VAL(as_num(this) <= as_num(args[0]));
}
NATIVE_METHOD_NAMED(Number, star, "*", 1) {
  return NUMBER_VAL(as_num(this) * as_num(args[0]));
}
NATIVE_METHOD(Number, string, 0) {
  return OBJ_VAL(stringf("%g", as_num(this)));
}

ObjNative *newNative(ObjString *name, int arity, NativeFn fun) {
  ObjNative *native = allocateNative();
  native->arity = arity;
  native->fun = fun;
  native->name = name;
  return native;
}

void markNative(Obj *obj) {
  ObjNative *native = (ObjNative *)obj;
  markObject((Obj *)native->name);
}

int inspectNative(Obj *obj, FILE *io) {
  ObjNative *native = (ObjNative *)obj;
  return fprintf(io,
                 FG_MAGENTA "<native %s" FG_DEFAULT "/" FG_MAGENTA
                            "%d>" FG_DEFAULT,
                 native->name->chars, native->arity) -
         FG_SIZE * 4;
}

int nativeLength(Obj *obj) {
  ObjNative *native = (ObjNative *)obj;
  return native->arity;
}

REGISTER_OBJECT_DEF(Native);
ObjDef Native = {
    .class_name = "Native",
    .size = sizeof(ObjNative),
    .mark = markNative,
    .inspect = inspectNative,
    .length = nativeLength,
};
