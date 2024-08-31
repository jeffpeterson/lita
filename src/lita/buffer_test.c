#include <assert.h>

#include "buffer.h"
#include "lib.h"
#include "string.h"

void buffer_test() {
  Buffer buf = new_buffer(0);
  append_str_to_buffer(&buf, "abc", 3);
  append_buffer(&buf, (u8 *)"def", 3);

  assert(buf.count == 6);

  ObjString *a = buffer_to_string(&buf);
  ObjString *b = newString("abcdef");

  assert(a == b);
}
