#ifndef lita_lib_h
#define lita_lib_h

#include <stdio.h>

#include "common.h"
#include "object.h"
#include "string.h"
#include "value.h"

#define fmt(f, ...) obj(string_format(f, ...))

typedef Value _;

_ fn(const char *name, int arity, NativeFn fun);
_ memory(u8 *bytes, int length);
_ num(double num);
_ str(const char *str);

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
_ method(_ klass, _ fun);

// # Files
let read(let path);
let write(let path, let content);
let append(let path, let content);

#endif
