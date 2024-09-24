#ifndef lita_bound_h
#define lita_bound_h

#include "common.h"
#include "object.h"
#include "value.h"

#define isBound(val) isObjDef(val, &Bound)
#define asBound(val) as(Bound, val)
#define allocateBound() ALLOCATE_OBJ(Bound)

/** A closure bound to a receiver.  */
typedef struct ObjBound {
  Obj obj;
  Value receiver; /** Bound `this` value. */
  Value method;   /** Method being bound. */
} ObjBound;

extern const ObjDef Bound;

ObjBound *newBound(Value receiver, Value method);
Value bound(Value receiver, Value method);

#endif
