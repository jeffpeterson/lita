#ifndef lita_upvalue_h
#define lita_upvalue_h

#include "common.h"
#include "object.h"
#include "value.h"

#define allocateUpvalue() ALLOCATE_OBJ(Upvalue)
#define isUpvalue(val) is_obj_def(val, &Upvalue)
#define asUpvalue(val) as(Upvalue, val)

/**
 * Tracks a closed-over variable by keeping a pointer to its
 * location in memory.
 *
 * "Open" upvalues point to values on the VM's stack.
 *
 * Todo: rename to ObjRef?
 */
typedef struct ObjUpvalue {
  Obj obj;
  Value closed;    /** Stores this upvalue's Value once it has been "closed". */
  Value *location; /** Pointer to this upvalue's Value. */
  struct ObjUpvalue *next; /** Linked list of all upvalues tracked by VM. */
} ObjUpvalue;

ObjDef Upvalue;

ObjUpvalue *newUpvalue(Value *slot);

#endif
