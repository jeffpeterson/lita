#ifndef lita_closure_h
#define lita_closure_h

#include "common.h"
#include "function.h"
#include "object.h"
#include "upvalue.h"
#include "value.h"

#define isClosure(val) isObjDef(val, &Closure)
#define asClosure(val) as(Closure, val)
#define allocateClosure() ALLOCATE_OBJ(Closure)

/**
 * upvalueCount is duplicated from ObjFunction because we need it during GC and
 * the ObjFunction might get GC'd first.
 */
typedef struct ObjClosure {
  Obj obj;
  ObjFunction *function; /** Function being closed-over. */
  int upvalueCount;      /** Number of closed-over upvalues. */
  ObjUpvalue **upvalues; /** Array of upvalue pointers being closed-over. */
} ObjClosure;

extern const ObjDef Closure;

ObjClosure *newClosure(ObjFunction *function);

#endif
