#include <stdio.h>
#include "set_valid_func.h"

int is_valid(int N, int M) {
    if (N < 0 || N > 5000) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (M < 0 || M > (N * (N - 1) / 2)) {
        printf("bad number of edges\n");
        return 0;
    }
    return 1;
}

int comparator(const void *a, const void *b) {
    const Edge *edge1 = (const Edge *)a;
    const Edge *edge2 = (const Edge *)b;
    return edge1->weight - edge2->weight;
}

void make_set(int parent[], int rank[], int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find_parent(int parent[], int component) {
    if (parent[component] == component)
        return component;
    return parent[component] = find_parent(parent, parent[component]);
}

void union_set(int u, int v, int parent[], int rank[]) {
    u = find_parent(parent, u);
    v = find_parent(parent, v);

    if (u != v) {
        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else {
            parent[v] = u;
            if (rank[u] == rank[v]) {
                rank[u]++;
            }
        }
    }
}


