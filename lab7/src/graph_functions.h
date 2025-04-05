#ifndef GRAPH_FUNCTIONS_H
#define GRAPH_FUNCTIONS_H

#include "constants.h"

Graph* create_graph(unsigned short V);
void add_edge(Graph* graph, unsigned short src, unsigned short dest);
int is_valid(unsigned short N, int M);
int has_cycle(unsigned short N, Graph* graph);
void free_graph(Graph* graph);

#endif

