#ifndef lita_random_h
#define lita_random_h

#include "common.h"
#include "pcg_basic.h"
#include "value.h"

typedef pcg32_random_t RandomState;

void randomSeed(u64 seed);

/** 0 <= n < 2^32 */
u32 random();

/** 0 <= n < max */
u32 randomBelow(u32 max);

/** 0 <= n <= max */
u32 randomMax(u32 max);

/** min <= n <= max */
u32 randomBetween(u32 min, u32 max);

#endif
