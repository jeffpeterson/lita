#include <time.h>

#include "array.h"
#include "lib.h"
#include "native.h"
#include "vm.h"

/// Helpers

bool defineNative(const char *name, int arity, NativeFn fun) {
  return setGlobal(string(name), fn(name, arity, fun));
}

let global_class(const char *name) {
  let vname = string(name);
  let klass = global(vname);
  if (is_class(klass)) return klass;
  return setGlobal(vname, class(vname));
}

/// Native global functions

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

/// Native methods

/// Any
static _ Any_class(_ this, int argc, _ *args) { return classOf(this); }
static _ Any_eql(_ this, int argc, _ *args) {
  return BOOL_VAL(this == args[0]);
}
static _ Any_hash(_ this, int argc, _ *args) { return hashValue(this); }
static _ Any_inspect(_ this, int argc, _ *args) { return inspect(this); }
static _ Any_objectId(_ this, int argc, _ *args) {
  return NUMBER_VAL((u64)AS_OBJ(this));
}
static _ Any_string(_ this, int argc, _ *args) { return toString(this); }

/// Array
static Value Array_get(let this, int argc, _ *args) {
  ObjArray *arr = AS_ARRAY(this);
  u32 idx = asNum(args[0]);
  if (idx >= arr->length) return nil;

  return arr->values[idx];
}
static Value Array_length(let this, int argc, _ *args) {
  return NUMBER_VAL(AS_ARRAY(this)->length);
}
static Value Array_plus(let this, int argc, _ *args) {
  ObjArray *a = AS_ARRAY(this);
  ObjArray *b = as_array(args[0]);
  ObjArray *out = newArray();
  resizeArray(out, a->length + b->length);
  writeArray(out, 0, a->values, a->length);
  writeArray(out, a->length, b->values, b->length);
  return OBJ_VAL(out);
}

static Value Array_push(let this, int argc, _ *args) {
  ObjArray *arr = AS_ARRAY(this);
  for (int i = 0; i < argc; i++) appendArray(arr, args[i]);
  return this;
}

static Value Array_slice(let this, int argc, _ *args) {
  ObjArray *arr = AS_ARRAY(this);
  int start = argc > 0 ? asNum(args[0]) : 0;
  int len = argc > 1 ? asNum(args[1]) : arr->length - start;
  return OBJ_VAL(copyArray(arr->values + start, len));
}

/// Function
static _ Function_arity(_ this, int argc, _ *args) { return arity(this); }
static _ Function_bytes(_ this, int argc, _ *args) {
  if (!is_closure(this)) return error("Only Fns have bytes.");

  ObjFun *fn = AS_FUN(this);

  return memory(fn->chunk.code, fn->chunk.count);
}
static _ Function_byteCount(_ this, int argc, _ *args) {
  if (!is_closure(this)) return error("Only Fns have bytes.");

  ObjFun *fn = AS_FUN(this);

  return AS_NUMBER(fn->chunk.count);
}

/// Number
static _ Number_eql(_ this, int argc, _ *args) {
  return BOOL_VAL(AS_NUMBER(this) == AS_NUMBER(args[0]));
}
static _ Number_star(_ this, int argc, _ *args) {
  let arg = args[0];

  if (IS_NUMBER(arg)) return AS_NUMBER(this) * AS_NUMBER(arg);

  return error("Cannot multiply these values.");
}
static _ Number_string(_ this, int argc, _ *args) {
  return OBJ_VAL(stringf("%g", AS_NUMBER(this)));
}

/// String
static _ String_plus(_ this, int argc, _ *args) {
  let other = toString(args[0]);
  return obj(concatStrings(as_string(this), as_string(other)));
}

/// Tuple
static _ Tuple_map(_ this, int argc, _ *args) {
  if (!argc) return error("map() requires a callable argument");
  ObjTuple *tuple = AS_TUPLE(this);
  let fun = args[0];

  for (u8 i = 0; i < tuple->length; i++) {
    push(fun);
    push(tuple->values[i]);
    vm_call(1);
  }
  vm_tuple(tuple->length);
  return pop();
}

ObjFun *core_sol();

InterpretResult defineNatives() {
  defineNative("clock", 0, native_clock);
  defineNative("hash", 1, native_hash);
  defineNative("pp", 1, native_pp);
  defineNative("read", 0, native_read);
  defineNative("write", 1, native_write);
  defineNative("append", 1, native_append);

  vm.Any = global_class("Any");

  InterpretResult result = runFun(core_sol());

  if (result) return result;

  vm.Array = global(str("Array"));
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

  method(vm.Any, fn("==", 1, Any_eql));
  method(vm.Any, fn("class", 0, Any_class));
  method(vm.Any, fn("hash", 0, Any_hash));
  method(vm.Any, fn("inspect", 0, Any_inspect));
  method(vm.Any, fn("objectId", 0, Any_objectId));
  method(vm.Any, fn("string", 0, Any_string));
  method(vm.Any, fn("toString", 0, Any_string));

  method(vm.Array, fn("get", 1, Array_get));
  method(vm.Array, fn("length", 0, Array_length));
  method(vm.Array, fn("push", 0, Array_push));
  method(vm.Array, fn("slice", 0, Array_slice));
  method(vm.Array, fn("+", 1, Array_plus));

  method(vm.Number, fn("==", 1, Number_eql));
  method(vm.Number, fn("*", 1, Number_star));
  method(vm.Number, fn("string", 0, Number_string));

  method(vm.Function, fn("arity", 0, Function_arity));         // getter
  method(vm.Function, fn("bytes", 0, Function_bytes));         // getter
  method(vm.Function, fn("byteCount", 0, Function_byteCount)); // getter

  method(vm.String, fn("+", 1, String_plus));

  method(vm.Tuple, fn("map", 1, Tuple_map));

  return result;
}
