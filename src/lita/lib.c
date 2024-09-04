#include <assert.h>
#include <string.h>

#include "array.h"
#include "bound.h"
#include "class.h"
#include "lib.h"
#include "memory.h"
#include "string.h"
#include "system.h"
#include "term.h"
#include "tuple.h"
#include "vm.h"

let fn(const char *name, int arity, NativeFn fun) {
  return obj(newNative(newString(name), arity, fun));
}
let memory(u8 *bytes, int length) {
  return obj(copyString((char *)bytes, length));
}
let num(double num) { return NUMBER_VAL(num); }
let str(const char *str) { return obj(newString(str)); }

let method(let klass, let fun) {
  assert(isClass(klass));

  let key = name(fun);

  if (is_nil(key)) {
    return crash("Method must be callable.");
  }

  tableSet(&asClass(klass)->methods, key, fun);

  return fun;
}

let static_method(let klass, let fun) {
  assert(isClass(klass));
  let key = name(fun);
  set(klass, key, fun);
  return klass;
}

let add(let a, let b) {
  push(a);
  push(b);
  vm_add();
  return pop();
}

let subtract(let a, let b) {
  if (is_num(a) && is_num(b)) return num(as_num(a) - as_num(b));

  // if (isString(a) && isString(b))
  //   remove b from end of a
  return nil;
}

let multiply(let a, let b) {
  push(a);
  push(b);
  vm_multiply();
  return pop();
}

/** Returns arity of fun, -1 if not callable. */
int arity(Value fun) {
  if (isBound(fun)) return arity(asBound(fun)->method);
  if (isClosure(fun)) return asClosure(fun)->function->arity;
  if (isNative(fun)) return asNative(fun)->arity;
  if (isClass(fun)) return arity(findMethod(fun, str("init")));

  return -1;
}

let classOf(let self) { return obj(valueClass(self)); }

let superOf(let klass) { return obj(asClass(klass)->parent); }

let bindFn(let self, let fun) {
  if (isClosure(fun) || isNative(fun)) return bound(self, fun);

  return fun;
}

let findMethod(let klass, let name) {
  Value fun = nil;
  while (isClass(klass) && !tableGet(&asClass(klass)->methods, name, &fun))
    klass = superOf(klass);

  return fun;
}

let find(let self, let key) {
  let val;
  if (is_obj(self)) {
    if (tableGet(&AS_OBJ(self)->fields, key, &val)) return val;
    if (isClass(self)) {
      val = find(superOf(self), key);
      if (not_nil(val)) return val;
    }
  }

  return findMethod(classOf(self), key);
}

bool has(let self, let key) { return !is_nil(find(self, key)); }
let get(let self, let key) { return bindFn(self, find(self, key)); }
let set(let self, let key, let value) { return crash("Not implemented."); }

let hash(let val) { return NUMBER_VAL(hash_value(val)); }

u32 len(let x) {
  if (!is_obj(x)) return 1;

  Obj *obj = AS_OBJ(x);

  if (obj->def->length) return obj->def->length(obj);
  return 1;
}

let name(let fn) {
  return isClass(fn)      ? obj(asClass(fn)->name)
         : isFunction(fn) ? obj(asFunction(fn)->name)
         : isNative(fn)   ? obj(asNative(fn)->name)
         : isClosure(fn)  ? obj(asClosure(fn)->function->name)
         : isBound(fn)    ? name(asBound(fn)->method)
                          : nil;
}

let read(let path) { return obj(readFile(as_string(path))); }

let write(let path, let content) {
  if (!writeFile(as_string(path), as_string(content)))
    return crash("Could not write to file.");

  return content;
}

let append(let path, let content) {
  if (!appendFile(as_string(path), as_string(content)))
    return crash("Could not append to file.");

  return content;
}
