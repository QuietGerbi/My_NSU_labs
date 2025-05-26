#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "constants.h"

HTNode* reconstruct_tree(BitFileReader* br);
int32_t huffman_main(int32_t arg_count, char** arg_values);

#endif



