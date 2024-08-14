#include <assert.h>

#include "iterator.h"
#include "memory.h"

ObjIterator *as_iterator(Value val) {
  assert(is_iterator(val));
  return AS_ITERATOR(val);
}

static void free_iterator(Obj *obj) {
  ObjIterator *iter = (ObjIterator *)obj;
  iter->done = true;
  iter->size = 0;
  iter->current = NULL;
}

static void mark_iterator(Obj *obj) {
  ObjIterator *iter = (ObjIterator *)obj;
  markValue(iter->state);
  for (int i = 0; i < iter->size; i++) markValue(iter->current[i]);
}

static int iterator_length(Obj *obj) { return ((ObjIterator *)obj)->size; }

void iterator_init(Obj *obj) {
  ObjIterator *iter = (ObjIterator *)obj;
  iter->state = NIL_VAL;
  iter->next = NULL;
  iter->current = NULL;
  iter->size = 0;
  iter->index = 0;
  iter->total = -1;
  iter->done = true;
}

bool iterate_next(ObjIterator *iter) {
  if (iter->done) return false;

  if (++iter->index > 0) {
    if (iter->total < 0 || iter->index < iter->total) iter->next(iter);
    else iter->done = true;
  }

  return !iter->done;
}

REGISTER_OBJECT_DEF(Iterator);
const ObjDef Iterator = {
    .class_name = "Iterator",
    .size = sizeof(ObjIterator),
    .init = iterator_init,
    .free = free_iterator,
    .mark = mark_iterator,
    .length = iterator_length,
};
