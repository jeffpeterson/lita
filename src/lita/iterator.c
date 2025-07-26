#include "iterator.h"
#include "memory.h"

bool iterateNext(ObjIterator *iter) {
  if (iter->done) return false;

  if (++iter->index > 0) {
    if (iter->length < 0 || iter->index < iter->length) iter->next(iter);
    else iter->done = true;
  }

  return !iter->done;
}

static void freeIterator(Obj *obj) {
  ObjIterator *iter = (ObjIterator *)obj;
  iter->done = true;
  iter->size = 0;
  iter->current = NULL;
}

static void markIterator(Obj *obj) {
  ObjIterator *iter = (ObjIterator *)obj;
  markValue(iter->state);
  for (int i = 0; i < iter->size; i++) markValue(iter->current[i]);
}

static int iteratorLength(Obj *obj) { return ((ObjIterator *)obj)->size; }

static void allocIterator(Obj *obj) {
  ObjIterator *iter = (ObjIterator *)obj;
  iter->state = NIL_VAL;
  iter->next = NULL;
  iter->current = NULL;
  iter->size = 0;
  iter->index = 0;
  iter->length = -1;
  iter->done = true;
}

REGISTER_OBJECT_DEF(Iterator);
const ObjDef Iterator = {
    .className = "Iterator",
    .size = sizeof(ObjIterator),
    .alloc = allocIterator,
    .free = freeIterator,
    .mark = markIterator,
    .length = iteratorLength,
};
