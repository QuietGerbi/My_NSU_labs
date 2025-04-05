#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_function.h"
#include "constants.h"

#define BUFFER_SIZE 8192

void topological_sort(unsigned short N, Graph* graph) {
    unsigned short* indegree = calloc(N, sizeof(unsigned short));
    unsigned short* queue = malloc(N * sizeof(unsigned short));
    unsigned short front = 0, rear = 0;
    char buffer[BUFFER_SIZE];
    char* buf_ptr = buffer;

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

    while (front < rear) {
        unsigned short u = queue[front++];
        
        int bytes = sprintf(buf_ptr, "%d ", u + 1);
        buf_ptr += bytes;
        
        if (buf_ptr - buffer > BUFFER_SIZE - 20) {
            *buf_ptr = '\0';
            fputs(buffer, stdout);
            buf_ptr = buffer;
        }

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

    if (buf_ptr != buffer) {
        *buf_ptr = '\0';
        fputs(buffer, stdout);
    }
    printf("\n");

    free(indegree);
    free(queue);
}
