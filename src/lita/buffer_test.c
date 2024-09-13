#include <assert.h>

#include "buffer.h"
#include "string.h"

void buffer_test() {
  Buffer buf = newBuffer(0);
  appendStrToBuffer(&buf, "abc", 3);
  appendBuffer(&buf, (u8 *)"def", 3);

  assert(buf.count == 6);

  ObjString *a = bufferToString(&buf);
  ObjString *b = newString("abcdef");

  assert(a == b);
}
