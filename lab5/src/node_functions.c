#include "constants.h"

HTNode* make_leaf_node(uint8_t sym, size_t cnt) {
    HTNode* n = (HTNode*)calloc(1, sizeof(HTNode));
    n->count = cnt;
    n->symbol = sym;
    return n;
}

HTNode* make_internal_node(HTNode* a, HTNode* b) {
    HTNode* n = (HTNode*)calloc(1, sizeof(HTNode));
    n->count = a->count + b->count;
    n->lc = a;
    n->rc = b;
    return n;
}

void destroy_tree(HTNode* root) {
    if (!root) return;
    destroy_tree(root->lc);
    destroy_tree(root->rc);
    free(root);
}



