#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "html.h"
#include "dijkstra.h"
#include "constants.h"
#include "bitset.h"

int main(int argc, char* argv[]) {
    int N, S, F, M;
    int** graph = NULL;
    char mode[3] = "";
    char output_filename[100] = "";

    if (argc > 2) {
        strncpy(mode, argv[1], sizeof(mode) - 1);
        strncpy(output_filename, argv[2], sizeof(output_filename) - 1);
    }

    int html_mode_check = (strcmp(mode, "-p") == 0);

    param_input(&N, &S, &F, &M);
    if (is_valid(N, S, F, M) == -1) {
        return 0;
    }

    graph = (int**)malloc((N + 1) * sizeof(int*));
    if (!graph) {
        return 0;
    }
    
    for (int i = 1; i <= N; i++) {
        graph[i] = (int*)calloc(N + 1, sizeof(int));
        if (!graph[i]) {
            for (int j = 1; j < i; j++) {
                free(graph[j]);
            }
            free(graph);
            return 0;
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        if (scanf("%d %d %lld", &u, &v, &w) != 3) {
            printf("bad number of lines\n");
            free_graph(graph, N);
            return 0;
        }
        if (u < 1 || u > N || v < 1 || v > N) {
            printf("bad vertex\n");
            free_graph(graph, N);
            return 0;
        }
        if (w < 0 || w > INT_MAX) {
            printf("bad length\n");
            free_graph(graph, N);
            return 0;
        }
        graph[u][v] = w;
        graph[v][u] = w;
    }

    dijkstra(N, S, F, graph, html_mode_check, output_filename);
    free_graph(graph, N);
    return 0;
}




