#ifndef lita_native_h
#define lita_native_h

#include "common.h"
#include "object.h"
#include "value.h"
#include "vm.h"

Value defineNative(const char *name, int arity, NativeFn fun);
let global_class(const char *name);

let Any_self(let this, int argc, let *args);

InterpretResult defineNatives();

#endif
