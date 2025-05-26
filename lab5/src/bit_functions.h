#ifndef BIT_FUNCTIONS_H
#define BIT_FUNCTIONS_H
#include "constants.h"

void add_bit_to_code(HuffCode* hc, int bit);
void generate_codes(const HTNode* node, HuffCode current, HuffCode* table);
void setup_bit_writer(BitFileWriter* bw, FILE* f);
void write_bit(BitFileWriter* bw, int bit);
void write_byte(BitFileWriter* bw, uint8_t byte);
void flush_bit_writer(BitFileWriter* bw);
void serialize_tree(const HTNode* node, BitFileWriter* bw);
void setup_bit_reader(BitFileReader* br, FILE* f);
int read_bit(BitFileReader* br);
uint8_t read_byte(BitFileReader* br);

#endif



