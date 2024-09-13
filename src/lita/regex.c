#include <assert.h>

#include "lib.h"
#include "memory.h"
#include "native.h"
#include "regex.h"
#include "vm.h"

Value regex(const char *source) { return obj(makeRegex(newString(source))); }
static u32 defaultOptions = PCRE2_UTF | PCRE2_UCP;

ObjRegex *makeRegex(ObjString *source) {
  // Obj *obj = new_instance(global_class("Regex"));
  // ecs_set_pair(vm.world, obj->eid, RegexSource, {source});

  ObjRegex *regex = allocateRegex();
  u32 options = defaultOptions;
  regex->obj.def = &Regex;
  regex->source = source;
  regex->re = pcre2_compile((PCRE2_SPTR)source->chars, source->length, options,
                            &regex->error_code, &regex->error_offset,
                            NULL); // TODO: pcre2_compile() options

  if (regex->re == NULL) {
    pcre2_get_error_message(regex->error_code, regex->error_message,
                            sizeof(regex->error_message));
    crash("pcre2_compile: %s", (char *)regex->error_message);
  }
  return regex;
}

static int regexLength(Obj *obj) {
  ObjRegex *regex = (ObjRegex *)obj;
  return regex->source->length;
}

static void markRegex(Obj *obj) {
  ObjRegex *regex = (ObjRegex *)obj;
  markObject((Obj *)regex->source);
}

static void freeRegex(Obj *obj) {
  ObjRegex *regex = (ObjRegex *)obj;
  pcre2_code_free(regex->re);
}

static int inspectRegex(Obj *obj, FILE *io) {
  ObjRegex *regex = (ObjRegex *)obj;
  return fprintf(io, "`") + fputs(regex->source->chars, io) + fprintf(io, "`");
}

static int dumpRegex(Obj *obj, FILE *io) {
  ObjRegex *regex = (ObjRegex *)obj;
  ObjString *source = escapeString(regex->source);
  return fprintf(io, "regex(%.*s)", source->length, source->chars);
}

ObjString *replaceRegex(ObjString *subject, ObjRegex *regex,
                        ObjString *replacement) {
  u32 options = PCRE2_SUBSTITUTE_GLOBAL | PCRE2_SUBSTITUTE_EXTENDED |
                PCRE2_SUBSTITUTE_OVERFLOW_LENGTH;
  Buffer output = newBuffer(subject->length * 2);
  output.count = output.capacity;

  int result;

substitute:
  result =
      pcre2_substitute(regex->re, (PCRE2_SPTR)subject->chars, subject->length,
                       0, options, NULL, NULL, (PCRE2_SPTR)replacement->chars,
                       replacement->length, output.bytes, &output.count);

  if (result == PCRE2_ERROR_NOMEMORY) {
    resizeBuffer(&output, output.count);
    goto substitute;
  } else if (result < 0) {
    PCRE2_UCHAR8 error_message[256];
    pcre2_get_error_message(result, error_message, sizeof(error_message));
    crash("pcre2_substitute(%d): %s", result, (char *)error_message);
  }

  return bufferToString(&output);
}

NATIVE_GETTER(Regex, source, OBJ_VAL);
NATIVE_METHOD_NAMED(Regex, plus, "+", 1) {
  ObjRegex *regex = asRegex(this);
  if (isString(args[0])) {
    ObjString *source =
        stringf("%s\\Q%s\\E", regex->source->chars, asChars(args[0]));
    return OBJ_VAL(makeRegex(source));
  } else {
    return OBJ_VAL(
        makeRegex(concatStrings(regex->source, asRegex(args[0])->source)));
  }
}

REGISTER_OBJECT_DEF(Regex);
const ObjDef Regex = {
    .className = "Regex",
    .size = sizeof(ObjRegex),
    .mark = markRegex,
    .free = freeRegex,
    .inspect = inspectRegex,
    .dump = dumpRegex,
    .length = regexLength,
};

ECS_COMPONENT_DECLARE(RegexError);
ECS_COMPONENT_DECLARE(Regex2);
ECS_TAG_DECLARE(RegexSource);

static void CompileRegex(ecs_iter_t *it) {
  // EntityId *source = ecs_field(&it, Regex2, 0);
}

static ECS_DTOR(Regex2, regex, { pcre2_code_free(regex->code); });

void RegexesImport(World *world) {
  ECS_MODULE(world, Regexes);

  ECS_COMPONENT(world, RegexError);
  ECS_COMPONENT(world, Regex2);

  ECS_TAG_DEFINE(world, RegexSource);

  ECS_SYSTEM(world, CompileRegex, EcsOnUpdate, (RegexSource, $source), !Regex2,
             !RegexError);

  ecs_set_hooks(world, Regex2, {.dtor = ecs_dtor(Regex2)});
}
