#include <assert.h>

#include "buffer.h"
#include "lib.h"
#include "string.h"

void buffer_test() {
  Buffer buf = newBuffer(0);
  appendStrToBuffer(&buf, "abc");
  appendBuffer(&buf, (u8 *)"def", 3);

  assert(buf.count == 6);

  ObjString *a = buffer_to_string(&buf);
  ObjString *b = new_string("abcdef");

  assert(a == b);
}
