#include <time.h>

#include "lib.h"
#include "native.h"
#include "vm.h"

/// Helpers

bool defineNative(const char *name, int arity, NativeFn fun) {
  return setGlobal(string(name), fn(name, arity, fun));
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

/// Native methods

static _ Any_class(_ this, int argc, _ *args) { return classOf(this); }
static _ Any_hash(_ this, int argc, _ *args) { return hashValue(this); }
static _ Any_inspect(_ this, int argc, _ *args) { return inspect(this); }
static _ Any_string(_ this, int argc, _ *args) { return toString(this); }

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

static _ String_plus(_ this, int argc, _ *args) {
  let other = toString(args[0]);
  return obj(concatStrings(asStr(this), asStr(other)));
}

ObjFun *core_sol();

InterpretResult defineNatives() {
  defineNative("clock", 0, nativeClock);
  defineNative("hash", 1, nativeHash);
  defineNative("pp", 1, nativePrettyPrint);
  defineNative("read", 0, nativeRead);
  defineNative("write", 1, nativeWrite);
  defineNative("append", 1, nativeAppend);

  vm.Any = setGlobal(str("Any"), class(str("Any")));

  InterpretResult result = runFun(core_sol());

  if (result)
    return result;

  vm.Bool = global(str("Bool"));
  vm.Class = global(str("Class"));
  vm.Error = global(str("Error"));
  vm.Function = global(str("Function"));
  vm.Method = global(str("Method"));
  vm.NativeFunction = global(str("NativeFunction"));
  vm.Nil = global(str("Nil"));
  vm.Number = global(str("Number"));
  vm.Object = global(str("Object"));
  vm.Range = global(str("Range"));
  vm.String = global(str("String"));
  vm.Table = global(str("Table"));
  vm.Tuple = global(str("Tuple"));

  method(vm.Any, fn("class", 0, Any_class));
  method(vm.Any, fn("hash", 0, Any_hash));
  method(vm.Any, fn("inspect", 0, Any_inspect));
  method(vm.Any, fn("toString", 0, Any_string));
  method(vm.Any, fn("string", 0, Any_string));

  method(vm.Number, fn("*", 1, Number_star));

  method(vm.Function, fn("bytes", 0, Function_bytes));         // getter
  method(vm.Function, fn("byteCount", 0, Function_byteCount)); // getter

  method(vm.String, fn("+", 1, String_plus));
  return result;
}
