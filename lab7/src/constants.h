#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef struct {
    unsigned short* vertices;
    unsigned short count;
    unsigned short capacity;
} AdjList;

typedef struct {
    unsigned short V;
    AdjList* array;
} Graph;

#endif

