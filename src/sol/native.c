#include <time.h>

#include "lib.h"
#include "native.h"
#include "vm.h"

/// Helpers

bool defineNative(const char *name, int arity, NativeFn fun) {
  return setGlobal(string(name), fn(name, arity, fun));
}

static _ globalClass(const char *name, const char *parent) {
  let n = str(name);
  return setGlobal(n, subClass(n, global(str(parent))));
}

/// Native global functions

static _ nativeClock(_ this, int argc, _ *args) {
  return num((double)clock() / CLOCKS_PER_SEC);
}

static _ nativeHash(_ this, int argc, _ *args) {
  return num(hashValue(args[0]));
}

static _ nativePrettyPrint(_ this, int argc, _ *args) {
  if (argc == 1)
    return pp(args[0]);

  return pp(t(argc, args));
}

static _ nativeRead(_ this, int argc, _ *args) {
  let path = argc == 0 ? str("/dev/stdin") : args[0];
  return read(path);
}

static _ nativeWrite(_ this, int argc, _ *args) {
  let path = argc == 1 ? str("/dev/stdout") : args[0];
  return write(path, args[argc - 1]);
}

static _ nativeAppend(_ this, int argc, _ *args) {
  let path = argc == 1 ? str("/dev/stdout") : args[0];
  return append(path, args[argc - 1]);
}

static _ Any_class(_ this, int argc, _ *args) { return classOf(this); }
static _ Any_hash(_ this, int argc, _ *args) { return hashValue(this); }
static _ Any_toString(_ this, int argc, _ *args) { return toString(this); }

static _ Function_bytes(_ this, int argc, _ *args) {
  if (!isFn(this))
    return error("Only Fns have bytes.");

  ObjFun *fn = AS_FUN(this);

  return memory(fn->chunk.code, fn->chunk.count);
}

static _ Function_byteCount(_ this, int argc, _ *args) {
  if (!isFn(this))
    return error("Only Fns have bytes.");

  ObjFun *fn = AS_FUN(this);

  return AS_NUMBER(fn->chunk.count);
}

static _ Number_star(_ this, int argc, _ *args) {
  let arg = args[0];

  if (isNum(arg))
    return AS_NUMBER(this) * AS_NUMBER(arg);

  return error("Cannot multiply these values.");
}

ObjFun *core_sol();

void defineNatives() {
  defineNative("clock", 0, nativeClock);
  defineNative("hash", 1, nativeHash);
  defineNative("pp", 1, nativePrettyPrint);
  defineNative("read", 0, nativeRead);
  defineNative("write", 1, nativeWrite);
  defineNative("append", 1, nativeAppend);

  let Any = setGlobal(str("Any"), class(str("Any")));
  method(Any, fn("class", 0, Any_class));
  method(Any, fn("hash", 0, Any_hash));
  method(Any, fn("toString", 0, Any_toString));

  globalClass("Nil", "Any");
  globalClass("Object", "Any");

  globalClass("Bool", "Object");
  globalClass("Class", "Object");
  let Number = globalClass("Number", "Object");
  method(Number, fn("*", 1, Number_star));

  globalClass("Error", "Object");

  let Function = globalClass("Function", "Object");
  method(Function, fn("bytes", 0, Function_bytes));         // getter
  method(Function, fn("byteCount", 0, Function_byteCount)); // getter

  globalClass("Method", "Function");
  globalClass("NativeFunction", "Function");
  globalClass("Range", "Object");
  globalClass("String", "Object");
  globalClass("Table", "Object");
  globalClass("Tuple", "Object");

  runFun(core_sol());
}
