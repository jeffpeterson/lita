#include "io.h"
#include "native.h"

Value io(FILE *fp, Ownership ownership) { return obj(makeIO(fp, ownership)); }

ObjIO *makeIO(FILE *fp, Ownership ownership) {
  ObjIO *io = allocateIO();
  io->fp = fp;
  io->ownership = ownership;
  internObject((Obj **)&io);
  return io;
}

static int inspectIO(Obj *obj, FILE *fp) {
  ObjIO *io = (ObjIO *)obj;
  return fprintf(fp, "<IO %p>", io->fp);
}

static void freeIO(Obj *obj) {
  ObjIO *io = (ObjIO *)obj;
  if (io->ownership) fclose(io->fp);
}

NATIVE_METHOD(IO, write, 1) {
  ObjIO *io = asIO(this);
  ObjString *str = asString(args[0]);
  fwrite(str->chars, sizeof(char), str->length, io->fp);
  return this;
}

REGISTER_OBJECT_DEF(IO);
const ObjDef IO = {
    .className = "IO",
    .size = sizeof(ObjIO),
    .hash = hashObjectDefault,
    .free = freeIO,
    .inspect = inspectIO,
};
