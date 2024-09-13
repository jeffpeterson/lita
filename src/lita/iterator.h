#ifndef lita_iterator_h
#define lita_iterator_h

#include "common.h"
#include "object.h"

#define allocateIterator() ALLOCATE_OBJ(Iterator)
#define isIterator(val) isObjDef(val, &Iterator)
#define asIterator(val) as(Iterator, val)

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

const ObjDef Iterator;

bool iterateNext(ObjIterator *iter);

#endif
