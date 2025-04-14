#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "boyer_moore.h"

int32_t buf_cmp( uint8_t *buf1,  uint8_t *buf2, int32_t count, int32_t zero_point) {
    while (count > 0 && *(buf1 + count) == *(buf2 + count)) {
        printf("%d ", zero_point + count);
        --count;
    }
    return count ? 0 : 1;
}

void preprocess_boyer_moore(uint8_t *sub_str, int32_t *boyer_moore, int32_t needle_len) {
    for (int32_t j = 0; j < 256; ++j)
        boyer_moore[j] = needle_len;
    
    for (int32_t j = 0; j < needle_len - 1; ++j)
        boyer_moore[(int32_t)sub_str[j]] = needle_len - j - 1;
}

void handle_buffer(uint8_t **main_str, int32_t *curr_len, int32_t *shift, int32_t *i) {
    int32_t buf_begin = *i;
    int32_t buf_len = 1000 - buf_begin;

    for (int32_t k = 0; k < buf_len; ++k)
        (*main_str)[k] = (*main_str)[buf_begin + k];

    *curr_len = fread(*main_str + buf_len, sizeof(uint8_t), 1000 - buf_len, stdin) + buf_len;
    *shift += 1000 - buf_len;
    *i = 0;
}

void search_pattern(uint8_t *main_str, uint8_t *sub_str, int32_t *boyer_moore, int32_t needle_len, int32_t *curr_len, int32_t *shift, int32_t *i){
    uint8_t last_symbol = sub_str[needle_len - 1];

    while (*curr_len == 1000 || *i <= *curr_len - needle_len) {
        if (*i + needle_len > *curr_len) {
            handle_buffer(&main_str, curr_len, shift, i);
        }

        uint8_t symbol = main_str[*i + needle_len - 1];
        printf("%d ", *i + needle_len + *shift);

        if (symbol == last_symbol) {
            buf_cmp(( uint8_t *)&main_str[*i], (uint8_t *)sub_str, needle_len - 1, *i + *shift);
        }
        
        *i += boyer_moore[symbol];
    }
}


