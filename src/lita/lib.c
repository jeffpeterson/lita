#include <assert.h>
#include <string.h>

#include "array.h"
#include "bound.h"
#include "class.h"
#include "lib.h"
#include "memory.h"
#include "string.h"
#include "term.h"
#include "tuple.h"
#include "vm.h"

let memory(u8 *bytes, int length) {
  return obj(copyString((char *)bytes, length));
}
let num(double num) { return NUMBER_VAL(num); }

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

/** Returns arity of fun, -1 if not callable. */
int arity(Value fun) {
  if (isBound(fun)) return arity(asBound(fun)->method);
  if (isClosure(fun)) return asClosure(fun)->function->arity;
  if (isNative(fun)) return asNative(fun)->arity;
  if (isClass(fun)) return arity(findMethod(fun, string("init")));

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

let name(let fn) {
  return isClass(fn)      ? obj(asClass(fn)->name)
         : isFunction(fn) ? obj(asFunction(fn)->name)
         : isNative(fn)   ? obj(asNative(fn)->name)
         : isClosure(fn)  ? obj(asClosure(fn)->function->name)
         : isBound(fn)    ? name(asBound(fn)->method)
                          : nil;
}
