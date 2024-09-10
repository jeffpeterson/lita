#ifndef lita_compiler_h
#define lita_compiler_h

#include "function.h"
#include "object.h"

ObjFunction *compile(const char *source, ObjString *path);
void markCompilerRoots();

#endif
