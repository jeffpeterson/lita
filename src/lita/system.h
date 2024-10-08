#ifndef lita_system_h
#define lita_system_h

#include "common.h"
#include "object.h"

ObjString *readFile(ObjString *path);
bool writeFile(ObjString *path, ObjString *content);
bool appendFile(ObjString *path, ObjString *content);

void runFile(ObjString *path);
void compileFileToC(ObjString *path);

Value getEnv(Value name);

#endif
