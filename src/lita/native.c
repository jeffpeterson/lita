#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#include "array.h"
#include "debug.h"
#include "lib.h"
#include "native.h"
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
  return OBJ_VAL(as_closure(this)->fun->name);
}
NATIVE_METHOD(Function, bytes, 0) {
  if (!is_closure(this)) return crash("Only Functions have bytes.");
  ObjFun *fn = AS_FUN(this);
  return memory(fn->chunk.code, fn->chunk.count);
}
NATIVE_METHOD(Function, byte_count, 0) {
  if (!is_closure(this)) return crash("Only Functions have bytes.");
  ObjFun *fn = AS_FUN(this);
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

ObjFun *core_lita();

InterpretResult defineNatives() {
  foreach_native(native) {
    let fun = fn(native->name, native->arity, native->fun);
    trace(native->class_name, fun);

    if (native->class_name) {
      let klass = global_class(native->class_name);
      if (native->is_static) static_method(klass, fun);
      else method(klass, fun);

    } else setGlobal(string(native->name), fun);
  }

  run_function(core_lita());

  foreach_boot_function(boot) {
    ObjFun *fun = boot->fun();
    trace("Booting", OBJ_VAL(fun));
    InterpretResult result = run_function(fun);
    if (result) return result;
  }

  return INTERPRET_OK;
}
