#include <assert.h>
#include <ctype.h>
#include <stdarg.h>

#include "lib.h"
#include "memory.h"
#include "native.h"
#include "string.h"
#include "table.h"
#include "term.h"
#include "value.h"
#include "vm.h"

ObjString *as_string(let x) {
  assert(is_string(x));
  return AS_STRING(x);
}

/**
 * Allocate an ObjString for a (null-terminated) char string.
 */
static ObjString *allocate_string(char *chars, int length, Hash hash) {
  ObjString *string = ALLOCATE_OBJ(ObjString, OBJ_CUSTOM);
  string->obj.def = &String;
  string->length = length;
  string->chars = chars;
  string->obj.hash = hash;

  intern(OBJ_VAL(string));
  return string;
}

ObjString *concat_strings(ObjString *a, ObjString *b) {
  int length = a->length + b->length;
  char *chars = ALLOCATE(char, length + 1);
  memcpy(chars, a->chars, a->length);
  memcpy(chars + a->length, b->chars, b->length);
  chars[length] = '\0';
  return take_string(chars, length);
}

ObjString *new_string(const char *chars) {
  return copy_string(chars, strlen(chars));
}

ObjString *take_string(char *chars, int length) {
  Hash hash;
  ObjString *interned =
      (ObjString *)getInterned(&hash, OBJ_CUSTOM, chars, length);

  if (interned != NULL) {
    FREE_ARRAY(char, chars, length + 1);
    return interned;
  }
  return allocate_string(chars, length, hash);
}

ObjString *copy_string(const char *chars, int length) {
  Hash hash;
  ObjString *interned =
      (ObjString *)getInterned(&hash, OBJ_CUSTOM, chars, length);

  if (interned != NULL) return interned;

  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocate_string(heapChars, length, hash);
}

ObjString *buffer_to_string(Buffer *buf) {
  if (buf->count == 0 || buf->bytes[buf->count - 1] != '\0')
    appendCharToBuffer(buf, '\0');
  growBuffer(buf, buf->count);
  return take_string((char *)buf->bytes, buf->count - 1);
}

ObjString *escape_string(ObjString *str) {
  Buffer out = newBuffer(str->length + 3);
  appendCharToBuffer(&out, '"');

  for (int i = 0; i < str->length; i++) {
    u8 ch = str->chars[i];

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

  return buffer_to_string(&out);
}

ObjString *unescape_string(ObjString *str) {
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

  return take_string(GROW_ARRAY(char, out, str->length + 1, len + 1), len);
}

ObjString *string_to_c_ident(ObjString *str) {
  // Extra byte in case of leading "_"
  char *out = ALLOCATE(char, str->length + 2);
  int len = 0;

  for (int i = 0; i < str->length; i++) {
    char ch = str->chars[i];
    bool isAlpha = (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    bool isWord = isAlpha || ch == '_';
    bool isDigit = ch >= '0' && ch <= '9';

    if (i == 0 && !isWord) out[len++] = '_';
    if (!isWord && !isDigit) ch = '_';

    out[len++] = ch;
  }

  out[len] = '\0';

  return take_string(GROW_ARRAY(char, out, str->length + 2, len + 1), len);
}

ObjString *stringf(const char *fmt, ...) {
  char *str;
  va_list args;
  va_start(args, fmt);
  int len = vasprintf(&str, fmt, args);
  va_end(args);

  if (len < 0) return copy_string("", 0);

  return take_string(str, len);
}

ObjString *vstring_format(const char *fmt, va_list args) {
  Buffer buf = newBuffer(8);
  int i = 0;

  while (fmt[i] != '\0') {
    char c = fmt[i];

    if (c != '{') i++;
    else switch (fmt[i + 1]) {
      case '{':
        // Print string including the first bracket
        appendBuffer(&buf, (u8 *)fmt, ++i);
        fmt += i + 1; // Skip the second bracket
        i = 0;
        continue;
      case '}': {
        // Print string without the first bracket
        appendBuffer(&buf, (u8 *)fmt, i);
        fmt += i + 2; // Skip the first and second bracket
        i = 0;
        Value v = va_arg(args, Value);
        ObjString *show = as_string(to_string(v));
        appendBuffer(&buf, (u8 *)show->chars, show->length);
        continue;
      }

      default:
        // Format error
        runtimeError("Invalid format: %s", fmt);
        crash("format");
      }
  }

  // Append rest of fmt including null byte.
  appendBuffer(&buf, (u8 *)fmt, i);

  growBuffer(&buf, buf.count);
  return take_string((char *)buf.bytes, buf.count);
}

ObjString *string_format(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  ObjString *str = vstring_format(fmt, args);
  va_end(args);
  return str;
}

int fstring_format(FILE *io, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  ObjString *str = vstring_format(fmt, args);
  va_end(args);
  return fwrite(str->chars, sizeof(char), str->length, io);
}

static const char *string_bytes(Obj *obj, int length) {
  ObjString *str = (ObjString *)obj;
  if (length != str->length) return NULL;
  return str->chars;
}

// # Natives
COMPILED_SOURCE(string);
NATIVE_METHOD(String, string, 0) { return this; }
NATIVE_METHOD(String, concat, 1) {
  let other = to_string(args[0]);
  return obj(concat_strings(as_string(this), as_string(other)));
}
ALIAS_OPERATOR(String, concat, plus, "+", 1);
ALIAS_OPERATOR(String, concat, star, "*", 1);
NATIVE_METHOD(String, escape, 0) {
  return OBJ_VAL(escape_string(AS_STRING(this)));
}

static int string_length(Obj *obj) { return ((ObjString *)obj)->length; }

void free_string(Obj *obj) {
  ObjString *string = (ObjString *)obj;
  FREE_ARRAY(char, string->chars, string->length + 1);
}

void mark_string(Obj *obj) {}

int inspect_string(Obj *obj, FILE *io) {
  ObjString *str = escape_string((ObjString *)obj);
  return fprintf(io, FG_GREEN "%s" FG_DEFAULT, str->chars) - 10;
}

int dump_string(Obj *obj, FILE *io) {
  ObjString *str = escape_string((ObjString *)obj);
  return fprintf(io, "str(%.*s)", str->length, str->chars);
}

const ObjDef String = {
    .class_name = "String",
    .size = sizeof(ObjString),
    .interned = true,
    .bytes = string_bytes,
    .free = free_string,
    .mark = mark_string,
    .inspect = inspect_string,
    .dump = dump_string,
    .length = string_length,
};
