#ifndef lita_native_h
#define lita_native_h

#include "common.h"
#include "function.h"
#include "object.h"
#include "string.h"
#include "value.h"

#define allocateNative() ALLOCATE_OBJ(Native)
#define isNative(val) is_obj_def(val, &Native)
#define asNative(val) as(Native, val)

#define AS_NATIVE(val) ((ObjNative *)AS_OBJ(val))
#define AS_NATIVE_FN(val) (AS_NATIVE(val)->fun)

typedef Value NativeFn(Value self, int argCount, Value *args);

typedef struct ObjNative {
  Obj obj;
  int arity;
  ObjString *name;
  NativeFn *fun;
} ObjNative;

ObjNative *newNative(ObjString *name, int arity, NativeFn fun);

ObjDef Native;

typedef struct NativeMethod {
  const char *class_name;
  const char *name;
  int arity;
  NativeFn *fun;
  bool is_static;
} NativeMethod;

typedef struct BootFunction {
  const char *name;
  ObjFunction *(*fun)();
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

#define STATIC_METHOD_NAMED(klass, attr, name, arity)                          \
  static Value klass_static##_##attr(Value this, int argc, Value *args);       \
  static NativeMethod SECTION(natives) klass##_##attr##_native = {             \
      #klass, name, arity, klass##_##attr, true,                               \
  };                                                                           \
  static Value klass_static##_##attr(Value this, int argc, Value *args)

#define STATIC_METHOD(klass, attr, arity)                                      \
  STATIC_METHOD_NAMED(klass, attr, #attr, arity)

#define COMPILED_SOURCE(name)                                                  \
  extern ObjFunction *name##_lita();                                           \
  static BootFunction SECTION(boot_functions)                                  \
      name##_lita_boot = {#name, name##_lita};

#endif
