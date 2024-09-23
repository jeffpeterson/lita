#include "source_location.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "term.h"

Value sourceLocation(const char *path, int line, int column) {
  return obj(newSourceLocation(newString(path), line, column));
}

ObjSourceLocation *newSourceLocation(ObjString *path, int line, int column) {
  ObjSourceLocation *sourceLocation = allocateSourceLocation();
  sourceLocation->path = path;
  sourceLocation->line = line;
  sourceLocation->column = column;
  internObject((Obj **)&sourceLocation);
  return sourceLocation;
}

static void markSourceLocation(Obj *obj) {
  ObjSourceLocation *sourceLocation = (ObjSourceLocation *)obj;
  markObject((Obj *)sourceLocation->path);
}

static int inspectSourceLocation(Obj *obj, FILE *io) {
  ObjSourceLocation *sourceLocation = (ObjSourceLocation *)obj;
  return fprintf(io, UNDERLINE "%s:%d:%d" NO_UNDERLINE,
                 stringChars(sourceLocation->path), sourceLocation->line,
                 sourceLocation->column) -
         sizeof(UNDERLINE) - sizeof(NO_UNDERLINE);
}

static int dumpSourceLocation(Obj *obj, FILE *io) {
  ObjSourceLocation *sourceLocation = (ObjSourceLocation *)obj;
  return fprintf(io, "sourceLocation(%s, %d, %d)",
                 stringChars(escapeString(sourceLocation->path)),
                 sourceLocation->line, sourceLocation->column);
}

NATIVE_GETTER(SourceLocation, path, OBJ_VAL);
NATIVE_GETTER(SourceLocation, line, NUMBER_VAL);
NATIVE_GETTER(SourceLocation, column, NUMBER_VAL);
DEFINE_OBJECT_TYPE(SourceLocation, .mark = markSourceLocation,
                   .hash = hashObjectDefault, .inspect = inspectSourceLocation,
                   .dump = dumpSourceLocation);
