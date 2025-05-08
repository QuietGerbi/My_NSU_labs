#include "bitset.h"
#include "html.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

Bitset* init_bitset() {
    Bitset* bs = (Bitset*)malloc(sizeof(Bitset));
    if (bs){
        memset(bs->bits, 0, sizeof(bs->bits));
    };
    return bs;
}

void free_bitset(Bitset* bs) {
    if (bs){
        free(bs);
    }
}

void set_bitset_bit(Bitset* bs, int index) {
    if (bs && index > 0) {
        index--;
        bs->bits[index / 32] |= (1 << (index % 32));
    }
}

int get_bitset_bit(const Bitset* bs, int index) {
    if (bs && index > 0) {
        index--;
        return (bs->bits[index / 32] & (1 << (index % 32))) != 0;
    }
    return 0;
}




