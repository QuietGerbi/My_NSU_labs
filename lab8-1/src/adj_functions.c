#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "adj_functions.h"
#include "constants.h"

AdjList* create_adj_list(int N) {
    AdjList* adj_list = (AdjList*)malloc((N + 1) * sizeof(AdjList));
    if (!adj_list) {
        return NULL;
    }
    
    memset(adj_list, 0, (N + 1) * sizeof(AdjList));
    for (int i = 0; i <= N; i++) {
        adj_list[i].size = 0;
        adj_list[i].capacity = 16;
        adj_list[i].edges = (Adjacency*)malloc(adj_list[i].capacity * sizeof(Adjacency));
        if (!adj_list[i].edges) {
            for (int j = 0; j <= i; j++) {
                if (adj_list[j].edges) {
                    free(adj_list[j].edges);
                }
            }
            free(adj_list);
            return NULL;
        }
    }
    return adj_list;
}

void add_edge(AdjList* adj_list, int u, int v, int weight) {
    if (adj_list[u].size >= adj_list[u].capacity) {
        adj_list[u].capacity *= 2;
        Adjacency* temp = (Adjacency*)realloc(adj_list[u].edges, adj_list[u].capacity * sizeof(Adjacency));
        if (!temp) return;
        adj_list[u].edges = temp;
    }
    adj_list[u].edges[adj_list[u].size++] = (Adjacency){v, weight};

    if (adj_list[v].size >= adj_list[v].capacity) {
        adj_list[v].capacity *= 2;
        Adjacency* temp = (Adjacency*)realloc(adj_list[v].edges, adj_list[v].capacity * sizeof(Adjacency));
        if (!temp) return;
        adj_list[v].edges = temp;
    }
    adj_list[v].edges[adj_list[v].size++] = (Adjacency){u, weight};
}

void free_adj_list(AdjList* adj_list, int N) {
    if (!adj_list) return;
    
    for (int i = 0; i <= N; i++) {
        if (adj_list[i].edges) {
            free(adj_list[i].edges);
        }
    }
    free(adj_list);
}


