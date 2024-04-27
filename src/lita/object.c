#include <assert.h>
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
    [OBJ_NATIVE] = {"NATIVE", "NativeFunction"},
    [OBJ_UPVALUE] = {"UPVALUE", NULL},
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
  initTable(&obj->fields);

#ifdef DEBUG_LOG_MEM
  fprintf(stderr, "%p allocate %zub for ", (void *)obj, size);
  inspect_obj_type(stderr, type);
  fprintf(stderr, "\n");
#endif
  return obj;
}

bool as_bool(Value x) {
  assert(is_bool(x));
  return AS_BOOL(x);
}
ObjClass *as_class(Value x) {
  assert(is_class(x));
  return AS_CLASS(x);
}
ObjClosure *as_fn(Value x) {
  assert(is_closure(x));
  return AS_CLOSURE(x);
}
ObjBound *as_bound(Value x) {
  assert(is_bound(x));
  return AS_BOUND(x);
}
ObjNative *as_native(Value x) {
  assert(is_native(x));
  return AS_NATIVE(x);
}
double as_num(Value x) {
  assert(is_num(x));
  return AS_NUMBER(x);
}
Obj *as_obj(Value x) {
  assert(is_obj(x));
  return AS_OBJ(x);
}

ObjBound *newBound(Value receiver, Value method) {
  ObjBound *bound = ALLOCATE_OBJ(ObjBound, OBJ_BOUND);
  bound->receiver = receiver;
  bound->method = method;
  return bound;
}

Obj *newObject(ObjClass *klass) {
  Obj *obj = ALLOCATE_OBJ(Obj, OBJ_CUSTOM);
  obj->klass = klass;
  return obj;
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

const char *objectBytes(Obj *obj, int length) {
  if (obj->def && obj->def->bytes) return obj->def->bytes(obj, length);

  switch (obj->type) {
  case OBJ_CUSTOM:
    if (length != obj->def->size) return NULL;
    return (char *)&obj->hash;

  default: return NULL;
  }
}

int inspect_obj_type(FILE *io, ObjType type) {
  return fprintf(io, "%s", objInfo[type].inspect);
}

int inspect_function(FILE *io, const char *kind, ObjFun *fun) {
  return fprintf(io,
                 FG_MAGENTA "<%s %s" FG_DEFAULT "/" FG_MAGENTA "%d>" FG_DEFAULT,
                 kind, fun->name->chars, fun->arity) -
         20;
}

int inspect_obj(FILE *io, Obj *obj) {
  if (obj->def && obj->def->inspect) return obj->def->inspect(obj, io);

  switch (obj->type) {
  case OBJ_BOUND: return inspect_obj(io, AS_OBJ(((ObjBound *)obj)->method));

  case OBJ_CLASS: {
    ObjClass *klass = (ObjClass *)obj;
    return fprintf(io, "%s { ", klass->name->chars) +
           inspect_table(io, &klass->methods) + fputs(" }", io);
  }

  case OBJ_CLOSURE: return inspect_function(io, "fn", ((ObjClosure *)obj)->fun);

  case OBJ_CUSTOM: return fprintf(io, "<custom %s>", obj->def->class_name);

  case OBJ_ERR: return fprintf(io, "Error: %s", ((ObjErr *)obj)->msg->chars);

  case OBJ_FUN: return inspect_function(io, "ObjFun", (ObjFun *)obj);

  case OBJ_NATIVE: {
    ObjNative *native = (ObjNative *)obj;
    return fprintf(io, FG_MAGENTA "<native %s/%d>" FG_DEFAULT,
                   native->name->chars, native->arity) -
           10;
  }

  case OBJ_UPVALUE: {
    ObjUpvalue *up = (ObjUpvalue *)obj;
    return fprintf(io, "<upvalue -> ") + inspect_value(io, *up->location) +
           fprintf(io, ">");
  }

  default:
    return fprintf(io, "%s(", obj->klass->name->chars) +
           inspect_table(io, &obj->fields) + fprintf(io, ")");
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
