#include <assert.h>
#include <string.h>

#include "array.h"
#include "lib.h"
#include "memory.h"
#include "string.h"
#include "system.h"
#include "term.h"
#include "tuple.h"
#include "vm.h"

_ fn(const char *name, int arity, NativeFn fun) {
  return obj(newNative(new_string(name), arity, fun));
}
_ memory(u8 *bytes, int length) {
  return obj(copy_string((char *)bytes, length));
}
_ num(double num) { return NUMBER_VAL(num); }
_ str(const char *str) { return obj(new_string(str)); }

_ class(_ name) {
  if (!is_string(name)) return nil;

  return pope(OBJ_VAL(newClass(AS_STRING(push(name)))));
}
_ method(_ klass, _ fun) {
  assert(is_class(klass));

  let key = name(fun);

  if (is_nil(key)) {
    return crash("Method must be callable.");
  }

  tableSet(&AS_CLASS(klass)->methods, key, fun);

  return fun;
}

let add(let a, let b) {
  push(a);
  push(b);
  vm_add();
  return pop();
}

_ subtract(_ a, _ b) {
  if (is_num(a) && is_num(b)) return num(as_num(a) - as_num(b));

  // if (is_string(a) && is_string(b))
  //   remove b from end of a
  return nil;
}

_ multiply(_ a, _ b) {
  push(a);
  push(b);
  vm_multiply();
  return pop();
}

/** Returns arity of fun, -1 if not callable. */
int arity(_ fun) {
  if (is_bound(fun)) return arity(as_bound(fun)->method);
  if (is_closure(fun)) return as_closure(fun)->fun->arity;
  if (is_native(fun)) return as_native(fun)->arity;
  if (is_class(fun)) return arity(findMethod(fun, str("init")));

  return -1;
}

_ classOf(_ self) { return obj(valueClass(self)); }

_ superOf(_ klass) { return obj(as_class(klass)->parent); }

_ bindFn(_ self, _ fun) {
  if (is_closure(fun) || is_native(fun)) return obj(newBound(self, fun));

  return fun;
}

_ findMethod(_ klass, _ name) {
  Value fun = nil;
  while (is_class(klass) && !tableGet(&as_class(klass)->methods, name, &fun))
    klass = superOf(klass);

  return fun;
}

_ find(_ self, _ key) {
  _ val;
  if (is_obj(self)) {
    if (tableGet(&AS_OBJ(self)->fields, key, &val)) return val;
    if (is_class(self)) {
      val = find(superOf(self), key);
      if (not_nil(val)) return val;
    }
  }

  return findMethod(classOf(self), key);
}

bool has(_ self, _ key) { return !is_nil(find(self, key)); }
_ get(_ self, _ key) { return bindFn(self, find(self, key)); }
_ set(_ self, _ key, _ value) { return crash("Not implemented."); }

_ hash(_ val) { return NUMBER_VAL(hash_value(val)); }

u32 len(_ x) {
  if (!is_obj(x)) return 1;

  Obj *obj = AS_OBJ(x);

  if (obj->def && obj->def->length) return obj->def->length(obj);

  switch (obj->type) {
  case OBJ_BOUND: return len(as_bound(x)->method);

  case OBJ_CLASS:
  case OBJ_CLOSURE:
  case OBJ_FUN:
  case OBJ_NATIVE: return arity(x);

  default: return 1;
  }
}

_ name(_ self) {
  switch (as_obj(self)->type) {
  case OBJ_CLASS: return obj(AS_CLASS(self)->name);
  case OBJ_FUN: return obj(AS_FUN(self)->name);
  case OBJ_NATIVE: return obj(AS_NATIVE(self)->name);
  case OBJ_CLOSURE: return obj(AS_CLOSURE(self)->fun->name);
  case OBJ_BOUND: return name(AS_BOUND(self)->method);
  default: return nil;
  }
}

_ read(_ path) {
  if (!is_string(path)) return crash("path must be a string.");

  return obj(readFile(AS_STRING(path)));
}

let write(let path, let content) {
  if (!writeFile(as_string(path), as_string(content)))
    return crash("Could not write to file.");

  return content;
}

_ append(_ path, _ content) {
  if (!is_string(path)) return crash("path must be a string.");

  if (!appendFile(as_string(path), as_string(content)))
    return crash("Could not append to file.");

  return content;
}
