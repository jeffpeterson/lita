#include <assert.h>

#include "term.h"

#define assertEqual(a, b)                                                      \
  assert(valuesEqual(a, b) || (trace("LHS", a), trace("RHS", b), 0))

#define escape(s) #s
#define green(s) FG_GREEN s FG_DEFAULT
#define red(s) FG_RED s FG_DEFAULT
