#include <assert.h>
#include <string.h>

#include "array.h"
#include "lib.h"
#include "memory.h"
#include "string.h"
#include "system.h"
#include "tuple.h"
#include "vm.h"

let error(const char *msg) { return obj(newError(new_string(msg))); }

_ fn(const char *name, int arity, NativeFn fun) {
  return obj(newNative(new_string(name), arity, fun));
}
_ memory(u8 *bytes, int length) {
  return obj(copy_string((char *)bytes, length));
}
_ num(double num) { return NUMBER_VAL(num); }
_ str(const char *str) { return obj(new_string(str)); }
_ string(const char *str) { return obj(new_string(str)); }

_ class(_ name) {
  if (!is_string(name)) return nil;

  return pope(OBJ_VAL(newClass(AS_STRING(push(name)))));
}

_ subClass(_ name, _ parent) {
  if (!is_class(parent)) return nil;

  _ klass = class(name);
  ObjClass *klassObj = AS_CLASS(klass);
  ObjClass *parentObj = AS_CLASS(parent);

  klassObj->parent = parentObj;
  tableAddAll(&parentObj->methods, &klassObj->methods);
  return klass;
}

_ method(_ klass, _ fun) {
  assert(is_class(klass));

  let key = name(fun);

  if (is_nil(key)) {
    return error("Method must be callable.");
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
  if (is_closure(fun)) return as_fn(fun)->fun->arity;
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
  if (is_obj(self) && tableGet(&AS_OBJ(self)->fields, key, &val)) return val;

  return findMethod(classOf(self), key);
}

bool has(_ self, _ key) { return !is_nil(find(self, key)); }
_ get(_ self, _ key) { return bindFn(self, find(self, key)); }
_ set(_ self, _ key, _ value) { return error("Not implemented."); }

_ hash(_ val) { return NUMBER_VAL(hashValue(val)); }

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
  if (!is_string(path)) return error("path must be a string.");

  return obj(readFile(AS_STRING(path)));
}

_ write(_ path, _ content) {
  if (!is_string(path)) return error("path must be a string.");

  let data = to_string(content);

  if (!writeFile(AS_STRING(path), AS_STRING(data)))
    return error("Could not write to file.");

  return data;
}

_ append(_ path, _ content) {
  if (!is_string(path)) return error("path must be a string.");

  let data = to_string(content);

  if (!appendFile(AS_STRING(path), AS_STRING(data)))
    return error("Could not append to file.");

  return data;
}

_ to_string(_ val) {
  if (is_int(val)) return OBJ_VAL(stringf("%d", as_int(val)));

  if (is_num(val)) return OBJ_VAL(stringf("%g", AS_NUMBER(val)));

  if (is_bool(val)) return string(AS_BOOL(val) ? "true" : "false");

  if (is_nil(val)) return string("nil");

  if (is_obj(val)) {
    switch (obj_type(val)) {
    case OBJ_CLASS: return OBJ_VAL(AS_CLASS(val)->name);

    case OBJ_BOUND:
    case OBJ_CLOSURE:
    case OBJ_FUN:
    case OBJ_NATIVE: return name(val);

    case OBJ_ERR: return OBJ_VAL(AS_ERR(val)->msg);

    // default: return str(objInfo[obj_type(val)].inspect);
    default: return send(val, str("string"), 0);
    }
  }

  return obj(stringf("<unknown type %64x>", val));
}

_ fprint(FILE *io, _ x) {
  fprintf(io, "%s\n", AS_STRING(to_string(x))->chars);
  return x;
}
_ print(_ x) {
  return fprint(stdout, x);
  return x;
}

_ pp(_ x) {
  fprint(stderr, inspect(x));
  return x;
}

_ inspect(_ val) {
  if (is_bool(val) || is_num(val) || is_nil(val)) return to_string(val);

  if (is_obj(val)) {
    Obj *obj = AS_OBJ(val);

    if (obj->def && obj->def->inspect) {
      char *str = NULL;
      size_t len = 0;
      FILE *io = open_memstream(&str, &len);
      obj->def->inspect(obj, io);
      fclose(io);
      let val = OBJ_VAL(take_string(str, len));

      return val;
    }

    switch (obj->type) {
    case OBJ_BOUND: return add(str("bound:"), inspect(AS_BOUND(val)->method));

    case OBJ_CLASS:
      return OBJ_VAL(stringf("<class %s>", AS_CLASS(val)->name->chars));

    case OBJ_CLOSURE: return to_string(OBJ_VAL(AS_CLOSURE(val)->fun));

    case OBJ_CUSTOM: return OBJ_VAL(stringf("<%s>", obj->def->class_name));

    case OBJ_ERR: return OBJ_VAL(stringf("Error(%s)", AS_ERR(val)->msg->chars));

    case OBJ_FUN: {
      ObjFun *fun = AS_FUN(val);
      return OBJ_VAL(stringf("<fn %s/%d>", fun->name->chars, fun->arity));
    }
    case OBJ_NATIVE: return OBJ_VAL(AS_NATIVE(val)->name);
    default: break;
    }
  }

  return to_string(val);
}
