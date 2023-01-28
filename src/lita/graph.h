#ifndef lita_graph_h
#define lita_graph_h

#include "common.h"
#include "object.h"
#include "table.h"

typedef struct Graph {
  Table nodes;
  Table edges;
} Graph;

void init_graph(Graph *graph);
void free_graph(Graph *graph);

void graph_edge(ObjTuple *edge);
void graph_add(Value index);
void graph_disconnect(ObjTuple *edge);

#endif
