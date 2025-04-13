#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H
#include <stdint.h>

int32_t buf_cmp( __u_char *buf1,  __u_char *buf2, int32_t count, int32_t zero_point);
void preprocess_boyer_moore(__u_char *sub_str, int32_t *boyer_moore, int32_t needle_len);
void handle_buffer(__u_char **main_str, int32_t *curr_len, int32_t *shift, int32_t *i);
void search_pattern(__u_char *main_str, __u_char *sub_str, int32_t *boyer_moore, int32_t needle_len, int32_t *curr_len, int32_t *shift, int32_t *i);

#endif


