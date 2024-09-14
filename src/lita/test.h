#include <assert.h>

#include "term.h"

#define assertEqual(a, b) assert(valuesEqual(a, b))
#define escape(s) #s
#define green(s) FG_GREEN s FG_DEFAULT
#define red(s) FG_RED s FG_DEFAULT
