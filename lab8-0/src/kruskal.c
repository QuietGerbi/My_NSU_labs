#include <stdlib.h>
#include "kruskal.h"
#include "set_valid_func.h"

int kruskal(int n, int edge_count, Edge edges[], Edge saved_edges[]) {
    qsort(edges, edge_count, sizeof(Edge), comparator);

    int parent[n+1];
    int rank[n+1];
    make_set(parent, rank, n);

    int edge_index = 0;
    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        int root_u = find_parent(parent, u);
        int root_v = find_parent(parent, v);

        if (root_u != root_v) {
            union_set(root_u, root_v, parent, rank);
            saved_edges[edge_index++] = edges[i];
        }
    }

    return edge_index;
}

