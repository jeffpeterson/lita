#include <time.h>

#include "array.h"
#include "lib.h"
#include "native.h"
#include "tuple.h"
#include "vm.h"

// # Helpers

Value defineNative(const char *name, int arity, NativeFn fun) {
  return setGlobal(string(name), fn(name, arity, fun));
}

let global_class(const char *name) {
  let vname = string(name);
  let klass = global(vname);
  if (is_class(klass)) return klass;
  return setGlobal(vname, class(vname));
}

// # Native global functions

static _ native_clock(_ this, int argc, _ *args) {
  return num((double)clock() / CLOCKS_PER_SEC);
}

static _ native_hash(_ this, int argc, _ *args) {
  return num(hashValue(args[0]));
}

static _ native_pp(_ this, int argc, _ *args) {
  if (argc == 1) return pp(args[0]);

  return pp(t(argc, args));
}

static _ native_read(_ this, int argc, _ *args) {
  let path = argc == 0 ? str("/dev/stdin") : args[0];
  return read(path);
}

static _ native_write(_ this, int argc, _ *args) {
  let path = argc == 1 ? str("/dev/stdout") : args[0];
  return write(path, args[argc - 1]);
}

static _ native_append(_ this, int argc, _ *args) {
  let path = argc == 1 ? str("/dev/stdout") : args[0];
  return append(path, args[argc - 1]);
}

// # Native methods

// # Any
let Any_self(let this, int argc, let *args) { return this; }
static _ Any_class(_ this, int argc, _ *args) { return classOf(this); }
static _ Any_eql(_ this, int argc, _ *args) {
  return BOOL_VAL(valuesEqual(this, args[0]));
}
static _ Any_hash(_ this, int argc, _ *args) {
  return NUMBER_VAL(hashValue(this));
}
static _ Any_inspect(_ this, int argc, _ *args) { return inspect(this); }
static _ Any_objectId(_ this, int argc, _ *args) {
  return NUMBER_VAL((u64)AS_OBJ(this));
}
static _ Any_string(_ this, int argc, _ *args) { return to_string(this); }

// # Function
static _ Function_arity(_ this, int argc, _ *args) {
  return NUMBER_VAL(arity(this));
}
static _ Function_bytes(_ this, int argc, _ *args) {
  if (!is_closure(this)) return error("Only Fns have bytes.");

  ObjFun *fn = AS_FUN(this);

  return memory(fn->chunk.code, fn->chunk.count);
}
static _ Function_byteCount(_ this, int argc, _ *args) {
  if (!is_closure(this)) return error("Only Fns have bytes.");

  ObjFun *fn = AS_FUN(this);

  return num(fn->chunk.count);
}

// # Number
static _ Number_eql(_ this, int argc, _ *args) {
  return BOOL_VAL(AS_NUMBER(this) == AS_NUMBER(args[0]));
}
static _ Number_star(_ this, int argc, _ *args) {
  let arg = args[0];

  if (is_num(arg)) return NUMBER_VAL(AS_NUMBER(this) * AS_NUMBER(arg));

  return error("Cannot multiply these values.");
}
static _ Number_string(_ this, int argc, _ *args) {
  return OBJ_VAL(stringf("%g", AS_NUMBER(this)));
}

ObjFun *core_lita();

InterpretResult defineNatives() {
  defineNative("clock", 0, native_clock);
  defineNative("hash", 1, native_hash);
  defineNative("pp", 1, native_pp);
  defineNative("read", 0, native_read);
  defineNative("write", 1, native_write);
  defineNative("append", 1, native_append);

  vm.Any = global_class("Any");

  InterpretResult result = runFun(core_lita());

  if (result) return result;

  vm.Array = global_class("Array");
  vm.Bool = global_class("Bool");
  vm.Class = global_class("Class");
  vm.Error = global_class("Error");
  vm.Function = global_class("Function");
  vm.Method = global_class("Method");
  vm.NativeFunction = global_class("NativeFunction");
  vm.Nil = global_class("Nil");
  vm.Number = global_class("Number");
  vm.Object = global_class("Object");
  vm.Range = global_class("Range");
  vm.String = global_class("String");
  vm.Table = global_class("Table");
  vm.Tuple = global_class("Tuple");

  method(vm.Any, fn("==", 1, Any_eql));
  method(vm.Any, fn("self", 0, Any_self));
  method(vm.Any, fn("class", 0, Any_class));
  method(vm.Any, fn("hash", 0, Any_hash));
  method(vm.Any, fn("inspect", 0, Any_inspect));
  method(vm.Any, fn("objectId", 0, Any_objectId));
  method(vm.Any, fn("string", 0, Any_string));
  method(vm.Any, fn("to_string", 0, Any_string));

  method(vm.Number, fn("==", 1, Number_eql));
  method(vm.Number, fn("*", 1, Number_star));
  method(vm.Number, fn("string", 0, Number_string));

  method(vm.Function, fn("arity", 0, Function_arity));         // getter
  method(vm.Function, fn("bytes", 0, Function_bytes));         // getter
  method(vm.Function, fn("byteCount", 0, Function_byteCount)); // getter

  return result;
}
