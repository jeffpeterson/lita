#include <assert.h>

#include "example.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "vm.h"

ObjExample *as_example(Value x) {
  assert(is_example(x));
  return AS_EXAMPLE(x);
}

Value example(const char *comment) {
  return obj(new_example(new_string(comment)));
}

ObjExample *new_example(ObjString *comment) {
  ObjExample *example = allocate_example();
  example->comment = comment;
  return example;
}

static int example_length(Obj *obj) {
  ObjExample *example = (ObjExample *)obj;
  return example->comment->length;
}

static void mark_example(Obj *obj) {
  ObjExample *example = (ObjExample *)obj;
  markObject((Obj *)example->comment);
}

static int inspect_example(Obj *obj, FILE *io) {
  ObjExample *example = (ObjExample *)obj;
  return fstring_format(io, "Example({})", OBJ_VAL(example->comment));
}

NATIVE_GETTER(Example, comment, OBJ_VAL);

REGISTER_OBJECT_DEF(Example);
ObjDef Example = {
    .class_name = "Example",
    .size = sizeof(ObjExample),
    .mark = mark_example,
    .inspect = inspect_example,
    .length = example_length,
};
