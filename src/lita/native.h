#ifndef lita_native_h
#define lita_native_h

#include "common.h"
#include "object.h"
#include "value.h"
#include "vm.h"

typedef struct NativeMethod {
  const char *class_name;
  const char *name;
  int arity;
  NativeFn *fun;
} NativeMethod;

typedef struct BootFunction {
  const char *name;
  ObjFun *(*fun)();
} BootFunction;

#define foreach_native(var) section_foreach_entry(natives, NativeMethod, var)
#define foreach_boot_function(var)                                             \
  section_foreach_entry(boot_functions, BootFunction, var)

#define NATIVE_FUNCTION(name, arity)                                           \
  static Value native_##name(Value this, int argc, Value *args);               \
  static NativeMethod SECTION(natives) native_func_##name = {                  \
      NULL,                                                                    \
      #name,                                                                   \
      arity,                                                                   \
      native_##name,                                                           \
  };                                                                           \
  static Value native_##name(Value this, int argc, Value *args)

#define NATIVE_METHOD_NAMED(klass, attr, name, arity)                          \
  static Value klass##_##attr(Value this, int argc, Value *args);              \
  static NativeMethod SECTION(natives) klass##_##attr##_native = {             \
      #klass,                                                                  \
      name,                                                                    \
      arity,                                                                   \
      klass##_##attr,                                                          \
  };                                                                           \
  static Value klass##_##attr(Value this, int argc, Value *args)

#define NATIVE_METHOD(klass, attr, arity)                                      \
  NATIVE_METHOD_NAMED(klass, attr, #attr, arity)

#define NATIVE_GETTER(klass, attr, mapper)                                     \
  NATIVE_METHOD(klass, attr, 0) {                                              \
    Obj##klass *obj = (Obj##klass *)AS_OBJ(this);                              \
    return mapper(obj->attr);                                                  \
  }

#define ALIAS_OPERATOR(klass, from, to, op, arity)                             \
  static NativeMethod SECTION(natives) klass##_##to##_native = {               \
      #klass,                                                                  \
      op,                                                                      \
      arity,                                                                   \
      klass##_##from,                                                          \
  }

#define COMPILED_SOURCE(name)                                                  \
  extern ObjFun *name##_lita();                                                \
  static BootFunction SECTION(boot_functions)                                  \
      name##_lita_boot = {#name, name##_lita};

Value defineNative(const char *name, int arity, NativeFn fun);

InterpretResult defineNatives();

#endif
