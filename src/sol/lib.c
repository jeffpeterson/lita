#include <assert.h>
#include <string.h>

#include "lib.h"
#include "memory.h"
#include "string.h"
#include "system.h"
#include "tuple.h"
#include "vm.h"

bool isBool(_ x) { return IS_BOOL(x); }
bool isClass(_ x) { return IS_CLASS(x); }
bool isFn(_ x) { return IS_CLOSURE(x); }
bool isInst(_ x) { return IS_INSTANCE(x); }
bool isMethod(_ x) { return IS_BOUND(x); }
bool isNative(_ x) { return IS_NATIVE(x); }
bool isNum(_ x) { return IS_NUMBER(x); }
bool isObj(_ x) { return IS_OBJ(x); }
bool isRange(_ x) { return IS_RANGE(x); }
bool isStr(_ x) { return IS_STRING(x); }
bool isTuple(_ x) { return IS_TUPLE(x); }

bool asBool(_ x) {
  assert(isBool(x));
  return AS_BOOL(x);
}
ObjClass *asClass(_ x) {
  assert(isClass(x));
  return AS_CLASS(x);
}
ObjClosure *asFn(_ x) {
  assert(isFn(x));
  return AS_CLOSURE(x);
}
ObjInstance *asInst(_ x) {
  assert(isInst(x));
  return AS_INSTANCE(x);
}
int asInt(_ x) { return asNum(x); }
ObjBound *asMethod(_ x) {
  assert(isMethod(x));
  return AS_BOUND(x);
}
ObjNative *asNative(_ x) {
  assert(isNative(x));
  return AS_NATIVE(x);
}
double asNum(_ x) {
  assert(isNum(x));
  return AS_NUMBER(x);
}
Obj *asObj(_ x) {
  assert(isObj(x));
  return AS_OBJ(x);
}
ObjRange *asRange(_ x) {
  assert(isRange(x));
  return AS_RANGE(x);
}
ObjString *asStr(_ x) {
  assert(isStr(x));
  return AS_STRING(x);
}
ObjTuple *asTuple(_ x) {
  assert(isTuple(x));
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

_ add(_ a, _ b) {
  if (IS_NUMBER(a) && IS_NUMBER(b))
    return NUMBER_VAL(AS_NUMBER(a) + AS_NUMBER(b));

  if (!IS_OBJ(a)) {
    runtimeError("This type cannot be added.");
    return NIL_VAL;
  }

  Obj *out;
  switch (OBJ_TYPE(a)) {
  case OBJ_STRING:
    out = (Obj *)concatStrings(AS_STRING(a), AS_STRING(toStr(b)));
    break;
  case OBJ_TUPLE:
    out = (Obj *)zipTuples(AS_TUPLE(a), AS_TUPLE(b), add);
    break;
  default:
    runtimeError("Values cannot be added.");
    return NIL_VAL;
  }

  if (out == NULL)
    return NIL_VAL;

  return OBJ_VAL(out);
}

_ subtract(_ a, _ b) {
  if (isNum(a) && isNum(b))
    return num(asNum(a) - asNum(b));

  // if (isStr(a) && isStr(b))
  //   remove b from end of a
  return nil;
}

_ multiply(_ a, _ b) {
  if (isNum(a) && isNum(b))
    return num(asNum(a) * asNum(b));

  if (!IS_OBJ(a)) {
    runtimeError("This type cannot be multiplied.");
    return NIL_VAL;
  }

  Obj *out;
  switch (OBJ_TYPE(a)) {
  case OBJ_STRING:
    out = (Obj *)concatStrings(AS_STRING(a), AS_STRING(toStr(b)));
    break;
  case OBJ_TUPLE:
    out = (Obj *)zipTuples(AS_TUPLE(a), AS_TUPLE(b), multiply);
    break;
  default:
    runtimeError("Values cannot be multiplied.");
    return NIL_VAL;
  }

  if (out == NULL)
    return NIL_VAL;

  return OBJ_VAL(out);
}

_ fprint(FILE *io, _ x) {
  fprintf(io, "%s\n", AS_STRING(toString(x))->chars);
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
  if (IS_BOOL(val) || IS_NUMBER(val) || IS_NIL(val))
    return toStr(val);

  if (IS_OBJ(val)) {
    switch (OBJ_TYPE(val)) {
    case OBJ_BOUND: {
      ObjFun *fun = AS_BOUND(val)->method->fun;
      return OBJ_VAL(stringf("<bound %s/%d>", fun->name->chars, fun->arity));
    }

    case OBJ_CLASS:
      return OBJ_VAL(stringf("<class %s>", AS_CLASS(val)->name->chars));

    case OBJ_CLOSURE:
      return toStr(OBJ_VAL(AS_CLOSURE(val)->fun));

    case OBJ_ERR:
      return OBJ_VAL(stringf("Error(%s)", AS_ERR(val)->msg->chars));

    case OBJ_FUN: {
      ObjFun *fun = AS_BOUND(val)->method->fun;
      return OBJ_VAL(stringf("<fn %s/%d>", fun->name->chars, fun->arity));
    }
    case OBJ_INSTANCE:
      return toStr(OBJ_VAL(AS_INSTANCE(val)->klass));
    case OBJ_NATIVE:
      return OBJ_VAL(AS_NATIVE(val)->name);

    case OBJ_RANGE: {
      ObjRange *range = AS_RANGE(val);
      return OBJ_VAL(stringf("%s..%s", toStr(range->start), toStr(range->end)));
    }

    case OBJ_STRING:
      return OBJ_VAL(stringf("\"%s\"", AS_STRING(val)->chars));

    case OBJ_TUPLE: {
      ObjTuple *tuple = AS_TUPLE(val);

      if (tuple->length < 1)
        return str("");

      let out = inspect(tuple->values[0]);
      for (int i = 1; i < tuple->length; i++) {
        out = add(add(out, str(", ")), inspect(tuple->values[i]));
      }
      return out;
    }

    default:
      break;
    }
  }

  return toString(val);
}

_ get(_ self, _ key) {
  _ value;
  if (isInst(self) && tableGet(&asInst(self)->fields, key, &value))
    return value;

  ObjClass *klass = classOf(self);

  if (tableGet(&klass->methods, key, &value))
    return OBJ_VAL(newBound(self, AS_CLOSURE(value)));

  return nil;
}

_ set(_ self, _ key, _ value) { return error("Not implemented."); }

_ hash(_ val) { return NUMBER_VAL(hashValue(val)); }

_ len(_ x) {
  if (!isObj(x))
    return nil;

  switch (asObj(x)->type) {
  case OBJ_BOUND:
    return len(obj(asMethod(x)->method));

  case OBJ_CLASS:
  case OBJ_CLOSURE:
  case OBJ_ERR:
  case OBJ_FUN:
  case OBJ_INSTANCE:
  case OBJ_NATIVE:
  case OBJ_UPVALUE:

  case OBJ_RANGE:
    return subtract(asRange(x)->end, asRange(x)->start);

  case OBJ_STRING:
  case OBJ_TUPLE:
  default:
    return nil;
  }
}

_ name(_ self) { return error("Not implemented."); }

_ toStr(_ v) { return toString(v); }

_ toString(_ val) {
  if (IS_NUMBER(val))
    return OBJ_VAL(stringf("%g", AS_NUMBER(val)));

  if (IS_BOOL(val))
    return string(AS_BOOL(val) ? "true" : "false");

  if (IS_NIL(val))
    return string("nil");

  if (IS_OBJ(val)) {
    switch (OBJ_TYPE(val)) {
    case OBJ_BOUND:
      return OBJ_VAL(AS_BOUND(val)->method->fun->name);
    case OBJ_CLASS:
      return OBJ_VAL(AS_CLASS(val)->name);
    case OBJ_CLOSURE:
      return toString(OBJ_VAL(AS_CLOSURE(val)->fun));
    case OBJ_ERR:
      return OBJ_VAL(AS_ERR(val)->msg);
    case OBJ_FUN:
      return OBJ_VAL(AS_FUN(val)->name);
    case OBJ_INSTANCE:
      // get(val, string("toString"));
      return toString(OBJ_VAL(AS_INSTANCE(val)->klass));
    case OBJ_NATIVE:
      return OBJ_VAL(AS_NATIVE(val)->name);

    case OBJ_RANGE: {
      ObjRange *range = AS_RANGE(val);
      return OBJ_VAL(
          stringf("%s..%s", toString(range->start), toString(range->end)));
    }

    case OBJ_STRING:
      return val;

    default:
      return str(objInfo[OBJ_TYPE(val)].inspect);
    }
  }

  return obj(stringf("<unknown type %64x>", val));
}

_ class(_ name) {
  if (!isStr(name))
    return nil;

  return pope(OBJ_VAL(newClass(AS_STRING(push(name)))));
}

_ subClass(_ name, _ parent) {
  if (!isClass(parent))
    return nil;

  _ klass = class(name);
  ObjClass *klassObj = AS_CLASS(klass);
  ObjClass *parentObj = AS_CLASS(parent);

  klassObj->parent = parentObj;
  tableAddAll(&parentObj->methods, &klassObj->methods);
  return klass;
}

_ method(_ klass, _ fun) {
  if (!isClass(klass))
    return nil;

  ObjString *name;

  if (IS_FUN(fun)) {
    name = AS_FUN(fun)->name;
  } else if (IS_NATIVE(fun)) {
    name = AS_NATIVE(fun)->name;
  } else if (IS_CLOSURE(fun)) {
    name = AS_CLOSURE(fun)->fun->name;
  } else if (IS_BOUND(fun)) {
    name = AS_BOUND(fun)->method->fun->name;
  } else {
    return error("Method must be callable.");
  }

  tableSet(&AS_CLASS(klass)->methods, push(OBJ_VAL(name)), fun);
  pop();

  return fun;
}

_ read(_ path) {
  if (!isStr(path))
    return error("path must be a string.");

  return obj(readFile(AS_STRING(path)));
}

_ write(_ path, _ content) {
  if (!isStr(path))
    return error("path must be a string.");

  let data = toStr(content);

  if (!writeFile(AS_STRING(path), AS_STRING(data)))
    return error("Could not write to file.");

  return data;
}

_ append(_ path, _ content) {
  if (!isStr(path))
    return error("path must be a string.");

  let data = toStr(content);

  if (!appendFile(AS_STRING(path), AS_STRING(data)))
    return error("Could not append to file.");

  return data;
}
