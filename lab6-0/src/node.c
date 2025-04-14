#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "constants.h"
#include "node.h"

node* create_node(int32_t k) {
    node* p = (node*)malloc(sizeof(node));
    p->key = k;
    p->height = 1;
    p->left = p->right = NULL;
    return p;
}

int8_t height(node* p) {
    return p ? p->height : 0;
}

int32_t bfactor(node* p) {
    return height(p->right) - height(p->left);
}

void fixheight(node* p) {
    int8_t hl = height(p->left);
    int8_t hr = height(p->right);
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

node* balance(node* p, int16_t** rotations, int32_t* count, int32_t* capacity) {
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0) {
            p->right = rotateright(p->right);
            
            if (*count >= *capacity) {
                *capacity *= (*capacity/2);
                *rotations = realloc(*rotations, *capacity * sizeof(short));
                if (!*rotations) {
                return 0;
            }
            }
            (*rotations)[(*count)++] = 3; // BL
            return rotateleft(p);
        }

        if (*count >= *capacity) {
            *capacity *= (*capacity/2);
            *rotations = realloc(*rotations, *capacity * sizeof(short));
            if (!*rotations) {
                return 0;
            }
        }
        (*rotations)[(*count)++] = 1; // SL
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0) {
            p->left = rotateleft(p->left);

            if (*count >= *capacity) {
                *capacity *= (*capacity/2);
                *rotations = realloc(*rotations, *capacity * sizeof(short));
                if (!*rotations) {
                    return 0;
                }
            }
            (*rotations)[(*count)++] = 4; // BR
            return rotateright(p);
        }

        if (*count >= *capacity) {
            *capacity *= (*capacity/2);
            *rotations = realloc(*rotations, *capacity * sizeof(short));
            if (!*rotations) {
                return 0;
            }
        }
        (*rotations)[(*count)++] = 2; // SR
        return rotateright(p);
    }
    return p;
}

node* insert(node* p, int k, int16_t** rotations, int32_t* count, int32_t* capacity) {
    if (!p) return create_node(k);
    if (k < p->key)
        p->left = insert(p->left, k, rotations, count, capacity);
    else
        p->right = insert(p->right, k, rotations, count, capacity);
    return balance(p, rotations, count, capacity);
}

void free_tree(node* p) {
    if (p) {
        free_tree(p->left);
        free_tree(p->right);
        free(p);
    }
}

int32_t is_valid(int32_t N) {
    if (N < 0 || N > 2000000) {
        return -1;
    }     
    return 0;
}

const char* rotation_to_string(int16_t type) {
    switch (type) {
        case 1: return "SL";
        case 2: return "SR";
        case 3: return "BL";
        case 4: return "BR";
        default: return "NONE";
    }
}

void PrintPaths(node* root, int8_t* path, int32_t depth) {
    if (root == NULL) return;
    
    if (root->left == NULL && root->right == NULL) {
        path[depth] = '\0';
        printf("%s %d\n", path, root->key);
        return;
    }
    
    if (root->left != NULL) {
        path[depth] = 'L';
        PrintPaths(root->left, path, depth + 1);
    }
    
    if (root->right != NULL) {
        path[depth] = 'R';
        PrintPaths(root->right, path, depth + 1);
    }
}

void in_order_traversal(node* root) {
    if (root == NULL) return;
    
    in_order_traversal(root->left);
    printf("%d ", root->key);
    in_order_traversal(root->right);
}


