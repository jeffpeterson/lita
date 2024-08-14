#ifndef lita_entity_h
#define lita_entity_h

#include "common.h"
#include "object.h"
#include "table.h"

#define AS_ENTITY(val) ((ObjEntity *)AS_OBJ(val))
#define is_entity(val) is_obj_def(val, &Entity)
#define new_entity() ((ObjEntity *)new_object(&Entity))

typedef struct ObjEntity {
  Obj obj;
  Table *values;
} ObjEntity;

const ObjDef Entity;

ObjEntity *as_entity(Value val);
ObjEntity *copy_entity(Value *values, uint8_t length);
ObjEntity *take_entity(Value *values, uint8_t length);

let ent(int len, let *vals);
let ent2(let a, let b);
let ent3(let a, let b, let c);
let ent4(let a, let b, let c, let d);
let ent5(let a, let b, let c, let d, let e);
let ent6(let a, let b, let c, let d, let e, let f);
let ent7(let a, let b, let c, let d, let e, let f, let g);

#endif
