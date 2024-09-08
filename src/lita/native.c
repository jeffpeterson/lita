#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#include "array.h"
#include "debug.h"
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

NATIVE_FUNCTION(shell, 1) {
  char *str = NULL;
  usize len = 0;
  FILE *io = open_memstream(&str, &len);

  fprintf(io, "%s", asChars(args[0]));
  for (int i = 1; i < argc; i++)
    fprintf(io, " %s", escape_string(as_string(args[i]))->chars);

  fclose(io);
  return number(system(take_string(str, len)->chars));
}
NATIVE_FUNCTION(clock, 0) { return number((double)clock() / CLOCKS_PER_SEC); }
NATIVE_FUNCTION(time, 0) { return number((double)time(NULL)); }
NATIVE_FUNCTION(elapsed, 0) { return number(elapsed()); }
NATIVE_FUNCTION(hash, 1) {
  return OBJ_VAL(stringf("%#x", hash_value(args[0])));
}
NATIVE_FUNCTION(pp, 1) { return argc > 1 ? pp(t(argc, args)) : pp(args[0]); }
NATIVE_FUNCTION(read, 0) { return read(argc ? args[0] : string("/dev/stdin")); }
NATIVE_FUNCTION(mkdir, 1) { return mkdir(as_string(args[0])->chars, 0777); }
NATIVE_FUNCTION(write, 1) {
  let path = argc == 1 ? string("/dev/stdout") : args[0];
  return write(path, args[argc - 1]);
}
NATIVE_FUNCTION(append, 1) {
  let path = argc == 1 ? string("/dev/stdout") : args[0];
  return append(path, args[argc - 1]);
}
NATIVE_FUNCTION(repl, 0) {
  repl();
  return nil;
}

NATIVE_METHOD(Any, self, 0) { return this; }
NATIVE_METHOD(Any, class, 0) { return classOf(this); }
NATIVE_METHOD(Any, inspect, 0) { return inspect(this); }
NATIVE_METHOD(Any, object_id, 0) { return NUMBER_VAL((u64)AS_OBJ(this)); }
NATIVE_METHOD(Any, string, 0) { return inspect(this); }
NATIVE_METHOD_NAMED(Any, eql, "==", 1) {
  return BOOL_VAL(valuesEqual(this, args[0]));
}
NATIVE_METHOD_NAMED(Any, not_eql, "!=", 1) {
  return BOOL_VAL(!valuesEqual(this, args[0]));
}
NATIVE_METHOD(Any, hash, 0) {
  return OBJ_VAL(stringf("%#x", hash_value(this)));
}

NATIVE_METHOD(Object, etype, 0) {
  const ecs_type_t *type = ecs_get_type(vm.world, as_obj(this)->eid);
  char *type_str = ecs_type_str(vm.world, type);
  return OBJ_VAL(take_string(type_str, -1));
}

NATIVE_METHOD_NAMED(Number, gt, ">", 1) {
  return BOOL_VAL(as_num(this) > as_num(args[0]));
}
NATIVE_METHOD_NAMED(Number, gte, ">=", 1) {
  return BOOL_VAL(as_num(this) >= as_num(args[0]));
}
NATIVE_METHOD_NAMED(Number, lt, "<", 1) {
  return BOOL_VAL(as_num(this) < as_num(args[0]));
}
NATIVE_METHOD_NAMED(Number, lte, "<=", 1) {
  return BOOL_VAL(as_num(this) <= as_num(args[0]));
}
NATIVE_METHOD_NAMED(Number, star, "*", 1) {
  return NUMBER_VAL(as_num(this) * as_num(args[0]));
}
NATIVE_METHOD(Number, string, 0) {
  return OBJ_VAL(stringf("%g", as_num(this)));
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

REGISTER_OBJECT_DEF(Native);
ObjDef Native = {
    .class_name = "Native",
    .size = sizeof(ObjNative),
    .mark = markNative,
    .inspect = inspectNative,
    .length = nativeLength,
};
