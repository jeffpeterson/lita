#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "memory.h"
#include "object.h"
#include "table.h"
#include "term.h"
#include "vm.h"

const ObjInfo objInfo[13] = {
    [OBJ_BOUND] = {"BOUND", "Method"},
    [OBJ_CLASS] = {"CLASS", "Class"},
    [OBJ_CLOSURE] = {"CLOSURE", "Function"},
    [OBJ_CUSTOM] = {"CUSTOM", NULL},
    [OBJ_ERR] = {"ERR", "Error"},
    [OBJ_FUN] = {"FUN", NULL},
    [OBJ_INSTANCE] = {"INSTANCE", NULL},
    [OBJ_NATIVE] = {"NATIVE", "NativeFunction"},
    [OBJ_UPVALUE] = {"UPVALUE", NULL},
    [OBJ_RANGE] = {"RANGE", "Range"},
    [OBJ_STRING] = {"STRING", "String"},
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

ObjBound *newBound(Value receiver, Value method) {
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
  for (int i = 0; i < fun->upvalueCount; i++) upvalues[i] = NULL;

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
  if (obj->def && obj->def->bytes) return obj->def->bytes(obj, length);

  switch (obj->type) {
  case OBJ_RANGE: {
    if (length != sizeof(Value) * 2) return NULL;

    ObjRange *range = (ObjRange *)obj;
    return (char *)&range->start;
  }

  case OBJ_CUSTOM:
    if (length != obj->def->size) return NULL;
    return (char *)&obj->hash;

  default: return NULL;
  }
}

int fprintObjType(FILE *io, ObjType type) {
  return fprintf(io, "%s", objInfo[type].inspect);
}

int fprintFunction(FILE *io, const char *kind, ObjFun *fun) {
  return fprintf(io,
                 FG_MAGENTA "<%s %s" FG_DEFAULT "/" FG_MAGENTA "%d>" FG_DEFAULT,
                 kind, fun->name->chars, fun->arity) -
         20;
}

int fprintObject(FILE *io, Obj *obj) {
  if (obj->def && obj->def->inspect) return obj->def->inspect(obj, io);

  switch (obj->type) {
  case OBJ_BOUND: return fprintObject(io, AS_OBJ(((ObjBound *)obj)->method));

  case OBJ_CLASS: {
    ObjClass *klass = (ObjClass *)obj;
    return fprintf(io, "%s { ", klass->name->chars) +
           fprintTable(io, &klass->methods) + fputs(" }", io);
  }

  case OBJ_CLOSURE: return fprintFunction(io, "fn", ((ObjClosure *)obj)->fun);

  case OBJ_CUSTOM: return fprintf(io, "<custom %s>", obj->def->class_name);

  case OBJ_ERR: return fprintf(io, "Error: %s", ((ObjErr *)obj)->msg->chars);

  case OBJ_FUN: return fprintFunction(io, "ObjFun", (ObjFun *)obj);

  case OBJ_INSTANCE: {
    ObjInstance *inst = (ObjInstance *)obj;
    return fprintf(io, "%s(", inst->klass->name->chars) +
           fprintTable(io, &inst->fields) + fprintf(io, ")");
  }
  case OBJ_NATIVE: {
    ObjNative *native = (ObjNative *)obj;
    return fprintf(io, FG_MAGENTA "<native %s/%d>" FG_DEFAULT,
                   native->name->chars, native->arity) -
           10;
  }

  case OBJ_RANGE: {
    ObjRange *range = (ObjRange *)obj;
    return fprintValue(io, range->start) + fprintf(io, "..") +
           fprintValue(io, range->end);
  }

  case OBJ_UPVALUE: {
    ObjUpvalue *up = (ObjUpvalue *)obj;
    return fprintf(io, "<upvalue -> ") + fprintValue(io, *up->location) +
           fprintf(io, ">");
  }

  default: fprintf(stderr, "inspect not implemented for this object"); exit(1);
  }
}

int cmpObjects(Obj *a, Obj *b) {
  int td = a->type - b->type;

  if (td != 0) return td;

  if (a == b) return 0;

  switch (a->type) {
  case OBJ_BOUND:
  default:
    // Todo: finish
    return a - b;
  }
}
