#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H
#include <stdint.h>

int32_t buf_cmp( uint8_t *buf1,  uint8_t *buf2, int32_t count, int32_t zero_point);
void preprocess_boyer_moore(uint8_t *sub_str, int32_t *boyer_moore, int32_t needle_len);
void handle_buffer(uint8_t **main_str, int32_t *curr_len, int32_t *shift, int32_t *i);
void search_pattern(uint8_t *main_str, uint8_t *sub_str, int32_t *boyer_moore, int32_t needle_len, int32_t *curr_len, int32_t *shift, int32_t *i);

#endif


