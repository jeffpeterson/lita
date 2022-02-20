#include <stdarg.h>

#include "buffer.h"
#include "lib.h"
#include "memory.h"
#include "string.h"
#include "table.h"
#include "value.h"
#include "vm.h"

/**
 * Allocate an ObjString for a (null-terminated) char array.
 */
static ObjString *allocateString(char *chars, int length, Hash hash) {
  ObjString *string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
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
  return copyString(chars, strlen(chars));
}

ObjString *takeString(char *chars, int length) {
  Hash hash;
  ObjString *interned =
      (ObjString *)getInterned(&hash, OBJ_STRING, chars, length);

  if (interned != NULL) {
    FREE_ARRAY(char, chars, length + 1);
    return interned;
  }
  return allocateString(chars, length, hash);
}

ObjString *copyString(const char *chars, int length) {
  Hash hash;
  ObjString *interned =
      (ObjString *)getInterned(&hash, OBJ_STRING, chars, length);

  if (interned != NULL)
    return interned;

  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocateString(heapChars, length, hash);
}

ObjString *stringf(const char *fmt, ...) {
  char *str;
  va_list args;
  va_start(args, fmt);
  int len = vasprintf(&str, fmt, args);
  va_end(args);

  if (len < 0)
    return copyString("", 0);

  return takeString(str, len);
}

ObjString *stringFormat(const char *fmt, ...) {
  Buffer buf = newBuffer(8);
  enum { A_NONE, A_PRINT, A_DEBUG, A_SHOW, A_ESCAPE } action = A_NONE;
  int offset = 0;
  int i = 0;

  va_list args;
  va_start(args, fmt);

  for (i = 0; fmt[i] != '\0'; i++) {
    char c = fmt[i];

    if (c == '{') {
      char c2 = fmt[i + 1];
      switch (c2) {
      case '{':
        // Print string up to the first bracket
        appendBuffer(&buf, fmt + offset, i - offset);
        // Skip the second bracket.
        offset += ++i;
        break;
      case '}': {
        i++;
        Value v = va_arg(args, Value);
        ObjString *show = asStr(toString(v));
        appendBuffer(&buf, show->chars, show->length);
        break;
      }

      default:
        // Format error
        runtimeError("Invalid format: %s", fmt);
        crash("format");
      }
    }
  }
  va_end(args);

  // Append rest of fmt including null byte.
  appendBuffer(&buf, fmt + offset, i - offset);

  growBuffer(&buf, buf.count);
  return takeString(&buf.bytes, buf.count);
}
