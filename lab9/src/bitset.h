#ifndef BITSET_H
#define BITSET_H

#include "constants.h"

Bitset* init_bitset();
void free_bitset(Bitset* bs);
void set_bitset_bit(Bitset* bs, int index);
int get_bitset_bit(const Bitset* bs, int index);

#endif



