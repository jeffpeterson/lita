#include <assert.h>
#include <time.h>

#include "native.h"
#include "random.h"

static __thread RandomState randomState = PCG32_INITIALIZER;

AT_VM_BOOT(setRandomSeed) {
  randomSeed(time(NULL));
  return NULL;
}

void randomSeed(u64 seed) { pcg32_srandom_r(&randomState, seed, 42); }
u32 random() { return pcg32_random_r(&randomState); }
u32 randomBelow(u32 max) { return pcg32_boundedrand_r(&randomState, max); }
u32 randomMax(u32 max) { return randomBelow(max + 1); }
u32 randomBetween(u32 min, u32 max) {
  assert(min < max);
  return min + randomMax(max - min);
}

NATIVE_FUNCTION(random, 0) {
  if (argc == 2) return number(randomBetween(asInt(args[0]), asInt(args[1])));
  else if (argc == 1) return number(randomBelow(asInt(args[0])));
  else return number(random());
}
