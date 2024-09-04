#ifndef lita_lib_h
#define lita_lib_h

#include <stdio.h>

#include "common.h"
#include "native.h"
#include "object.h"
#include "string.h"
#include "value.h"

#define fmt(f, ...) obj(string_format(f, ...))

typedef Value let;

let fn(const char *name, int arity, NativeFn fun);
let memory(u8 *bytes, int length);
let num(double num);
let str(const char *str);

int arity(let fun);

let classOf(let self);
let superOf(let klass);
let bindFn(let self, let fun);
let findMethod(let klass, let name);
let find(let self, let name);

bool has(let self, let key);
let get(let self, let key);
let set(let self, let key, let value);

let add(let a, let b);
let subtract(let a, let b);
let multiply(let a, let b);

let hash(let val);
u32 len(let val);
let name(let fn);

let method(let klass, let fun);
let static_method(let klass, let fun);

// # Files
let read(let path);
let write(let path, let content);
let append(let path, let content);

#endif
