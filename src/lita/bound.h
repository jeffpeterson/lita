#ifndef lita_bound_h
#define lita_bound_h

#include "common.h"
#include "object.h"
#include "value.h"

#define AS_BOUND(val) ((ObjBound *)AS_OBJ(val))
#define isBound(val) is_obj_def(val, &Bound)
#define allocateBound() ((ObjBound *)new_object(&Bound))

/** A closure bound to a receiver.  */
typedef struct ObjBound {
  Obj obj;
  let receiver; /** Bound `this` value. */
  let method;   /** Method being bound. */
} ObjBound;

ObjDef Bound;

ObjBound *asBound(let val);
ObjBound *newBound(let receiver, let method);
let bound(let receiver, let method);

#endif
