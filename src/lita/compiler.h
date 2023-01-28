#ifndef lita_compiler_h
#define lita_compiler_h

#include "object.h"

ObjFun *compile(const char *source, ObjString *name);
void markCompilerRoots();

#endif
