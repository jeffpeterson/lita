#include "chunk.h"
#include "test.h"

#define assertEncodeDecode(lng, size)                                          \
  {                                                                            \
    u32 res;                                                                   \
    u8 bytes[5] = {0xff, 0xff, 0xff, 0xff, 0xff};                              \
    assert(encodeLong(lng, bytes) == size);                                    \
    assert(decodeLong(&res, bytes) == size);                                   \
    assert(res == lng);                                                        \
  }

void chunk_test() {
  assertEncodeDecode(0x7f, 1);
  assertEncodeDecode(0x80, 2);
  assertEncodeDecode(0x3fff, 2);
  assertEncodeDecode(0xabcd, 3);
  assertEncodeDecode(0x12345678, 5);

  Chunk chunk;
  initChunk(&chunk);
  for (int i = 0; i < 1000; i++) addConstant(&chunk, NUMBER_VAL(i));
  assert(chunk.constants.count == 1000);

  assertEqual(getConstant(&chunk, 999), number(999));
  writeChunkLong(&chunk, 999, 1, nil);
  assert(chunk.count == 2);

  writeChunkLong(&chunk, 1, 1, nil);
  assert(chunk.count == 3);

  u8 *ip = chunk.code;
  assertEqual(readConstant(&chunk, &ip), number(999));
  assert(ip == chunk.code + 2);

  assertEqual(readConstant(&chunk, &ip), number(1));
  assert(ip == chunk.code + 3);
}
