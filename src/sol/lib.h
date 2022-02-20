#ifndef sol_lib_h
#define sol_lib_h

#include <stdio.h>

#include "common.h"
#include "object.h"
#include "value.h"

#define TO_STRING(val) toString(val)
#define obj(o) OBJ_VAL(o)

typedef Value let;
typedef Value _;

bool isClass(_ x);
bool isFn(_ x);
bool isInst(_ x);
bool isMethod(_ x);
bool isNative(_ x);
bool isNum(_ x);
bool isObj(_ x);
bool isRange(_ x);
bool isStr(_ x);
bool isTuple(_ x);

_ error(const char *msg);
_ fn(const char *name, int arity, NativeFn fun);
_ memory(u8 *bytes, int length);
_ num(double num);
_ str(const char *str);
_ string(const char *str);
_ t2(_ a, _ b);
_ t3(_ a, _ b, _ c);
_ t4(_ a, _ b, _ c, _ d);
_ t(int len, _ *vals);

_ toStr(_ val);
_ toString(_ val);

_ add(_ a, _ b);
_ multiply(_ a, _ b);

_ hash(_ val);

_ class(_ name);
_ subClass(_ name, _ parent);
_ method(_ klass, _ fun);

_ pp(_ x);
_ fprint(FILE *io, _ x);
_ print(_ x);
_ inspect(_ val);

/// Files
_ read(_ path);
_ write(_ path, _ content);
_ append(_ path, _ content);

#endif
