#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    int n;
    if (scanf("%d", &n)!=1){
        printf("bad input!\n");
        return 0;
    };

    int* arr = (int*)malloc(n*sizeof(int));
    arr_input(arr, n);
    quick_sort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}


