#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void arr_input(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("bad input\n");
            return;
        }
    }
}

int median_of_three(int* arr, int low, int high) {
    int mid = low + (high - low) / 2;
    
    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);
    
    return mid;
}

void three_way_partition(int* arr, int low, int high, int* left_pivot, int* right_pivot) {
    int pivot_idx = median_of_three(arr, low, high);
    int pivot = arr[pivot_idx];
    
    swap(&arr[pivot_idx], &arr[low]);
    
    int i = low;
    int lt = low;
    int gt = high;
    
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(&arr[i], &arr[lt]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            swap(&arr[i], &arr[gt]);
            gt--;
        } else {
            i++;
        }
    }
    
    *left_pivot = lt;
    *right_pivot = gt;
}

void quick_sort(int* arr, int low, int high) {
    while (low < high) {
        int left_pivot, right_pivot;
        three_way_partition(arr, low, high, &left_pivot, &right_pivot);
        
        if (left_pivot - low < high - right_pivot) {
            quick_sort(arr, low, left_pivot - 1);
            low = right_pivot + 1;
        } else {
            quick_sort(arr, right_pivot + 1, high);
            high = left_pivot - 1;
        }
    }
}

