#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"
#include "memory.h"
#include "table.h"
#include "vm.h"

#if DEBUG_LOG_GC || DEBUG_LOG_MEM
#include "debug.h"
#include <stdio.h>
#endif

#define GC_HEAP_GROW_FACTOR 2

Value keep(Value v) {
  tableInc(&vm.keep, v, 1);
  return v;
}

Value unkeep(Value v) {
  if (tableInc(&vm.keep, v, -1) == 0) tableDelete(&vm.keep, v);
  return v;
}

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
  vm.bytesAllocated += newSize - oldSize;

  // More sophisticated collectors might run on a separate thread or be
  // interleaved periodically during program execution—often at function
  // call boundaries or when a backward jump occurs.
  if (newSize > oldSize) {
    if (config.stress_gc || vm.bytesAllocated > vm.nextGC) request_gc();
  }

  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void *result = realloc(pointer, newSize);

  if (result == NULL) {
    printf("realloc() failed. Probably out of memory");
    exit(1);
  }
  return result;
}

void *cloneMemory(void *src, usize size) {
  void *dst = ALLOCATE(u8, size);
  memcpy(dst, src, size);
  return dst;
}

void markObject(Obj *obj) {
  if (obj == NULL) return;
  if (obj->isMarked) return;

#if DEBUG_LOG_GC
  fprintf(stderr, "%p mark gray ", obj);
  inspectObject(stderr, obj, 1);
  fprintf(stderr, "\n");
#endif

  obj->isMarked = true;

  // Grow the grayStack if needed.
  if (vm.grayCapacity < vm.grayCount + 1) {
    vm.grayCapacity = GROW_CAPACITY(vm.grayCapacity);
    vm.grayStack =
        (Obj **)realloc(vm.grayStack, sizeof(Obj *) * vm.grayCapacity);

    // We could not grow the grayStack.
    if (vm.grayStack == NULL) {
      // > To be more robust, we can allocate a “rainy day fund” block of
      // > memory when we start the VM. If the gray stack allocation fails,
      // > we free the rainy day block and try again. That may give us enough
      // > wiggle room on the heap to create the gray stack, finish the GC,
      // > and free up more memory.
      // Todo: Handle this with more grace.
      exit(1);
    }
  }

  vm.grayStack[vm.grayCount++] = obj;
}

void markValue(Value value) {
  if (isObject(value)) markObject(AS_OBJ(value));
}

void markValueArray(ValueArray *array) {
  for (int i = 0; i < array->count; i++) {
    markValue(array->values[i]);
  }
}

static void blackenObject(Obj *obj) {
#if DEBUG_LOG_GC
  fprintf(stderr, "%p mark black ", obj);
  inspectObject(stderr, obj, 1);
  fprintf(stderr, "\n");
#endif

  markObject((Obj *)obj->klass);
  markTable(&obj->fields);

  if (obj->def->mark) return obj->def->mark(obj);
}

void freeObject(Obj *obj) {
  assert(!obj->next);
  assert(obj->hash);

#if DEBUG_LOG_MEM
  fprintf(stderr, "%p free %s\n", obj, obj->def->className);
#endif

  freeTable(&obj->fields);
  if (obj->def->free) obj->def->free(obj);
  reallocate(obj, obj->def->size, 0);
}

static void markRoots() {
  for (Value *slot = vm.stack; slot < vm.stackHigh; slot++) markValue(*slot);
  for (int i = 0; i < vm.frameCount; i++) markObject((Obj *)vm.frames[i].obj);

  for (ObjUpvalue *upvalue = vm.openUpvalues; upvalue != NULL;
       upvalue = upvalue->next) {
    markObject((Obj *)upvalue);
  }

  markTable(&vm.globals);
  markTable(&vm.keep);
  markCompilerRoots();
}

static void traceReferences() {
  while (vm.grayCount > 0) {
    Obj *obj = vm.grayStack[--vm.grayCount];
    blackenObject(obj);
  }
}

static void sweep() {
  vm.stackSinceGC = vm.stackHigh;

  Obj *prev = NULL;
  Obj *obj = vm.objects;

  while (obj != NULL) {
    if (obj->isMarked) {
      // Object was reached during "mark" stage.

      // Reset marked status for next GC.
      obj->isMarked = false;
      prev = obj;
      obj = obj->next;
      continue;
    }

    // Collect the unreachable object.
    Obj *unreached = obj;
    obj = obj->next;
    if (prev) prev->next = obj;
    else vm.objects = obj;
    unreached->next = NULL;

#if DEBUG_LOG_GC
    fprintf(stderr, "sweep %p %s %zub\n", unreached, unreached->def->className,
            unreached->def->size);
    // inspectObject(stderr, unreached, 1);
    // fprintf(stderr, "\n");
#endif

    tableDelete(&vm.interned, OBJ_VAL(unreached));
    freeObject(unreached);
  }
}

void request_gc() {
  vm.gc_requested = true;

#if DEBUG_LOG_GC
  fprintf(stderr, "-- gc requested\n");
#endif
}

int collect_garbage() {
  usize before = vm.bytesAllocated;
  vm.gc_requested = false;

#if DEBUG_LOG_GC
  fprintf(stderr, "-- gc begin\n");
  fprintf(stderr, "-- mark roots\n");
#endif

  markRoots();

#if DEBUG_LOG_GC
  fprintf(stderr, "-- trace references\n");
#endif

  traceReferences();

#if DEBUG_LOG_GC
  fprintf(stderr, "-- remove white interned values\n");
#endif

#if DEBUG_LOG_GC
  fprintf(stderr, "-- sweep\n");
#endif

  // We must not allocate during garbage collection.
  assert(before >= vm.bytesAllocated);

  sweep();

  vm.nextGC = vm.bytesAllocated * GC_HEAP_GROW_FACTOR;
  int collected = before - vm.bytesAllocated;

#if DEBUG_LOG_GC
  fprintf(stderr, "-- gc end\n");
  fprintf(stderr, "-- collected %i bytes (from %zu to %zu) next at %zu\n",
          collected, before, vm.bytesAllocated, vm.nextGC);
#endif

  return collected;
}

void freeObjects() {
  Obj *object = vm.objects;
  while (object != NULL) {
    Obj *next = object->next;
    object->next = NULL;
    freeObject(object);
    object = next;
  }

  free(vm.grayStack);
}
