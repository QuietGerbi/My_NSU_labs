#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "constants.h"
#include "node.h"

void init_pool(pool* p) {
    p->nodes = malloc(sizeof(node) * POOL_SIZE);
    p->index = 0;
    if (!p->nodes) return;
}

node* alloc_node(pool* p, int32_t k) {
    if (p->index >= POOL_SIZE) {
        printf("Bad input\n");
        return 0;
    }
    node* n = &p->nodes[p->index++];
    n->key = k;
    n->height = 1;
    n->left = n->right = NULL;
    return n;
}

uint8_t height(node* p) {
    return p ? p->height : 0;
}

int32_t bfactor(node* p) {
    return height(p->right) - height(p->left);
}

void fixheight(node* p) {
    uint8_t hl = height(p->left);
    uint8_t hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) {
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) {
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p, int8_t** rotations, int32_t* count, int32_t* capacity) {
    fixheight(p);
    int32_t balance_factor = bfactor(p);
    
    if (balance_factor == 2) {
        if (bfactor(p->right) < 0) {
            p->right = rotateright(p->right);
            if (*count >= *capacity) {
                *capacity = (*capacity == 0) ? 8 : *capacity * 2;
                int8_t* new_rotations = realloc(*rotations, *capacity * sizeof(int8_t));
                if (!new_rotations) return 0;
                *rotations = new_rotations;
            }
            (*rotations)[(*count)++] = 3; // BL
            p = rotateleft(p);
        } else {
            if (*count >= *capacity) {
                *capacity = (*capacity == 0) ? 8 : *capacity * 2;
                int8_t* new_rotations = realloc(*rotations, *capacity * sizeof(int8_t));
                if (!new_rotations) return 0;
                *rotations = new_rotations;
            }
            (*rotations)[(*count)++] = 1; // SL
            p = rotateleft(p);
        }
    } else if (balance_factor == -2) {
        if (bfactor(p->left) > 0) {
            p->left = rotateleft(p->left);
            if (*count >= *capacity) {
                *capacity = (*capacity == 0) ? 8 : *capacity * 2;
                int8_t* new_rotations = realloc(*rotations, *capacity * sizeof(int8_t));
                if (!new_rotations) return 0;
                *rotations = new_rotations;
            }
            (*rotations)[(*count)++] = 4; // BR
            p = rotateright(p);
        } else {
            if (*count >= *capacity) {
                *capacity = (*capacity == 0) ? 8 : *capacity * 2;
                int8_t* new_rotations = realloc(*rotations, *capacity * sizeof(int8_t));
                if (!new_rotations) return 0;
                *rotations = new_rotations;
            }
            (*rotations)[(*count)++] = 2; // SR
            p = rotateright(p);
        }
    }
    return p;
}

node* insert(node* root, int32_t k, pool* p, int8_t** rotations, int32_t* count, int32_t* capacity) {
    node* new_node = alloc_node(p, k);
    if (!root) return new_node;

    node* current = root;
    node* stack[30];
    int top = -1;

    while (current) {
        stack[++top] = current;
        if (k < current->key) current = current->left;
        else if (k > current->key) current = current->right;
        else return root;
    }

    current = new_node;
    if (top >= 0) {
        if (k < stack[top]->key) stack[top]->left = current;
        else stack[top]->right = current;
    }

    while (top >= 0) {
        current = stack[top--];
        current = balance(current, rotations, count, capacity);
        if (top >= 0) {
            if (current->key < stack[top]->key) stack[top]->left = current;
            else stack[top]->right = current;
        } else {
            root = current;
        }
    }
    return root;
}

void free_tree(pool* p) {
    free(p->nodes);
}

int32_t is_valid(int32_t N) {
    return (N >= 0 && N <= POOL_SIZE) ? 0 : -1;
}

const char* rotation_to_string(int8_t type) {
    switch (type) {
        case 1: return "SL";
        case 2: return "SR";
        case 3: return "BL";
        case 4: return "BR";
        default: return "NONE";
    }
}

void print_leaf_paths(node* root, char* path, int depth) {
    if (root == NULL) return;
    
    if (root->left == NULL && root->right == NULL) {
        path[depth] = '\0';
        printf("%s %d\n", path, root->key);
        return;
    }
    
    if (root->left) {
        path[depth] = 'L';
        print_leaf_paths(root->left, path, depth + 1);
    }
    
    if (root->right) {
        path[depth] = 'R';
        print_leaf_paths(root->right, path, depth + 1);
    }
}

