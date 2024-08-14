#ifndef lita_io_h
#define lita_io_h

#include "common.h"
#include "object.h"
#include "value.h"

typedef struct ObjIO {
  Obj obj;
  FILE *fp;
  Ownership ownership;
} ObjIO;

#define AS_IO(val) ((ObjIO *)AS_OBJ(val))
#define is_io(val) is_obj_def(val, &IO)

ObjIO *make_io(FILE *fp, Ownership ownership);
Value io(FILE *fp, Ownership ownership);

const ObjDef IO;

#endif
