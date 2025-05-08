#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdint.h>

#define POOL_SIZE 2000000

typedef struct node {
    int32_t key;
    uint8_t height;
    struct node* left;
    struct node* right;
} node;

typedef struct pool {
    node* nodes;
    size_t index;
} pool;

#endif


