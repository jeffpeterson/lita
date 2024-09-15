#include "chunk.h"
#include "test.h"

#define assertEncodeDecode(n, size)                                            \
  do {                                                                         \
    u32 c;                                                                     \
    u8 bytes[5];                                                               \
    assert(encodeLong(n, bytes) == size);                                      \
    assert(decodeLong(&c, bytes) == size);                                     \
    assert(c == n);                                                            \
  } while (false)

void chunk_test() {
  assertEncodeDecode(0x7f, 1);
  assertEncodeDecode(0x80, 2);
  assertEncodeDecode(0x3fff, 2);
  assertEncodeDecode(0xabcd, 3);
  assertEncodeDecode(0x12345678, 5);
}
