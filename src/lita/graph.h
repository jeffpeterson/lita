#ifndef lita_graph_h
#define lita_graph_h

// #include <db.h>
// #include <ossp/uuid.h>

#include "common.h"

// #include "store.h"

// typedef uuid_t Id;

typedef struct Graph {
  // DB db;
  // Store links;
  // Store data;
} Graph;

void init_graph(Graph *graph);
void free_graph(Graph *graph);

#endif
