#ifndef lita_iterator_h
#define lita_iterator_h

#include "common.h"
#include "object.h"

#define AS_ITERATOR(val) ((ObjIterator *)AS_OBJ(val))
#define is_iterator(val) is_obj_def(val, &Iterator)
#define new_iterator() ((ObjIterator *)new_object(&Iterator))

typedef struct ObjIterator {
  Obj obj;

  Value state; /** Internal state for the iterator. */
  void (*next)(struct ObjIterator *iter); /** Advance the iterator. */

  Value *current; /** Current iterated set of values. */
  int size;       /** Size of the current set of values. */
  int index;      /** Which iteration is this? Starting at 0 */
  int total;      /** Total number of iterations. -1 if unknown. */
  bool done;      /** True if the iteration is ended. */
} ObjIterator;

extern const ObjDef Iterator;

ObjIterator *as_iterator(Value val);

bool iterate_next(ObjIterator *iter);

#endif
