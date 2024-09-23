#ifndef lita_lib_h
#define lita_lib_h

#include "common.h"
#include "value.h"

#define fmt(f, ...) obj(string_format(f, ...))

let memory(u8 *bytes, int length);
let num(double num);

int arity(let fun);

let classOf(let self);
let superOf(let klass);
let bindFn(let self, let fun);
let findMethod(let klass, let name);
let find(let self, let name);

bool has(let self, let key);
let get(let self, let key);
let set(let self, let key, let value);

let name(let fn);

let method(let klass, let fun);
let static_method(let klass, let fun);

#endif
