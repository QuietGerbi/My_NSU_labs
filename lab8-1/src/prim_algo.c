#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "prim_algo.h"

#define INF LLONG_MAX

int is_valid(int N, int M) {
    if (N < 0 || N > MAX_N) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (M < 0 || M > (N * (N - 1) / 2)) {
        printf("bad number of edges\n");
        return 0;
    }
    return 1;
}

int prim(int n, AdjList* adj_list, Edge saved_edges[]) {
    int* in_mst = (int*)calloc(n + 1, sizeof(int));
    long long* key = (long long*)malloc((n + 1) * sizeof(long long));
    int* parent = (int*)malloc((n + 1) * sizeof(int));

    if (!in_mst || !key || !parent){
        free(in_mst);
        free(key);
        free(parent);
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        key[i] = INF;
        in_mst[i] = 0;
    }
    key[1] = 0;
    parent[1] = -1;

    int edge_index = 0;
    for (int count = 0; count < n; count++) {
        int u = -1;
        long long min_key = INF;
        for (int v = 1; v <= n; v++) {
            if (!in_mst[v] && key[v] < min_key) {
                min_key = key[v];
                u = v;
            }
        }
        if (u == -1){
            free(in_mst);
            free(key);
            free(parent);
            return edge_index;
        }
        in_mst[u] = 1;
        if (parent[u] != -1) {
            saved_edges[edge_index++] = (Edge){parent[u], u, (int)key[u]};
        }
        for (int i = 0; i < adj_list[u].size; i++) {
            int v = adj_list[u].edges[i].dest;
            int weight = adj_list[u].edges[i].weight;
            if (!in_mst[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }
    free(in_mst);
    free(key);
    free(parent);
    return edge_index;
}


