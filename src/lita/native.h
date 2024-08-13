#ifndef lita_native_h
#define lita_native_h

#define foreach_native(var) section_foreach_entry(natives, NativeMethod, var)

#define NATIVE_ACCESSOR(klass, attr, mapper)                                   \
  static Value klass##_##attr(Value self, int argc, Value *args) {             \
    Obj##klass *obj = (Obj##klass *)AS_OBJ(self);                              \
    return mapper(obj->attr);                                                  \
  }                                                                            \
  static NativeMethod __attribute__((                                          \
      used, section("__DATA,natives"))) klass##_##attr##_native = {            \
      .class_name = #klass,                                                    \
      .name = #attr,                                                           \
      .arity = 0,                                                              \
      .fun = klass##_##attr,                                                   \
  };

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

extern NativeMethod __start_natives __asm("section$start$__DATA$natives");
extern NativeMethod __stop_natives __asm("section$end$__DATA$natives");

Value defineNative(const char *name, int arity, NativeFn fun);

let Any_self(let this, int argc, let *args);

InterpretResult defineNatives();

#endif
