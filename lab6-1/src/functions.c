#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "functions.h"

void initialize_pool(NodePool* pool) {
    pool->node_pool = (Node*)malloc(MAX_NODES * sizeof(Node));
    if (!pool->node_pool) {
        return;
    }
    pool->pool_index = 0;
}

int32_t create_node(NodePool* pool, int32_t key) {
    if (pool->pool_index >= MAX_NODES) {
        return 0;
    }
    Node* node = &pool->node_pool[pool->pool_index];
    node->key = key;
    node->left = -1;
    node->right = -1;
    node->parent_color.parent = -1;
    node->parent_color.color = RED;
    return pool->pool_index++;
}

void rotate_left(int32_t* root, NodePool* pool, int32_t x) {
    Node* nodes = pool->node_pool;
    int32_t y = nodes[x].right;
    nodes[x].right = nodes[y].left;
    
    if (nodes[y].left != -1) {
        nodes[nodes[y].left].parent_color.parent = x;
    }
    
    nodes[y].parent_color.parent = nodes[x].parent_color.parent;
    
    if (nodes[x].parent_color.parent == -1) {
        *root = y;
    } else if (x == nodes[nodes[x].parent_color.parent].left) {
        nodes[nodes[x].parent_color.parent].left = y;
    } else {
        nodes[nodes[x].parent_color.parent].right = y;
    }
    
    nodes[y].left = x;
    nodes[x].parent_color.parent = y;
}

void rotate_right(int32_t* root, NodePool* pool, int32_t x) {
    Node* nodes = pool->node_pool;
    int32_t y = nodes[x].left;
    nodes[x].left = nodes[y].right;
    
    if (nodes[y].right != -1) {
        nodes[nodes[y].right].parent_color.parent = x;
    }
    
    nodes[y].parent_color.parent = nodes[x].parent_color.parent;
    
    if (nodes[x].parent_color.parent == -1) {
        *root = y;
    } else if (x == nodes[nodes[x].parent_color.parent].right) {
        nodes[nodes[x].parent_color.parent].right = y;
    } else {
        nodes[nodes[x].parent_color.parent].left = y;
    }
    
    nodes[y].right = x;
    nodes[x].parent_color.parent = y;
}

void insert_fixup(int32_t* root, NodePool* pool, int32_t n) {
    Node* nodes = pool->node_pool;
    while (nodes[n].parent_color.parent != -1 && 
           nodes[nodes[n].parent_color.parent].parent_color.color == RED) {
        int32_t g = nodes[nodes[n].parent_color.parent].parent_color.parent;
        
        if (nodes[n].parent_color.parent == nodes[g].left) {
            int32_t u = nodes[g].right;
            
            if (u != -1 && nodes[u].parent_color.color == RED) {
                nodes[nodes[n].parent_color.parent].parent_color.color = BLACK;
                nodes[u].parent_color.color = BLACK;
                nodes[g].parent_color.color = RED;
                n = g;
            } else {
                if (n == nodes[nodes[n].parent_color.parent].right) {
                    n = nodes[n].parent_color.parent;
                    rotate_left(root, pool, n);
                }
                nodes[nodes[n].parent_color.parent].parent_color.color = BLACK;
                nodes[g].parent_color.color = RED;
                rotate_right(root, pool, g);
            }
        } else {
            int32_t u = nodes[g].left;
            
            if (u != -1 && nodes[u].parent_color.color == RED) {
                nodes[nodes[n].parent_color.parent].parent_color.color = BLACK;
                nodes[u].parent_color.color = BLACK;
                nodes[g].parent_color.color = RED;
                n = g;
            } else {
                if (n == nodes[nodes[n].parent_color.parent].left) {
                    n = nodes[n].parent_color.parent;
                    rotate_right(root, pool, n);
                }
                nodes[nodes[n].parent_color.parent].parent_color.color = BLACK;
                nodes[g].parent_color.color = RED;
                rotate_left(root, pool, g);
            }
        }
    }
    nodes[*root].parent_color.color = BLACK;
}

int32_t get_black_height(int32_t root, NodePool* pool) {
    if (root==-1) return 0;
    Node* nodes = pool->node_pool;
    int32_t height = 0;
    int32_t current = root;
    while (current != -1) {
        if (nodes[current].parent_color.color == BLACK) height++;
        current = nodes[current].left;
    }
    return height + 1;
}


