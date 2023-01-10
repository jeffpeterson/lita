#ifndef sol_native_h
#define sol_native_h

#include "common.h"
#include "object.h"
#include "value.h"
#include "vm.h"

bool defineNative(const char *name, int arity, NativeFn fun);
let global_class(const char *name);

InterpretResult defineNatives();

#endif
