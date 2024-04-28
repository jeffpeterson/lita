#include <assert.h>

#include "io.h"
#include "lib.h"
#include "memory.h"
#include "vm.h"

/** Safely convert val to io pointer. */
ObjIO *as_io(let x) {
  assert(is_io(x));
  return AS_IO(x);
}

ObjIO *make_io(FILE *fp, Ownership ownership) {
  ObjIO *io = ALLOCATE_OBJ(ObjIO, OBJ_CUSTOM);
  io->obj.def = &io_def;
  io->fp = fp;
  io->ownership = ownership;
  io->obj.hash = hashBytes((char *)&io->fp, sizeof(Value) * 2);
  return io;
}

let io(FILE *fp, Ownership ownership) { return obj(make_io(fp, ownership)); }

const char *io_bytes(Obj *obj, int length) {
  if (length != sizeof(FILE *)) return NULL;
  ObjIO *io = (ObjIO *)obj;
  return (char *)&io->fp;
}

static int inspect_io(Obj *obj, FILE *fp) {
  ObjIO *io = (ObjIO *)obj;
  return fprintf(fp, "<IO %p>", io->fp);
}

static void free_io(Obj *obj) {
  ObjIO *io = (ObjIO *)obj;
  if (io->ownership) fclose(io->fp);
}

static let IO_write(let this, int argc, let *args) {
  ObjIO *io = as_io(this);
  ObjString *str = as_string(to_string(args[0]));
  fwrite(str->chars, sizeof(char), str->length, io->fp);
  return this;
}

static void io_natives(let IO) { method(IO, fn("write", 1, IO_write)); }

const ObjDef io_def = {
    .class_name = "IO",
    .size = sizeof(ObjIO),
    .free = free_io,
    .interned = true,
    .bytes = io_bytes,
    .inspect = inspect_io,
    .natives = io_natives,
};
