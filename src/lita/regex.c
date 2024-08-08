#include <assert.h>

#include "lib.h"
#include "memory.h"
#include "regex.h"
#include "vm.h"

/** Safely convert val to regex pointer. */
ObjRegex *as_regex(Value x) {
  assert(is_regex(x));
  return AS_REGEX(x);
}

ObjRegex *make_regex(ObjString *source) {
  ObjRegex *regex = ALLOCATE_OBJ(ObjRegex, OBJ_CUSTOM);
  regex->obj.def = &Regex;
  regex->source = source;
  regex->re = pcre2_compile((PCRE2_SPTR)source->chars, source->length, 0,
                            &regex->error_code, &regex->error_offset,
                            NULL); // TODO: pcre2_compile() options

  if (regex->re == NULL) {
    pcre2_get_error_message(regex->error_code, regex->error_message,
                            sizeof(regex->error_message));
    crash((char *)regex->error_message);
  }
  return regex;
}

static int regex_length(Obj *obj) {
  ObjRegex *regex = (ObjRegex *)obj;
  return regex->source->length;
}

static void mark_regex(Obj *obj) {
  ObjRegex *regex = (ObjRegex *)obj;
  markObject((Obj *)regex->source);
}

static int inspect_regex(Obj *obj, FILE *io) {
  ObjRegex *regex = (ObjRegex *)obj;
  return fprintf(io, "/") + fputs(escape_string(regex->source)->chars, io) +
         fprintf(io, "/");
}

// ObjFun *regex_lita();

static void regex_natives(let Regex) {
  // runFun(regex_lita());
}

const ObjDef Regex = {
    .class_name = "Regex",
    .size = sizeof(ObjRegex),
    .mark = mark_regex,
    .inspect = inspect_regex,
    // .dump = dump_regex,
    .length = regex_length,
    .natives = regex_natives,
};

Value regex(const char *source) { return obj(make_regex(new_string(source))); }
