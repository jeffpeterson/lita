#include <assert.h>
#include <ctype.h>
#include <stdarg.h>

#include "memory.h"
#include "native.h"
#include "scanner.h"
#include "string.h"
#include "term.h"
#include "value.h"
#include "vm.h"

#if ENABLE_REGEX
#include "regex.h"
#endif

Value string(const char *str) { return obj(newString(str)); }

char *stringChars(ObjString *string) {
  if (!string) return NULL;
  assert(string->obj.def == &String);
  return string->chars;
}

/** Allocate an ObjString for a (null-terminated) char string. */
ObjString *takeString(char *chars, int length) {
  if (chars == NULL) return NULL;
  if (length == -1) length = strlen(chars);
  ObjString *string = allocateString();
  string->length = length;
  string->chars = chars;
  internObject((Obj **)&string);
  return string;
}

ObjString *concatStrings(ObjString *a, ObjString *b) {
  int length = a->length + b->length;
  char *chars = ALLOCATE(char, length + 1);
  memcpy(chars, a->chars, a->length);
  memcpy(chars + a->length, b->chars, b->length);
  chars[length] = '\0';
  return takeString(chars, length);
}

ObjString *newString(const char *chars) { return copyString(chars, -1); }

ObjString *copyString(const char *chars, usize length) {
  if (chars == NULL) return NULL;
  if (length == -1) length = strlen(chars);
  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return takeString(heapChars, length);
}

ObjString *bufferToString(Buffer *buf) {
  if (buf->count == 0 || buf->bytes[buf->count - 1] != '\0')
    appendCharToBuffer(buf, '\0');
  resizeBuffer(buf, buf->count);
  return takeString(buf->chars, buf->count - 1);
}

ObjString *escapeString(ObjString *str) {
  Buffer out = newBuffer(str->length + 3);
  appendCharToBuffer(&out, '"');

  for (int i = 0; i < str->length; i++) {
    u8 ch = str->chars[i];

    if (ch == '\\') appendCharToBuffer(&out, ch);

    if (isprint(ch) || ch > 127) {
      appendCharToBuffer(&out, ch);
      continue;
    }

    appendCharToBuffer(&out, '\\');

    ch = ch >= '\0' && ch <= '\6'  ? ch + '0'
         : ch == '\a'              ? 'a'
         : ch == '\b'              ? 'b'
         : ch == '\e'              ? 'e'
         : ch == '\f'              ? 'f'
         : ch == '\n'              ? 'n'
         : ch == '\r'              ? 'r'
         : ch == '\t'              ? 't'
         : ch == '\\' || ch == '"' ? ch
                                   : 'x';
    appendCharToBuffer(&out, ch);
  }

  appendCharToBuffer(&out, '"');

  return bufferToString(&out);
}

ObjString *unescapeString(ObjString *str) {
  char *out = ALLOCATE(char, str->length + 1);
  int len = 0;
  bool escape = false;

  for (int i = 0; i < str->length; i++) {
    char ch = str->chars[i];
    if (escape) {
      escape = false;
      out[len++] = ch >= '0' && ch <= '9' ? ch - '0'
                   : ch == 'a'            ? '\a'
                   : ch == 'b'            ? '\b'
                   : ch == 'e'            ? '\e'
                   : ch == 'f'            ? '\f'
                   : ch == 'n'            ? '\n'
                   : ch == 'r'            ? '\r'
                   : ch == 's'            ? ' '
                   : ch == 't'            ? '\t'
                   : ch == '\\'           ? '\\'
                   : ch == '\''           ? '\''
                   : ch == '"'            ? '"'
                                          : ch;
      continue;
    }

    if (ch == '\\') escape = true;
    else out[len++] = ch;
  }

  out[len] = '\0';

  return takeString(GROW_ARRAY(char, out, str->length + 1, len + 1), len);
}

ObjString *stringToCIdent(ObjString *str) {
  char *out = NULL;
  usize size = 0;
  FILE *io = open_memstream(&out, &size);

  for (int i = 0; i < str->length; i++) {
    char ch = str->chars[i];

    switch (ch) {
    case ' ': fputc('_', io); break;
    case '@': fputs("_at_", io); break;
    case '*': fputs("_star_", io); break;
    case '+': fputs("_plus_", io); break;
    case '-': fputs("_minus_", io); break;
    case '/': fputs("_slash_", io); break;
    case '%': fputs("_mod_", io); break;
    case '=': fputs("_eq_", io); break;
    case '!': fputs("_not_", io); break;
    case '<': fputs("_lt_", io); break;
    case '>': fputs("_gt_", io); break;
    case '&': fputs("_and_", io); break;
    case '|': fputs("_or_", io); break;
    case '^': fputs("_xor_", io); break;
    case '~': fputs("_tilde_", io); break;
    case '(': fputs("_lparen_", io); break;
    case ')': fputs("_rparen_", io); break;
    case '[': fputs("_lbrack_", io); break;
    case ']': fputs("_rbrack_", io); break;
    case '{': fputs("_lcurly_", io); break;
    case '}': fputs("_rcurly_", io); break;
    case ',': fputs("_comma_", io); break;
    case '`': fputs("_backtick_", io); break;
    case '.': fputs("_dot_", io); break;
    case ':': fputs("_colon_", io); break;
    case '#': fputs("_bang_", io); break;
    case ';': fputs("_semi_", io); break;
    case '?': fputs("_question_", io); break;

    default: {
      bool isAlpha = (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
      bool isWord = isAlpha || ch == '_';
      bool isDigit = ch >= '0' && ch <= '9';

      if (i == 0 && !isWord) fputc('_', io);
      if (isWord || isDigit) fputc(ch, io);
      else runtimeError("Invalid identifier: %s", str->chars);
    }
    }
  }

  fclose(io);
  return copyString(out, size);
}

ObjString *stringf(const char *fmt, ...) {
  char *str;
  va_list args;
  va_start(args, fmt);
  int len = vasprintf(&str, fmt, args);
  va_end(args);

  if (len < 0) return copyString("", 0);

  return takeString(str, len);
}

ObjString *vstringFormat(const char *fmt, va_list args) {
  char *out = NULL;
  usize size = 0;
  FILE *io = open_memstream(&out, &size);
  vfstringFormat(io, fmt, args);
  fclose(io);
  return takeString(out, size);
}

int vfstringFormat(FILE *io, const char *fmt, va_list args) {
  int i = 0;
  int count = 0;

  while (fmt[i] != '\0') {
    char c = fmt[i];

    if (c != '{') i++;
    else switch (fmt[i + 1]) {
      case '{':
        // Print string including the first bracket
        count += fprintf(io, "%.*s", ++i, fmt);
        fmt += i + 1; // Skip over the second bracket
        i = 0;
        continue;
      case '}': {
        // Print string without the first bracket
        count += fprintf(io, "%.*s", i, fmt);
        fmt += i + 2; // Skip the first and second bracket
        i = 0;
        Value v = va_arg(args, Value);
        count += inspectValue(io, v);
        continue;
      }

      default: crash("Invalid format: %s", fmt);
      }
  }
  // Print the rest of the string
  return fprintf(io, "%s", fmt) + count;
}

ObjString *stringFormat(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  ObjString *str = vstringFormat(fmt, args);
  va_end(args);
  return str;
}

ObjString *replaceString(ObjString *subject, ObjString *search,
                         ObjString *replacement) {
  Buffer out = newBuffer(subject->length);

  for (int i = 0; i < subject->length; i++) {
    if (strncmp(subject->chars + i, search->chars, search->length) == 0) {
      appendStrToBuffer(&out, replacement->chars, replacement->length);
      i += search->length - 1;
    } else appendCharToBuffer(&out, subject->chars[i]);
  }

  return bufferToString(&out);
}

int fstringFormat(FILE *io, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int result = vfstringFormat(io, fmt, args);
  va_end(args);
  return result;
}

// # Natives
COMPILED_SOURCE(string);
NATIVE_METHOD(String, string, 0) { return this; }
NATIVE_METHOD(String, concat, 1) {
  if (!isString(args[0])) {
    vmInvoke(string("string"), 0);
    return VOID;
  }

  return obj(concatStrings(asString(this), asString(args[0])));
}
ALIAS_OPERATOR(String, concat, plus, "+", 1);
ALIAS_OPERATOR(String, concat, invoke, "", 1);
ALIAS_OPERATOR(String, concat, star, "*", 1);
NATIVE_METHOD(String, escape, 0) {
  return OBJ_VAL(escapeString(asString(this)));
}
NATIVE_METHOD_NAMED(String, spaceship, "<=>", 1) {
  ObjString *str = asString(this);
  ObjString *other = asString(args[0]);
  return number(strcmp(str->chars, other->chars));
}
NATIVE_METHOD(String, codePoint, 0) {
  ObjString *str = asString(this);
  if (str->length == 0) return NIL_VAL;
  return NUMBER_VAL(codePoint(str->chars));
}
NATIVE_METHOD(String, codePointSize, 0) {
  ObjString *str = asString(this);
  if (str->length == 0) return NIL_VAL;
  return NUMBER_VAL(utfBytes(str->chars));
}
NATIVE_METHOD(String, slice, 2) {
  ObjString *str = asString(this);
  int start = asInt(args[0]);
  int length = asInt(args[1]);
  if (start == 0 && length < 0) start = length, length = -length;
  if (start < 0) start = str->length + start;
  if (length < 0) start += length, length = -length;
  if (start >= str->length) return string("");
  if (start < 0) start = 0;
  if (start + length > str->length) length = str->length - start;
  if (start == 0 && length == str->length) return this;

  return OBJ_VAL(copyString(str->chars + start, length));
}
NATIVE_METHOD(String, replace, 2) {
  ObjString *subject = asString(this);
  ObjString *replacement = asString(args[1]);

#if ENABLE_REGEX
  if (isRegex(args[0]))
    return OBJ_VAL(replaceRegex(subject, asRegex(args[0]), replacement));

#endif
  return OBJ_VAL(replaceString(subject, asString(args[0]), replacement));
}

static int stringLength(Obj *obj) { return ((ObjString *)obj)->length; }

void freeString(Obj *obj) {
  ObjString *string = (ObjString *)obj;
  FREE_ARRAY(char, string->chars, string->length + 1);
}

void hashString(Obj *obj, HashState *state) {
  ObjString *string = (ObjString *)obj;
  updateHash(state, string->chars, string->length);
}

int inspectString(Obj *obj, FILE *io) {
  ObjString *str = escapeString((ObjString *)obj);
  return fprintf(io, FG_GREEN "%s" FG_DEFAULT, str->chars) - 10;
}

int dumpString(Obj *obj, FILE *io) {
  ObjString *str = escapeString((ObjString *)obj);
  return fprintf(io, "string(%.*s)", str->length, str->chars);
}

REGISTER_OBJECT_DEF(String);
const ObjDef String = {
    .className = "String",
    .size = sizeof(ObjString),
    .hash = hashString,
    .free = freeString,
    .inspect = inspectString,
    .dump = dumpString,
    .length = stringLength,
};
