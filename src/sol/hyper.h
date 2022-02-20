#ifndef sol_hyper_h
#define sol_hyper_h

// #include <db_cxx.h>
#include <ossp/uuid.h>

#include "store.h"

typedef uuid_t Id;

typedef struct Graph {
  Store links;
  Store data;
} Graph;

#endif
