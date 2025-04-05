#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_N 5000
#define MAX_WEIGHT INT_MAX

typedef struct {
    int dest;
    int weight;
} Adjacency;

typedef struct {
    Adjacency* edges;
    int size;
    int capacity;
} AdjList;

typedef struct {
    int u, v, weight;
} Edge;

#endif


