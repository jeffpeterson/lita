#ifndef lita_lib_h
#define lita_lib_h

#include <stdio.h>

#include "common.h"
#include "object.h"
#include "string.h"
#include "value.h"

#define TO_STRING(val) to_string(val)
#define obj(o) OBJ_VAL(o)
#define fmt(f, ...) obj(stringFormat(f, ...))

typedef Value _;

bool asBool(_ x);
ObjClass *asClass(_ x);
ObjClosure *asFn(_ x);
ObjInstance *asInst(_ x);
ObjBound *asBound(_ x);
ObjNative *asNative(_ x);
double asNum(_ x);
Obj *asObj(_ x);
void *asPtr(_ x);
ObjRange *asRange(_ x);

let error(const char *msg);

_ fn(const char *name, int arity, NativeFn fun);
_ memory(u8 *bytes, int length);
_ num(double num);
_ ptr(void *pointer);
_ range(_ start, _ end);
_ str(const char *str);
_ string(const char *str);

_ to_string(_ val);

int arity(_ fun);

_ classOf(_ self);
_ superOf(_ klass);
_ bindFn(_ self, _ fun);
_ findMethod(_ klass, _ name);
_ find(_ self, _ name);

bool has(_ self, _ key);
_ get(_ self, _ key);
_ set(_ self, _ key, _ value);

_ add(_ a, _ b);
_ subtract(_ a, _ b);
_ multiply(_ a, _ b);

_ hash(_ val);
u32 len(_ val);
_ name(_ val);

_ class(_ name);
_ subClass(_ name, _ parent);
_ method(_ klass, _ fun);

_ pp(_ x);
_ fprint(FILE *io, _ x);
_ print(_ x);
_ inspect(_ val);

// # Files
_ read(_ path);
_ write(_ path, _ content);
_ append(_ path, _ content);

#endif
