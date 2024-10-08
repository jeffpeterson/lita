#include <time.h>

#include "lib.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "term.h"
#include "tuple.h"
#include "vm.h"

Value fn(const char *name, int arity, NativeFn fun) {
  return obj(newNative(newString(name), arity, fun));
}

ObjNative *newNative(ObjString *name, int arity, NativeFn fun) {
  ObjNative *native = allocateNative();
  native->arity = arity;
  native->fun = fun;
  native->name = name;
  internObject((Obj **)&native);
  return native;
}

static double timespecDiff(struct timespec *start, struct timespec *end) {
  return (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1e9;
}

static struct timespec startTime;

static double elapsed() {
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  return timespecDiff(&startTime, &now);
}

AT_VM_BOOT(setStartTime) {
  clock_gettime(CLOCK_MONOTONIC, &startTime);
  return NULL;
}

NATIVE_FUNCTION(clock, 0) { return number((double)clock() / CLOCKS_PER_SEC); }
NATIVE_FUNCTION(time, 0) { return number((double)time(NULL)); }
NATIVE_FUNCTION(elapsed, 0) { return number(elapsed()); }
NATIVE_FUNCTION(hash, 1) { return OBJ_VAL(stringf("%#x", valueHash(args[0]))); }
NATIVE_FUNCTION(pp, 1) { return argc > 1 ? pp(t(argc, args)) : pp(args[0]); }

NATIVE_METHOD(Any, class, 0) { return classOf(this); }
NATIVE_METHOD(Any, inspect, 0) { return inspect(this); }
NATIVE_METHOD(Any, object_id, 0) { return NUMBER_VAL((u64)AS_OBJ(this)); }
NATIVE_METHOD_NAMED(Any, eql, "==", 1) {
  return BOOL_VAL(valuesEqual(this, args[0]));
}
NATIVE_METHOD(Any, hash, 0) { return OBJ_VAL(stringf("%#x", valueHash(this))); }

NATIVE_METHOD(Object, etype, 0) {
  const ecs_type_t *type = ecs_get_type(vm.world, asObject(this)->eid);
  char *type_str = ecs_type_str(vm.world, type);
  return OBJ_VAL(takeString(type_str, -1));
}
NATIVE_METHOD_NAMED(Number, spaceship, "<=>", 1) {
  return asNumber(this) - asNumber(args[0]);
}
NATIVE_METHOD_NAMED(Number, star, "*", 1) {
  return NUMBER_VAL(asNumber(this) * asNumber(args[0]));
}
NATIVE_METHOD(Number, string, 0) {
  return OBJ_VAL(stringf("%g", asNumber(this)));
}

static void markNative(Obj *obj) {
  ObjNative *native = (ObjNative *)obj;
  markObject((Obj *)native->name);
}

static int inspectNative(Obj *obj, FILE *io) {
  ObjNative *native = (ObjNative *)obj;
  return fprintf(io,
                 FG_MAGENTA "<native %s" FG_DEFAULT "/" FG_MAGENTA
                            "%d>" FG_DEFAULT,
                 native->name->chars, native->arity) -
         FG_SIZE * 4;
}

static int nativeLength(Obj *obj) {
  ObjNative *native = (ObjNative *)obj;
  return native->arity;
}

static InterpretResult callNative(Obj *obj, int argc) {
  ObjNative *native = (ObjNative *)obj;

  if (argc < native->arity)
    return runtimeError("Expected %d arguments but got %d.", native->arity,
                        argc);

  if (vm.frameCount == FRAMES_MAX) return runtimeError("Call stack overflow.");

  CallFrame *frame = newFrame(obj, argc + 1);
  if (!frame) return runtimeError("Call stack overflow.");

  return INTERPRET_OK;
}

REGISTER_OBJECT_DEF(Native);
const ObjDef Native = {
    .className = "Native",
    .size = sizeof(ObjNative),
    .hash = hashObjectDefault,
    .mark = markNative,
    .call = callNative,
    .inspect = inspectNative,
    .length = nativeLength,
};
