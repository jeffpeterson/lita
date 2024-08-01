#include <assert.h>

#include "debug.h"
#include "lib.h"
#include "xxhash.h"

void xxhash_test() {
  u8 buffer[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  size_t size = sizeof(buffer);

  u64 hash64 = XXH64(buffer, size, 0);
  // printf("XXH64: %#llx\n", hash64);
  assert(hash64 == 0x438e2507bf950423);

  u64 hash3 = XXH3_64bits(buffer, size);
  // printf("XXH3_64bits: %#llx\n", hash3);
  assert(hash3 == 0xa6584d1d9a6ae704);
}
