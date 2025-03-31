#ifndef SVG_FUNCTION_H
#define SVG_FUNCTION_H

#include "constants.h"

int is_in_mst(Edge* saved_edges, int edges_num, int u, int v);
int get_weight(Edge* all_edges, int all_edges_num, int u, int v);
void save_edges_to_svg(Edge* saved_edges, int edges_num, int vertex_count, Edge* all_edges, int all_edges_num);

#endif


