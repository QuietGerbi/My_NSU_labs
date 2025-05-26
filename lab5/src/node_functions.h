#ifndef NODE_FUNCTIONS_H
#define NODE_FUNCTIONS_H

#include "constants.h"

HTNode* make_leaf_node(uint8_t sym, size_t cnt);
HTNode* make_internal_node(HTNode* a, HTNode* b);
void destroy_tree(HTNode* root);


#endif



