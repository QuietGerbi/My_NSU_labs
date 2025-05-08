#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "bitset.h"
#include "dijkstra.h"
#include "constants.h"
#include "html.h"

void free_graph(int** graph, int N) {
    if (graph) {
        for (int i = 1; i <= N; i++) {
            if (graph[i]) free(graph[i]);
        }
        free(graph);
    }
}


void param_input(int* N, int* S, int* F, int* M) {
    if (scanf("%d", N)!=1){
        return;
    };
    if (scanf("%d %d", S, F)!=2){
        return;
    };
    if (scanf("%d", M)!=1){
        return;
    };
}

long long int is_valid(int N, int S, int F, int M) {
    if (N < 0 || N > 5000) {
        printf("bad number of vertices\n");
        return -1;
    }
    if ((S < 1 || S > N) || (F < 1 || F > N)) {
        printf("bad vertex\n");
        return -1;
    }
    if (M < 0 || M > (N * (N - 1) / 2)) {
        printf("bad number of edges\n");
        return -1;
    }
    return 0;
}

void dijkstra(int N, int S, int F, int** graph, int mode, char* output_filename) {
    long long* dist = (long long*)malloc((N + 1) * sizeof(long long));
    int* prev = (int*)malloc((N + 1) * sizeof(int));
    int* count_paths = (int*)malloc((N + 1) * sizeof(int));
    Bitset* visited = init_bitset();

    if (!dist || !prev || !count_paths || !visited) {
        free(dist);
        free(prev);
        free(count_paths);
        free_bitset(visited);
        return;
    }

    for (int i = 1; i <= N; i++) {
        dist[i] = LLONG_MAX;
        prev[i] = -1;
        count_paths[i] = 0;
    }
    dist[S] = 0;
    count_paths[S] = 1;

    for (int count = 0; count < N; count++) {
        int u = -1;
        long long min_dist = LLONG_MAX;

        for (int v = 1; v <= N; v++) {
            if (!get_bitset_bit(visited, v) && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }

        if (u == -1) break;

        set_bitset_bit(visited, u);

        for (int v = 1; v <= N; v++) {
            if (graph[u][v] != 0) {
                long long weight = graph[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    count_paths[v] = count_paths[u];
                } else if (dist[u] + weight == dist[v]) {
                    count_paths[v]++;
                }
            }
        }
    }

    if (mode){
        write_html(output_filename, graph, prev, dist, N, F, S);
        return;
    }

    for (int i = 1; i <= N; i++) {
        if (dist[i] == LLONG_MAX) {
            printf("oo ");
        } else if (dist[i] > INT_MAX) {
            printf("INT_MAX+ ");
        } else {
            printf("%lld ", dist[i]);
        }
    }
    printf("\n");

    if (dist[F] == LLONG_MAX) {
        printf("no path\n");
    } else if (dist[F] > INT_MAX && count_paths[F] >= 2) {
        printf("overflow\n");
    } else {
        int* path = (int*)malloc(N * sizeof(int));
        if (path) {
            int pathSize = 0;
            for (int v = F; v != -1; v = prev[v]) {
                path[pathSize++] = v;
            }
            for (int i = 0; i < pathSize; i++) {
                printf("%d ", path[i]);
            }
            printf("\n");
            free(path);
        } else {
            printf("no path\n");
        }
    }

    free(dist);
    free(prev);
    free(count_paths);
    free_bitset(visited);
}




