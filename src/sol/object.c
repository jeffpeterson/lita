#include <stdio.h>
#include <string.h>

#include "lib.h"
#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"
#include "vm.h"

const ObjInfo objInfo[11] = {
    [OBJ_BOUND] = {"BOUND", "Method"},
    [OBJ_CLASS] = {"CLASS", "Class"},
    [OBJ_CLOSURE] = {"CLOSURE", "Function"},
    [OBJ_ERR] = {"ERR", "Error"},
    [OBJ_FUN] = {"FUN", NULL},
    [OBJ_INSTANCE] = {"INSTANCE", NULL},
    [OBJ_NATIVE] = {"NATIVE", "NativeFunction"},
    [OBJ_UPVALUE] = {"UPVALUE", NULL},
    [OBJ_RANGE] = {"RANGE", "Range"},
    [OBJ_STRING] = {"STRING", "String"},
    [OBJ_TUPLE] = {"TUPLE", "Tuple"},
};

Obj *allocateObject(size_t size, ObjType type) {
  Obj *obj = (Obj *)reallocate(NULL, 0, size);
  obj->type = type;
  obj->isMarked = false;
  // Todo: Only hash for non-interned objects.
  Value val = OBJ_VAL(obj);
  obj->hash = hashBytes((char *)&val, sizeof(Value));
  obj->next = vm.objects;
  vm.objects = obj;

#ifdef DEBUG_LOG_MEM
  fprintf(stderr, "%p allocate %zub for ", (void *)obj, size);
  fprintObjType(stderr, type);
  fprintf(stderr, "\n");
#endif
  return obj;
}

ObjBound *newBound(Value receiver, ObjClosure *method) {
  ObjBound *bound = ALLOCATE_OBJ(ObjBound, OBJ_BOUND);
  bound->receiver = receiver;
  bound->method = method;
  return bound;
}

ObjClass *newClass(ObjString *name) {
  ObjClass *klass = ALLOCATE_OBJ(ObjClass, OBJ_CLASS);
  klass->name = name;
  klass->parent = NULL;
  initTable(&klass->methods);
  return klass;
}

ObjClosure *newClosure(ObjFun *fun) {
  ObjUpvalue **upvalues = ALLOCATE(ObjUpvalue *, fun->upvalueCount);
  for (int i = 0; i < fun->upvalueCount; i++)
    upvalues[i] = NULL;

  ObjClosure *closure = ALLOCATE_OBJ(ObjClosure, OBJ_CLOSURE);
  closure->fun = fun;
  closure->upvalues = upvalues;
  closure->upvalueCount = fun->upvalueCount;
  return closure;
}

ObjErr *newError(ObjString *msg) {
  ObjErr *err = ALLOCATE_OBJ(ObjErr, OBJ_ERR);
  err->msg = msg;
  return err;
}

ObjInstance *newInstance(ObjClass *klass) {
  ObjInstance *inst = ALLOCATE_OBJ(ObjInstance, OBJ_INSTANCE);
  inst->klass = klass;
  initTable(&inst->fields);
  return inst;
}

ObjFun *newFunction() {
  ObjFun *fun = ALLOCATE_OBJ(ObjFun, OBJ_FUN);
  fun->arity = 0;
  fun->upvalueCount = 0;
  fun->name = NULL;
  initChunk(&fun->chunk);
  return fun;
}

ObjNative *newNative(ObjString *name, int arity, NativeFn fun) {
  ObjNative *native = ALLOCATE_OBJ(ObjNative, OBJ_NATIVE);
  native->arity = arity;
  native->fun = fun;
  native->name = name;
  return native;
}

ObjUpvalue *newUpvalue(Value *slot) {
  ObjUpvalue *upvalue = ALLOCATE_OBJ(ObjUpvalue, OBJ_UPVALUE);
  upvalue->closed = NIL_VAL;
  upvalue->location = slot;
  upvalue->next = NULL;
  return upvalue;
}

ObjRange *makeRange(Value start, Value end) {
  ObjRange *range = ALLOCATE_OBJ(ObjRange, OBJ_RANGE);
  range->start = start;
  range->end = end;
  range->obj.hash = hashBytes((char *)&range->start, sizeof(Value) * 2);
  return range;
}

const char *objectBytes(Obj *obj, int length) {
  switch (obj->type) {
  case OBJ_RANGE: {
    if (length != sizeof(Value) * 2)
      return NULL;

    ObjRange *range = (ObjRange *)obj;
    return (char *)&range->start;
  }

  case OBJ_STRING: {
    ObjString *str = (ObjString *)obj;
    if (length != str->length)
      return NULL;
    return str->chars;
  }

  case OBJ_TUPLE: {
    ObjTuple *tuple = (ObjTuple *)obj;
    if (length != tuple->length * sizeof(Value))
      return NULL;

    return (char *)tuple->values;
  }

  default:
    return NULL;
  }
}

void fprintObjType(FILE *io, ObjType type) {
  fprintf(io, "%s", objInfo[type].inspect);
}

void fprintFunction(FILE *io, const char *kind, ObjFun *fun) {
  fprintf(io, "\e[35m<%s %s\e[39m/\e[35m%d>\e[39m", kind, fun->name->chars,
          fun->arity);
}

void fprintObject(FILE *io, Obj *obj) {
  switch (obj->type) {
  case OBJ_BOUND: {
    fprintFunction(io, "bound", ((ObjBound *)obj)->method->fun);
    break;
  }

  case OBJ_CLASS: {
    ObjClass *klass = (ObjClass *)obj;
    fprintf(io, "%s", klass->name->chars);
    fprintTable(io, &klass->methods);
    break;
  }

  case OBJ_CLOSURE:
    fprintFunction(io, "fn", ((ObjClosure *)obj)->fun);
    break;

  case OBJ_ERR:
    fprintf(io, "Error: %s", ((ObjErr *)obj)->msg->chars);
    break;

  case OBJ_FUN:
    fprintFunction(io, "ObjFun", (ObjFun *)obj);
    break;

  case OBJ_INSTANCE:
    fprintf(io, "<%s instance>", ((ObjInstance *)obj)->klass->name->chars);
    break;

  case OBJ_NATIVE: {
    ObjNative *native = (ObjNative *)obj;
    fprintf(io, "\e[35m<native %s/%d>\e[39m", native->name->chars,
            native->arity);
    break;
  }

  case OBJ_RANGE: {
    ObjRange *range = (ObjRange *)obj;
    fprintValue(io, range->start);
    fprintf(io, "..");
    fprintValue(io, range->end);
    break;
  }

  case OBJ_STRING:
    fprintf(io, "\e[32m\"%s\"\e[39m", ((ObjString *)obj)->chars);
    break;

  case OBJ_TUPLE: {
    ObjTuple *tuple = (ObjTuple *)obj;
    fprintf(io, "(");
    for (int i = 0; i < tuple->length; i++) {
      if (i > 0)
        fprintf(io, ", ");
      fprintValue(io, tuple->values[i]);
    }
    fprintf(io, ")");
    break;
  }

  case OBJ_UPVALUE: {
    ObjUpvalue *up = (ObjUpvalue *)obj;
    fprintf(io, "<upvalue -> ");
    fprintValue(io, *up->location);
    fprintf(io, ">");
    break;
  }
  }
}

int cmpObjects(Obj *a, Obj *b) {
  int td = a->type - b->type;

  if (td != 0)
    return td;

  if (a == b)
    return 0;

  switch (a->type) {
  case OBJ_BOUND:
  default:
    // Todo: finish
    return a - b;
  }
}
