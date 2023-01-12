#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"
#include "memory.h"
#include "table.h"
#include "vm.h"

#if defined(DEBUG_LOG_GC) || defined(DEBUG_LOG_MEM)
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
#ifdef DEBUG_STRESS_GC
    collectGarbage();
#endif
    if (vm.bytesAllocated > vm.nextGC) collectGarbage();
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

#ifdef DEBUG_LOG_GC
  fprintf(stderr, "%p mark gray ", (void *)obj);
  fprintValue(stderr, OBJ_VAL(obj));
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
  if (IS_OBJ(value)) markObject(AS_OBJ(value));
}

static void markArray(ValueArray *array) {
  for (int i = 0; i < array->count; i++) {
    markValue(array->values[i]);
  }
}

static void blackenObject(Obj *obj) {
#ifdef DEBUG_LOG_GC
  fprintf(stderr, "%p mark black ", (void *)obj);
  fprintValue(stderr, OBJ_VAL(obj));
  fprintf(stderr, "\n");
#endif

  switch (obj->type) {
  case OBJ_ARRAY: {
    ObjArray *arr = (ObjArray *)obj;
    for (int i = 0; i < arr->length; i++) markValue(arr->values[i]);
    break;
  }
  case OBJ_BOUND: {
    ObjBound *bound = (ObjBound *)obj;
    markValue(bound->receiver);
    markValue(bound->method);
    break;
  }

  case OBJ_CLASS: {
    ObjClass *klass = (ObjClass *)obj;
    markObject((Obj *)klass->name);
    markObject((Obj *)klass->parent);
    markTable(&klass->methods);
    break;
  }

  case OBJ_CLOSURE: {
    ObjClosure *closure = (ObjClosure *)obj;
    markObject((Obj *)closure->fun);
    for (int i = 0; i < closure->upvalueCount; i++) {
      markObject((Obj *)closure->upvalues[i]);
    }
    break;
  }

  case OBJ_ERR: {
    ObjErr *err = (ObjErr *)obj;
    markObject((Obj *)err->msg);
    break;
  }

  case OBJ_FUN: {
    ObjFun *fun = (ObjFun *)obj;
    markObject((Obj *)fun->name);
    markArray(&fun->chunk.constants);
    break;
  }

  case OBJ_INSTANCE: {
    ObjInstance *inst = (ObjInstance *)obj;
    markObject((Obj *)inst->klass);
    markTable(&inst->fields);
    break;
  }

  case OBJ_NATIVE: {
    ObjNative *native = (ObjNative *)obj;
    markObject((Obj *)native->name);
    break;
  }

  case OBJ_RANGE: {
    ObjRange *range = (ObjRange *)obj;
    markValue(range->start);
    markValue(range->end);
    break;
  }

  case OBJ_TUPLE: {
    ObjTuple *tuple = (ObjTuple *)obj;
    for (int i = 0; i < tuple->length; i++) markValue(tuple->values[i]);
    break;
  }

  case OBJ_UPVALUE: markValue(((ObjUpvalue *)obj)->closed); break;

  case OBJ_STRING: break;
  }
}

static void freeObject(Obj *obj) {
#ifdef DEBUG_LOG_MEM
  fprintf(stderr, "%p free ", (void *)obj);
  fprintObjType(stderr, obj->type);
  fprintf(stderr, " ");
  fprintObject(stderr, obj);
  fprintf(stderr, "\n");
#endif

  switch (obj->type) {
  case OBJ_ARRAY: {
    ObjArray *arr = (ObjArray *)obj;
    FREE_ARRAY(Value, arr->values, arr->capacity);
    FREE(ObjArray, obj);
    break;
  }
  case OBJ_BOUND: FREE(ObjBound, obj); break;

  case OBJ_CLASS: {
    ObjClass *klass = (ObjClass *)obj;
    freeTable(&klass->methods);
    FREE(ObjClass, obj);
    break;
  }

  case OBJ_CLOSURE: {
    ObjClosure *closure = (ObjClosure *)obj;
    FREE_ARRAY(ObjUpvalue *, closure->upvalues, closure->upvalueCount);
    FREE(ObjClosure, obj);
    break;
  }

  case OBJ_ERR: FREE(ObjErr, obj); break;

  case OBJ_FUN: {
    ObjFun *fun = (ObjFun *)obj;
    freeChunk(&fun->chunk);
    FREE(ObjFun, obj);
    break;
  }

  case OBJ_INSTANCE: {
    ObjInstance *inst = (ObjInstance *)obj;
    freeTable(&inst->fields);
    FREE(ObjInstance, obj);
    break;
  }

  case OBJ_NATIVE: FREE(ObjNative, obj); break;

  case OBJ_RANGE: FREE(ObjRange, obj); break;

  case OBJ_STRING: {
    ObjString *string = (ObjString *)obj;
    FREE_ARRAY(char, string->chars, string->length + 1);
    FREE(ObjString, obj);
    break;
  }
  case OBJ_TUPLE: {
    ObjTuple *tuple = (ObjTuple *)obj;
    FREE_ARRAY(Value, tuple->values, tuple->length);
    FREE(ObjTuple, obj);
    break;
  }

  case OBJ_UPVALUE: FREE(ObjUpvalue, obj); break;
  }
}

static void markRoots() {
  for (Value *slot = vm.stack; slot < vm.stackHigh; slot++) {
    markValue(*slot);
  }

  for (int i = 0; i < vm.frameCount; i++) {
    markObject((Obj *)vm.frames[i].closure);
  }

  for (ObjUpvalue *upvalue = vm.openUpvalues; upvalue != NULL;
       upvalue = upvalue->next) {
    markObject((Obj *)upvalue);
  }

  markTable(&vm.globals);
  markTable(&vm.keep);
  markCompilerRoots();
  markObject((Obj *)vm.str.init);
}

static void traceReferences() {
  while (vm.grayCount > 0) {
    Obj *obj = vm.grayStack[--vm.grayCount];
    blackenObject(obj);
  }
}

static void sweep() {
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
    if (prev != NULL) {
      prev->next = obj;
    } else {
      vm.objects = obj;
    }

#ifdef DEBUG_LOG_GC
    fprintf(stderr, "%p free ", (void *)unreached);
    fprintObjType(stderr, unreached->type);
    fprintf(stderr, " ");
    fprintObject(stderr, unreached);
    fprintf(stderr, "\n");
#endif

    freeObject(unreached);
  }
}

void collectGarbage() {
#ifdef DEBUG_LOG_GC
  size_t before = vm.bytesAllocated;
  fprintf(stderr, "-- gc begin\n");
  fprintf(stderr, "-- mark roots\n");
#endif
  markRoots();

#ifdef DEBUG_LOG_GC
  fprintf(stderr, "-- trace references\n");
#endif
  traceReferences();

#ifdef DEBUG_LOG_GC
  fprintf(stderr, "-- remove white interned values\n");
#endif
  tableRemoveWhite(&vm.interned);

#ifdef DEBUG_LOG_GC
  fprintf(stderr, "-- sweep\n");
#endif
  sweep();

  vm.nextGC = vm.bytesAllocated * GC_HEAP_GROW_FACTOR;

#ifdef DEBUG_LOG_GC
  fprintf(stderr, "-- gc end\n");
  fprintf(stderr, "   collected %zu bytes (from %zu to %zu) next at %zu\n",
          before - vm.bytesAllocated, before, vm.bytesAllocated, vm.nextGC);
#endif
}

void freeObjects() {
  Obj *object = vm.objects;
  while (object != NULL) {
    Obj *next = object->next;
    freeObject(object);
    object = next;
  }

  free(vm.grayStack);
}
