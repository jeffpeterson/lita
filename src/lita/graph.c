#include <stdlib.h>

#include "graph.h"

void init_graph(Graph *graph) {
  initTable(&graph->nodes);
  initTable(&graph->edges);
}

void free_graph(Graph *graph) {
  freeTable(&graph->nodes);
  freeTable(&graph->edges);
}
