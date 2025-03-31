#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void swap(int* a, int* b);
void arr_input(int* arr, int n);
int median_of_three(int* arr, int low, int high);
void three_way_partition(int* arr, int low, int high, int* left_pivot, int* right_pivot);
void quick_sort(int* arr, int low, int high);

#endif

