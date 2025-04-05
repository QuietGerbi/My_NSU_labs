#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "graph_functions.h"
#include "sort_function.h"

int main() {
    unsigned short N;
    int M;
    
    if (scanf("%hu", &N) != 1) {
        printf("bad number of lines");
        return 0;
    }

    if (scanf("%d", &M) != 1) {
        printf("bad number of lines");
        return 0;
    }

    if (!is_valid(N, M)) {
        return 0;
    }

    Graph* graph = create_graph(N);
    if (!graph) {
        return 0;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) {
            printf("bad number of lines");
            free_graph(graph);
            return 0;
        }
        if (u < 1 || u > N || v < 1 || v > N) {
            printf("bad vertex");
            free_graph(graph);
            return 0;
        }
        add_edge(graph, (unsigned short)(u - 1), (unsigned short)(v - 1));
    }

    if (has_cycle(N, graph)) {
        printf("impossible to sort");
    } else {
        topological_sort(N, graph);
    }

    free_graph(graph);
    return 0;
}



