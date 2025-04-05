#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "adj_functions.h"
#include "prim_algo.h"

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) {
        printf("bad input\n");
        return 0;
    }
    if (!is_valid(N, M)) return 0;

    AdjList* adj_list = create_adj_list(N);
    if (!adj_list) {
        return 0;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        if (scanf("%d %d %lld", &u, &v, &w) != 3) {
            printf("bad number of lines\n");
            free_adj_list(adj_list, N);
            return 0;
        }
        if (u < 1 || u > N || v < 1 || v > N) {
            printf("bad vertex\n");
            free_adj_list(adj_list, N);
            return 0;
        }
        if (w < 0 || w > MAX_WEIGHT) {
            printf("bad length\n");
            free_adj_list(adj_list, N);
            return 0;
        }
        add_edge(adj_list, u, v, (int)w);
    }

    Edge* saved_edges = NULL;
    if (N > 1) {
        saved_edges = (Edge*)malloc((N - 1) * sizeof(Edge));
        if (!saved_edges) {
            printf("no spanning tree\n");
            free_adj_list(adj_list, N);
            return 0;
        }
    }

    int edges_num = prim(N, adj_list, saved_edges);
    if (edges_num != N - 1) {
        printf("no spanning tree\n");
    } else {
        for (int i = 0; i < edges_num; i++) {
            if (saved_edges[i].u < saved_edges[i].v) {
                printf("%d %d\n", saved_edges[i].u, saved_edges[i].v);
            } else {
                printf("%d %d\n", saved_edges[i].v, saved_edges[i].u);
            }
        }
    }

    free(saved_edges);
    free_adj_list(adj_list, N);
    return 0;
}


