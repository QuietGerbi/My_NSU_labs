#include "constants.h"
#include "node_functions.h"
#include "bit_functions.h"
#include "constants.h"

HTNode* reconstruct_tree(BitFileReader* br) {
    int bit = read_bit(br);
    if (bit == 0) {
        uint8_t sym = read_byte(br);
        return make_leaf_node(sym, 0);
    } else if (bit == 1) {
        HTNode* left = reconstruct_tree(br);
        HTNode* right = reconstruct_tree(br);
        return make_internal_node(left, right);
    }
    return NULL;
}

int32_t huffman_main(int32_t arg_count, char** arg_values) {
    char operation;
    FILE* input_file;
    FILE* output_file;

    if (arg_count == 1) {
        input_file = fopen("in.txt", "rb");
        if (!input_file) return 0;
        if (fread(&operation, 1, 1, input_file) != 1) {
            fclose(input_file);
            return 0;
        }
        output_file = fopen("out.txt", "wb");
        if (!output_file) {
            fclose(input_file);
            return 0;
        }
    } else if (arg_count == 4) {
        if (strcmp(arg_values[1], "-c") == 0) {
            operation = 'c';
        } else if (strcmp(arg_values[1], "-d") == 0) {
            operation = 'd';
        } else {
            return 0;
        }
        input_file = fopen(arg_values[2], "rb");
        if (!input_file) {
            printf("Failed to open %s\n", arg_values[2]);
            return 0;
        }
        output_file = fopen(arg_values[3], "wb");
        if (!output_file) {
            printf("Failed to open %s\n", arg_values[3]);
            fclose(input_file);
            return 0;
        }
    } else {
        return 0;
    }

    if (operation == 'c') {
        if (arg_count == 4) fseek(input_file, 0, SEEK_SET);
        
        size_t freq_table[256] = {0};
        uint8_t current_byte;
        size_t total_bytes = 0;
        
        while (fread(&current_byte, 1, 1, input_file) == 1) {
            freq_table[current_byte]++;
            total_bytes++;
        }
        
        if (total_bytes == 0) {
            uint32_t zero = 0;
            fwrite(&zero, sizeof(uint32_t), 1, output_file);
            fclose(input_file);
            fclose(output_file);
            return 0;
        }
        
        HTNode* nodes[256];
        int node_count = 0;
        for (int i = 0; i < 256; i++) {
            if (freq_table[i] > 0) {
                nodes[node_count++] = make_leaf_node((uint8_t)i, freq_table[i]);
            }
        }
        
        while (node_count > 1) {
            int min1 = 0, min2 = 1;
            if (nodes[min1]->count > nodes[min2]->count) {
                min1 = 1; min2 = 0;
            }
            
            for (int i = 2; i < node_count; i++) {
                if (nodes[i]->count < nodes[min1]->count) {
                    min2 = min1;
                    min1 = i;
                } else if (nodes[i]->count < nodes[min2]->count) {
                    min2 = i;
                }
            }
            
            HTNode* new_node = make_internal_node(nodes[min1], nodes[min2]);
            nodes[min1] = new_node;
            nodes[min2] = nodes[--node_count];
        }
        
        HTNode* huffman_tree = nodes[0];
        
        uint32_t orig_length = (uint32_t)total_bytes;
        fwrite(&orig_length, sizeof(uint32_t), 1, output_file);
        
        BitFileWriter writer;
        setup_bit_writer(&writer, output_file);
        serialize_tree(huffman_tree, &writer);
        
        HuffCode code_table[256] = {0};
        HuffCode empty_code = {0};
        generate_codes(huffman_tree, empty_code, code_table);
        
        if (arg_count == 1) fseek(input_file, 1, SEEK_SET);
        else fseek(input_file, 0, SEEK_SET);
        
        while (fread(&current_byte, 1, 1, input_file) == 1) {
            HuffCode code = code_table[current_byte];
            for (int j = 0; j < code.bit_count; j++) {
                int byte_idx = j / 8;
                int bit_pos = j % 8;
                int bit = (code.code_bytes[byte_idx] >> (7 - bit_pos)) & 1;
                write_bit(&writer, bit);
            }
        }
        
        flush_bit_writer(&writer);
        destroy_tree(huffman_tree);
        
    } else if (operation == 'd') {
        if (arg_count == 4) fseek(input_file, 0, SEEK_SET);
        
        uint32_t orig_length;
        if (fread(&orig_length, sizeof(uint32_t), 1, input_file) != 1) {
            fclose(input_file);
            fclose(output_file);
            return 0;
        }
        
        if (orig_length == 0) {
            fclose(input_file);
            fclose(output_file);
            return 0;
        }
        
        BitFileReader reader;
        setup_bit_reader(&reader, input_file);
        HTNode* huffman_tree = reconstruct_tree(&reader);
        
        if (!huffman_tree) {
            fclose(input_file);
            fclose(output_file);
            return 0;
        }
        
        if (!huffman_tree->lc && !huffman_tree->rc) {
            uint8_t sym = huffman_tree->symbol;
            for (size_t i = 0; i < orig_length; i++) {
                fwrite(&sym, 1, 1, output_file);
            }
        } else {
            size_t decoded = 0;
            HTNode* current = huffman_tree;
            while (decoded < orig_length) {
                int bit = read_bit(&reader);
                if (bit == -1) break;
                
                current = bit ? current->rc : current->lc;
                if (!current) break;
                
                if (!current->lc && !current->rc) {
                    fwrite(&current->symbol, 1, 1, output_file);
                    decoded++;
                    current = huffman_tree;
                }
            }
        }
        
        destroy_tree(huffman_tree);
    }
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}




