#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "boyer_moore.h"

int main() {
    uint8_t sub_str[100];
    uint8_t *main_str = (uint8_t *)malloc(1001); 
    
    if (fgets((char *)sub_str, 100, stdin) == NULL) {
        free(main_str);
        return 0;
    }

    size_t len = strlen((char *)sub_str);
    if (len > 0 && sub_str[len - 1] == '\n') {
        sub_str[len - 1] = '\0';
    }

    int32_t needle_len = strlen((char *)sub_str);
    if (needle_len == 0) {
        free(main_str);
        return 0;
    }

    int32_t curr_len = fread(main_str, sizeof(uint8_t), 1000, stdin);
    if (curr_len <= 0) {
        free(main_str);
        return 0;
    }
    main_str[curr_len] = '\0';

    int32_t shift = 0;
    int32_t boyer_moore[256];
    int32_t i = 0;

    preprocess_boyer_moore(sub_str, boyer_moore, needle_len);
    search_pattern(main_str, sub_str, boyer_moore, needle_len, &curr_len, &shift, &i);

    free(main_str);
    return 0;
}

