#ifndef sol_compiler_h
#define sol_compiler_h

#include "object.h"

ObjFun *compile(const char *source);
void markCompilerRoots();

#endif
