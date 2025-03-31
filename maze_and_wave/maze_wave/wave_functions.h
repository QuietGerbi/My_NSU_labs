#ifndef WAVE_FUNCTIONS_H
#define WAVE_FUNCTIONS_H

int is_empty(int first);
int is_full(int last, int MAX_SIZE);
void enqueue(int **queue, int *first, int *last, int point[2], int MAX_SIZE);
void dequeue(int **queue, int *first, int *last, int point[2]);
void arr_reverse(int **arr, int N);
int matrix_cmp(int **path, int point[2], int row_counter);
char** read_matrix_from_file(const char* filename, int* rows, int* cols);
void matrix_value(char** graph_matrix, int** matrix, int start_position[2], int end_position[2], int rows, int cols);
int get_value(int** matrix, int rows, int cols, int row, int col);
void wave(int** matrix, int rows, int cols, int* start_position, int* end_position, int MAX_SIZE, int **queue, int *first, int *last);
int get_path(int** matrix, int rows, int cols, int* start_position, int* end_position, int* row_counter, int MAX_SIZE, int **queue, int *first, int *last, int **path);
void print_final_path(int** matrix, int rows, int cols, int* start_position, int* end_position, int MAX_SIZE, int **queue, int *first, int *last, int **path);

#endif

