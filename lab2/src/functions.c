#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int is_valid(char* arr) {
    char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for (int i = 0; arr[i] != '\0' && arr[i] != '\n'; i++) {
        short repeats = 0;
        short count = 0;

        for (int k=0;k<10;k++){
            if (arr[i]==digits[k]){
                count++;
            }
        }

        if (count==0) return -1;

        for (int j = 0; arr[j] != '\0' && arr[j] != '\n'; j++) {
            if (arr[i] == arr[j]) {
                repeats++;
            }
            if (repeats >= 2) {
                return -1;
            }
        }
    }
    return 1;
}

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(char* str, int start, int end) {
    while (start < end) {
        swap(&str[start], &str[end]);
        start++;
        end--;
    }
}

int next_permutation(char* str) {
    int len = strlen(str);
    if (len <= 1) return 0;
    
    int i = len - 2;
    while (i >= 0 && str[i] >= str[i + 1]) i--;
    if (i < 0) return 0;
    
    int j = len - 1;
    while (str[j] <= str[i]) j--;
    swap(&str[i], &str[j]);
    reverse(str, i + 1, len - 1);
    return 1;
}



