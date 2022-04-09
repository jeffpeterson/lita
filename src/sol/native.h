#ifndef sol_native_h
#define sol_native_h

#include "common.h"
#include "object.h"
#include "value.h"

bool defineNative(const char *name, int arity, NativeFn fun);
void defineNatives();

#endif
