#ifndef sol_system_h
#define sol_system_h

#include "common.h"
#include "object.h"

ObjString *readFile(ObjString *path);
bool writeFile(ObjString *path, ObjString *content);
bool appendFile(ObjString *path, ObjString *content);

void runFile(ObjString *path);
void compileFile(ObjString *path);

#endif
