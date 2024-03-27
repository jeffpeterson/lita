#include <assert.h>
#include <string.h>

#include "array.h"
#include "lib.h"
#include "memory.h"
#include "string.h"
#include "system.h"
#include "tuple.h"
#include "vm.h"

bool asBool(_ x) {
  assert(is_bool(x));
  return AS_BOOL(x);
}
ObjClass *asClass(_ x) {
  assert(is_class(x));
  return AS_CLASS(x);
}
ObjClosure *asFn(_ x) {
  assert(is_closure(x));
  return AS_CLOSURE(x);
}
ObjInstance *asInst(_ x) {
  assert(is_instance(x));
  return AS_INSTANCE(x);
}
ObjBound *asBound(_ x) {
  assert(is_bound(x));
  return AS_BOUND(x);
}
ObjNative *asNative(_ x) {
  assert(is_native(x));
  return AS_NATIVE(x);
}
double asNum(_ x) {
  assert(is_num(x));
  return AS_NUMBER(x);
}
Obj *asObj(_ x) {
  assert(is_obj(x));
  return AS_OBJ(x);
}
void *asPtr(_ x) {
  assert(is_ptr(x));
  return AS_PTR(x);
}
ObjRange *asRange(_ x) {
  assert(is_range(x));
  return AS_RANGE(x);
}
ObjTuple *asTuple(_ x) {
  assert(is_tuple(x));
  return AS_TUPLE(x);
}

_ error(const char *msg) { return obj(newError(newString(msg))); }
_ fn(const char *name, int arity, NativeFn fun) {
  return obj(newNative(newString(name), arity, fun));
}
_ memory(u8 *bytes, int length) {
  return obj(copyString((char *)bytes, length));
}
_ num(double num) { return NUMBER_VAL(num); }
_ ptr(void *pointer) { return PTR_VAL(pointer); }
_ range(_ start, _ end) { return obj(makeRange(start, end)); }
_ str(const char *str) { return obj(newString(str)); }
_ string(const char *str) { return obj(newString(str)); }

_ t(int len, _ *vals) { return obj(copyTuple(vals, len)); }

_ t2(_ a, _ b) { return t(2, (_[]){a, b}); }
_ t3(_ a, _ b, _ c) { return t(3, (_[]){a, b, c}); }
_ t4(_ a, _ b, _ c, _ d) { return t(4, (_[]){a, b, c, d}); }
_ t5(_ a, _ b, _ c, _ d, _ e) { return t(5, (_[]){a, b, c, d, e}); }
_ t6(_ a, _ b, _ c, _ d, _ e, _ f) { return t(6, (_[]){a, b, c, d, e, f}); }
_ t7(_ a, _ b, _ c, _ d, _ e, _ f, _ g) {
  return t(7, (_[]){a, b, c, d, e, f, g});
}

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

_ add(_ a, _ b) {
  if (is_num(a) && is_num(b)) return num(AS_NUMBER(a) + AS_NUMBER(b));

  if (!is_obj(a)) {
    runtimeError("This type cannot be added.");
    return nil;
  }

  Obj *out;
  switch (obj_type(a)) {
  case OBJ_STRING:
    out = (Obj *)concatStrings(AS_STRING(a), AS_STRING(to_string(b)));
    break;
  case OBJ_TUPLE: out = (Obj *)zipTuples(AS_TUPLE(a), AS_TUPLE(b), add); break;
  default: runtimeError("Values cannot be added."); return nil;
  }

  if (out == NULL) return nil;

  return obj(out);
}

_ subtract(_ a, _ b) {
  if (is_num(a) && is_num(b)) return num(asNum(a) - asNum(b));

  // if (is_string(a) && is_string(b))
  //   remove b from end of a
  return nil;
}

_ multiply(_ a, _ b) {
  if (is_num(a) && is_num(b)) return num(asNum(a) * asNum(b));

  if (!is_obj(a)) {
    runtimeError("This type cannot be multiplied.");
    return NIL_VAL;
  }

  Obj *out;
  switch (obj_type(a)) {
  case OBJ_STRING:
    out = (Obj *)concatStrings(AS_STRING(a), AS_STRING(to_string(b)));
    break;
  case OBJ_TUPLE:
    out = (Obj *)zipTuples(AS_TUPLE(a), AS_TUPLE(b), multiply);
    break;
  default: runtimeError("Values cannot be multiplied."); return NIL_VAL;
  }

  if (out == NULL) return NIL_VAL;

  return OBJ_VAL(out);
}

/** Returns arity of fun, -1 if not callable. */
int arity(_ fun) {
  if (is_bound(fun)) return arity(asBound(fun)->method);
  if (is_closure(fun)) return asFn(fun)->fun->arity;
  if (is_native(fun)) return asNative(fun)->arity;
  if (is_class(fun)) return arity(findMethod(fun, str("init")));

  return -1;
}

_ classOf(_ self) { return obj(valueClass(self)); }

_ superOf(_ klass) { return obj(asClass(klass)->parent); }

_ bindFn(_ self, _ fun) {
  if (is_closure(fun) || is_native(fun)) return obj(newBound(self, fun));

  return fun;
}

_ findMethod(_ klass, _ name) {
  Value fun = nil;
  while (is_class(klass) && !tableGet(&asClass(klass)->methods, name, &fun))
    klass = superOf(klass);

  return fun;
}

_ find(_ self, _ key) {
  _ val;
  if (is_instance(self) && tableGet(&asInst(self)->fields, key, &val))
    return val;

  return findMethod(classOf(self), key);
}

bool has(_ self, _ key) { return !is_nil(find(self, key)); }
_ get(_ self, _ key) { return bindFn(self, find(self, key)); }
_ set(_ self, _ key, _ value) { return error("Not implemented."); }

_ hash(_ val) { return NUMBER_VAL(hashValue(val)); }

u32 len(_ x) {
  if (!is_obj(x)) return 0;

  switch (asObj(x)->type) {
  case OBJ_ARRAY: return AS_ARRAY(x)->length;
  case OBJ_BOUND: return len(asBound(x)->method);
  case OBJ_RANGE: return subtract(asRange(x)->end, asRange(x)->start);

  case OBJ_CLASS:
  case OBJ_CLOSURE:
  case OBJ_FUN:
  case OBJ_NATIVE: return arity(x);

  case OBJ_STRING: return as_string(x)->length;
  case OBJ_INSTANCE: return asInst(x)->fields.len;
  case OBJ_TUPLE: return asTuple(x)->length;

  case OBJ_CUSTOM:
  case OBJ_ERR:
  case OBJ_UPVALUE: return 0;
  }
}

_ name(_ self) {
  switch (asObj(self)->type) {
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
    case OBJ_INSTANCE:
      // get(val, string("to_string"));
      return to_string(OBJ_VAL(AS_INSTANCE(val)->klass));

    case OBJ_RANGE: {
      ObjRange *range = AS_RANGE(val);
      return OBJ_VAL(
          stringf("%s..%s", to_string(range->start), to_string(range->end)));
    }

    case OBJ_STRING: return val;

    default: return str(objInfo[obj_type(val)].inspect);
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
    switch (obj_type(val)) {
    case OBJ_BOUND: return add(str("bound:"), inspect(AS_BOUND(val)->method));

    case OBJ_CLASS:
      return OBJ_VAL(stringf("<class %s>", AS_CLASS(val)->name->chars));

    case OBJ_CLOSURE: return to_string(OBJ_VAL(AS_CLOSURE(val)->fun));

    case OBJ_ERR: return OBJ_VAL(stringf("Error(%s)", AS_ERR(val)->msg->chars));

    case OBJ_FUN: {
      ObjFun *fun = AS_FUN(val);
      return OBJ_VAL(stringf("<fn %s/%d>", fun->name->chars, fun->arity));
    }
    case OBJ_INSTANCE: return to_string(OBJ_VAL(AS_INSTANCE(val)->klass));
    case OBJ_NATIVE: return OBJ_VAL(AS_NATIVE(val)->name);

    case OBJ_RANGE: {
      ObjRange *range = AS_RANGE(val);
      return OBJ_VAL(
          stringf("%s..%s", to_string(range->start), to_string(range->end)));
    }

    case OBJ_STRING: return OBJ_VAL(stringf("\"%s\"", AS_STRING(val)->chars));

    case OBJ_TUPLE: {
      ObjTuple *tuple = AS_TUPLE(val);

      if (tuple->length < 1) return str("");

      let out = inspect(tuple->values[0]);
      for (int i = 1; i < tuple->length; i++) {
        out = add(add(out, str(", ")), inspect(tuple->values[i]));
      }
      return out;
    }

    default: break;
    }
  }

  return to_string(val);
}
