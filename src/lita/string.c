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
static ObjString *makeString(char *chars, int length, Hash hash) {
  ObjString *string = allocateString();
  string->length = length;
  string->chars = chars;
  string->obj.hash = hash;

  intern(OBJ_VAL(string));
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

ObjString *newString(const char *chars) {
  if (chars == NULL) return NULL;
  return copyString(chars, strlen(chars));
}

ObjString *takeString(char *chars, int length) {
  if (length == -1) length = strlen(chars);
  Hash hash;
  ObjString *interned = (ObjString *)getInterned(&hash, chars, length);

  if (interned != NULL) {
    FREE_ARRAY(char, chars, length + 1);
    return interned;
  }
  return makeString(chars, length, hash);
}

ObjString *copyString(const char *chars, usize length) {
  Hash hash;
  ObjString *interned = (ObjString *)getInterned(&hash, chars, length);

  if (interned != NULL) return interned;

  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return makeString(heapChars, length, hash);
}

ObjString *bufferToString(Buffer *buf) {
  if (buf->count == 0 || buf->bytes[buf->count - 1] != '\0')
    appendCharToBuffer(buf, '\0');
  resizeBuffer(buf, buf->count);
  return takeString((char *)buf->bytes, buf->count - 1);
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

int fstringFormat(FILE *io, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int result = vfstringFormat(io, fmt, args);
  va_end(args);
  return result;
}

static const char *stringBytes(Obj *obj, int length) {
  ObjString *str = (ObjString *)obj;
  if (length != str->length) return NULL;
  return str->chars;
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

NATIVE_METHOD(String, replace, 2) {
  ObjString *str = asString(this);
  ObjString *to = asString(args[1]);

#if ENABLE_REGEX
  if (isRegex(args[0])) return OBJ_VAL(replaceRegex(str, asRegex(args[0]), to));

#endif

  ObjString *from = asString(args[0]);
  Buffer out = newBuffer(str->length);

  for (int i = 0; i < str->length; i++) {
    if (strncmp(str->chars + i, from->chars, from->length) == 0) {
      appendStrToBuffer(&out, to->chars, to->length);
      i += from->length - 1;
    } else {
      appendCharToBuffer(&out, str->chars[i]);
    }
  }

  return OBJ_VAL(bufferToString(&out));
}

static int stringLength(Obj *obj) { return ((ObjString *)obj)->length; }

void freeString(Obj *obj) {
  ObjString *string = (ObjString *)obj;
  FREE_ARRAY(char, string->chars, string->length + 1);
}

void markString(Obj *obj) {}

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
    .interned = true,
    .bytes = stringBytes,
    .free = freeString,
    .mark = markString,
    .inspect = inspectString,
    .dump = dumpString,
    .length = stringLength,
};
