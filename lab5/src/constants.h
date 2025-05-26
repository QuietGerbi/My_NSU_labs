#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct HuffmanTreeNode {
    size_t count;
    uint8_t symbol;
    struct HuffmanTreeNode* lc;
    struct HuffmanTreeNode* rc;
} HTNode;

typedef struct {
    int32_t bit_count;
    uint8_t code_bytes[6];
} HuffCode;

typedef struct {
    FILE* src;
    uint8_t buffer;
    int32_t bit_counter;
} BitFileReader;

typedef struct {
    FILE* dest;
    uint8_t buffer;
    int32_t bit_counter;
} BitFileWriter;



#endif



