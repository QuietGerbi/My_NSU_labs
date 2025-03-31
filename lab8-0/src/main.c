#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "kruskal.h"
#include "set_valid_func.h"
#include "svg_function.h"

int main(int argc, char* argv[]) {
    int N, M;
    char mode[3] = "";
    if (scanf("%d %d", &N, &M) != 2) {
        printf("bad input\n");
        return 0;
    }

    if (!is_valid(N, M)) {
        return 0;
    }

    if (argc > 1) {
        strncpy(mode, argv[1], sizeof(mode) - 1);
    }

    int gen_mode_check = (strcmp(mode, "-g") == 0);

    Edge *edges = (Edge *)malloc(M * sizeof(Edge));
    if (!edges) {
        printf("no spanning tree\n");
        return 0;
    }

    int edge_count = 0;
    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        if (scanf("%d %d %lld", &u, &v, &w) != 3) {
            printf("bad number of lines\n");
            free(edges);
            return 0;
        }
        if (u < 1 || u > N || v < 1 || v > N) {
            printf("bad vertex\n");
            free(edges);
            return 0;
        }
        if (w < 0 || w > INT_MAX) {
            printf("bad length\n");
            free(edges);
            return 0;
        }

        edges[edge_count].u = u;
        edges[edge_count].v = v;
        edges[edge_count].weight = (int)w;
        edge_count++;
    }

    Edge *saved_edges = NULL;
    if (N > 1) {
        saved_edges = (Edge *)malloc((N-1) * sizeof(Edge));
        if (!saved_edges) {
            printf("no spanning tree\n");
            free(edges);
            return 0;
    }
}

    int edges_num = kruskal(N, edge_count, edges, saved_edges);

    if (edges_num != N-1) {
        printf("no spanning tree\n");
    } else {

        if (gen_mode_check==1){
            save_edges_to_svg(saved_edges, edges_num, N, edges, edge_count);
        }
        for (int i = 0; i < edges_num; i++) {
            if (saved_edges[i].u < saved_edges[i].v) {
                printf("%d %d\n", saved_edges[i].u, saved_edges[i].v);
            } else {
                printf("%d %d\n", saved_edges[i].v, saved_edges[i].u);
            }
        }
    }

    free(edges);
    free(saved_edges);
    return 0;
}



