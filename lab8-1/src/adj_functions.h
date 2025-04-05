#ifndef ADJ_FUNCTIONS_H
#define ADJ_FUNCTIONS_H

#include "constants.h"

AdjList* create_adj_list(int N);
void add_edge(AdjList* adj_list, int u, int v, int weight);
void free_adj_list(AdjList* adj_list, int N);

#endif


