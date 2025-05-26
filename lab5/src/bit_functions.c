#include "constants.h"

void add_bit_to_code(HuffCode* hc, int bit) {
    int byte_pos = hc->bit_count / 8;
    int bit_pos = hc->bit_count % 8;
    if (!bit_pos) hc->code_bytes[byte_pos] = 0;
    if (bit) hc->code_bytes[byte_pos] |= (1 << (7 - bit_pos));
    hc->bit_count++;
}

void generate_codes(const HTNode* node, HuffCode current, HuffCode* table) {
    if (!node->lc && !node->rc) {
        table[node->symbol] = current;
    } else {
        HuffCode left = current;
        add_bit_to_code(&left, 0);
        generate_codes(node->lc, left, table);
        HuffCode right = current;
        add_bit_to_code(&right, 1);
        generate_codes(node->rc, right, table);
    }
}

void setup_bit_writer(BitFileWriter* bw, FILE* f) {
    bw->dest = f;
    bw->buffer = 0;
    bw->bit_counter = 0;
}

void write_bit(BitFileWriter* bw, int bit) {
    if (bw->bit_counter == 8) {
        fwrite(&bw->buffer, 1, 1, bw->dest);
        bw->buffer = 0;
        bw->bit_counter = 0;
    }
    if (bit) bw->buffer |= (1 << (7 - bw->bit_counter));
    bw->bit_counter++;
}

void write_byte(BitFileWriter* bw, uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        write_bit(bw, (byte >> i) & 1);
    }
}

void flush_bit_writer(BitFileWriter* bw) {
    if (bw->bit_counter > 0) {
        fwrite(&bw->buffer, 1, 1, bw->dest);
        bw->buffer = 0;
        bw->bit_counter = 0;
    }
}

void serialize_tree(const HTNode* node, BitFileWriter* bw) {
    if (!node->lc && !node->rc) {
        write_bit(bw, 0);
        write_byte(bw, node->symbol);
    } else {
        write_bit(bw, 1);
        serialize_tree(node->lc, bw);
        serialize_tree(node->rc, bw);
    }
}

void setup_bit_reader(BitFileReader* br, FILE* f) {
    br->src = f;
    br->buffer = 0;
    br->bit_counter = 8;
}

int read_bit(BitFileReader* br) {
    if (br->bit_counter == 8) {
        if (fread(&br->buffer, 1, 1, br->src) != 1) return -1;
        br->bit_counter = 0;
    }
    int bit = (br->buffer >> (7 - br->bit_counter)) & 1;
    br->bit_counter++;
    return bit;
}

uint8_t read_byte(BitFileReader* br) {
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
        int bit = read_bit(br);
        if (bit == -1) break;
        byte = (byte << 1) | bit;
    }
    return byte;
}



