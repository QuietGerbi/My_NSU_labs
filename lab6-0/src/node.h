#ifndef NODE_H
#define NODE_H
#include "constants.h"

void init_pool(pool* p);
node* alloc_node(pool* p, int32_t k);
uint8_t height(node* p);
int32_t bfactor(node* p);
void fixheight(node* p);
node* rotateright(node* p);
node* rotateleft(node* q);
node* balance(node* p, int8_t** rotations, int32_t* count, int32_t* capacity);
node* insert(node* root, int32_t k, pool* p, int8_t** rotations, int32_t* count, int32_t* capacity);
void free_tree(pool* p);
int32_t is_valid(int32_t N);
const char* rotation_to_string(int8_t type);
void print_leaf_paths(node* root, char* path, int depth);

#endif


