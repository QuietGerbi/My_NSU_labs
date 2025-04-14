#ifndef NODE_H
#define NODE_H
#include "constants.h"

node* create_node(int32_t k);
int8_t height(node* p);
int32_t bfactor(node* p);
void fixheight(node* p);
node* rotateright(node* p);
node* rotateleft(node* q);
node* balance(node* p, int16_t** rotations, int32_t* count, int32_t* capacity);
node* insert(node* p, int k, int16_t** rotations, int32_t* count, int32_t* capacity);
void free_tree(node* p);
int32_t is_valid(int32_t N);
const char* rotation_to_string(int16_t type);
void PrintPaths(node* root, int8_t* path, int32_t depth);
void in_order_traversal(node* root);

#endif


