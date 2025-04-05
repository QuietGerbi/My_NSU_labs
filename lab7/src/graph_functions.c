#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "graph_functions.h"

#define MAX_N 2000

Graph* create_graph(unsigned short V) {
    Graph* graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->array = calloc(V, sizeof(AdjList));
    for (unsigned short i = 0; i < V; i++) {
        graph->array[i].capacity = 10;
        graph->array[i].vertices = malloc(graph->array[i].capacity * sizeof(unsigned short));
    }
    return graph;
}

void add_edge(Graph* graph, unsigned short src, unsigned short dest) {
    AdjList* list = &graph->array[src];
    if (list->count == list->capacity) {
        list->capacity *= 2;
        list->vertices = realloc(list->vertices, list->capacity * sizeof(unsigned short));
    }
    list->vertices[list->count++] = dest;
}

int is_valid(unsigned short N, int M) {
    if (N == 0 || N > MAX_N) {
        puts("bad number of vertices");
        return 0;
    }
    if (M < 0 || M > N * (N - 1) / 2) {
        puts("bad number of edges");
        return 0;
    }
    return 1;
}

int has_cycle(unsigned short N, Graph* graph) {
    unsigned short* indegree = calloc(N, sizeof(unsigned short));
    unsigned short* queue = malloc(N * sizeof(unsigned short));
    unsigned short front = 0, rear = 0;

    for (unsigned short i = 0; i < N; i++) {
        AdjList* list = &graph->array[i];
        unsigned short cnt = list->count;
        unsigned short* vert = list->vertices;
        
        while (cnt--) {
            indegree[*vert++]++;
        }
    }

    for (unsigned short i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    unsigned short cnt = 0;
    while (front < rear) {
        unsigned short u = queue[front++];
        cnt++;

        AdjList* list = &graph->array[u];
        unsigned short edge_cnt = list->count;
        unsigned short* vert = list->vertices;
        
        while (edge_cnt--) {
            unsigned short v = *vert++;
            if (--indegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    free(indegree);
    free(queue);
    return cnt != N;
}

void free_graph(Graph* graph) {
    for (unsigned short i = 0; i < graph->V; i++) {
        free(graph->array[i].vertices);
    }
    free(graph->array);
    free(graph);
}

