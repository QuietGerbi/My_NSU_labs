#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_NODES 2000000

typedef enum { RED = 0, BLACK = 1 } Color;

typedef struct {
    int32_t parent : 24;
    Color color : 1;
} ParentAndColor;

typedef struct {
    int32_t key;
    ParentAndColor parent_color;
    int32_t left;
    int32_t right;
} Node;

typedef struct {
    Node* node_pool;
    int32_t pool_index;
} NodePool;

void initialize_pool(NodePool* pool);
int32_t create_node(NodePool* pool, int32_t key);
void rotate_left(int32_t* root, NodePool* pool, int32_t x);
void rotate_right(int32_t* root, NodePool* pool, int32_t x);
void insert_fixup(int32_t* root, NodePool* pool, int32_t n);
int32_t get_black_height(int32_t root, NodePool* pool);

#endif


