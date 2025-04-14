#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdint.h>

typedef struct node {
    int32_t key;
    __u_char height;
    struct node* left;
    struct node* right;
} node;

#endif


