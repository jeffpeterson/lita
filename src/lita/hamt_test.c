#include <assert.h>
#include <string.h>

#include "hamt/hamt.h"
#include "xxhash.h"

static uint32_t hash_string(const void *key, const size_t gen) {
  size_t length = key ? strlen(key) : 0;
  return XXH32(key, length, gen);
}

static int key_cmp(const void *a, const void *b) {
  assert(a), assert(b);
  return strcmp(a, b);
}

void hamt_test() {
  struct hamt_config cfg = {.key_hash_fn = hash_string,
                            .key_cmp_fn = key_cmp,
                            .ator = &hamt_allocator_default};

  struct hamt *h = hamt_create(&cfg);

  char *hi = "hi";
  char *th = "there";
  assert(hamt_size(h) == 0);
  hamt_set(h, hi, th);
  assert(hamt_size(h) == 1);
  // const char *v = hamt_get(h, hi);
  // assert(key_cmp(v, th) == 0);
}
