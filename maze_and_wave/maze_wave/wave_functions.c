#include <stdio.h>
#include <stdlib.h>
#include "wave_functions.h"

int is_empty(int first) {
    return (first == -1);
}

int is_full(int last, int MAX_SIZE) {
    return (last == MAX_SIZE - 1);
}

void enqueue(int **queue, int *first, int *last, int point[2], int MAX_SIZE) {
    if (is_full(*last, MAX_SIZE)) {
        printf("Queue is full\n");
        return;
    }
    if (is_empty(*first)) {
        *first = 0;
    }
    (*last)++;
    queue[*last][0] = point[0];
    queue[*last][1] = point[1];
}

void dequeue(int **queue, int *first, int *last, int point[2]) {
    if (is_empty(*first)) {
        printf("Queue is empty\n");
        point[0] = -1;
        point[1] = -1;
        return;
    }
    point[0] = queue[*first][0];
    point[1] = queue[*first][1];
    (*first)++;
    if (*first > *last) {
        *first = *last = -1;
    }
}

void arr_reverse(int **arr, int N) {
    int temp[2];
    for (int i = 0; i < N / 2; i++) {
        temp[0] = arr[i][0];
        temp[1] = arr[i][1];

        arr[i][0] = arr[N - 1 - i][0];
        arr[i][1] = arr[N - 1 - i][1];

        arr[N - 1 - i][0] = temp[0];
        arr[N - 1 - i][1] = temp[1];
    }
}

int matrix_cmp(int **path, int point[2], int row_counter) {
    for (int i = 0; i < row_counter; i++) {
        if (path[i][0] == point[0] && path[i][1] == point[1]) {
            return 1;
        }
    }
    return 0;
}

char** read_matrix_from_file(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    *rows = 0;
    *cols = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file)) {
        (*rows)++;
        if (*cols == 0) {
            for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
                (*cols)++;
            }
        }
    }

    rewind(file);

    char** graph_matrix = (char**)malloc(*rows * sizeof(char*));
    for (int i = 0; i < *rows; i++) {
        graph_matrix[i] = (char*)malloc(*cols * sizeof(char));
    }

    int row = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        for (int col = 0; col < *cols; col++) {
            graph_matrix[row][col] = buffer[col];
        }
        row++;
    }

    fclose(file);
    return graph_matrix;
}

void matrix_value(char** graph_matrix, int** matrix, int start_position[2], int end_position[2], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (graph_matrix[i][j] == '#') {
                matrix[i][j] = -7;
            } else if (graph_matrix[i][j] == 'A') {
                matrix[i][j] = -1;
                start_position[0] = i;
                start_position[1] = j;
            } else if (graph_matrix[i][j] == 'B') {
                matrix[i][j] = -1;
                end_position[0] = i;
                end_position[1] = j;
            } else {
                matrix[i][j] = -1;
            }
        }
    }
}

int get_value(int** matrix, int rows, int cols, int row, int col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return matrix[row][col];
    }
    return -10;
}

void wave(int** matrix, int rows, int cols, int* start_position, int* end_position, int MAX_SIZE, int **queue, int *first, int *last) {
    int cell = get_value(matrix, rows, cols, start_position[0], start_position[1]);
    if (cell == -10 || cell == -7) {
        return;
    }

    matrix[start_position[0]][start_position[1]] = 0;
    enqueue(queue, first, last, start_position, MAX_SIZE);

    while (!is_empty(*first)) {
        int point[2];
        dequeue(queue, first, last, point);
        int row = point[0];
        int col = point[1];

        if (row == end_position[0] && col == end_position[1]) {
            break;
        }

        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++) {
            int new_row = row + directions[i][0];
            int new_col = col + directions[i][1];
            if (get_value(matrix, rows, cols, new_row, new_col) == -1) {
                matrix[new_row][new_col] = matrix[row][col] + 1;
                int current_point[2] = {new_row, new_col};
                enqueue(queue, first, last, current_point, MAX_SIZE);
            }
        }
    }
}

int get_path(int** matrix, int rows, int cols, int* start_position, int* end_position, int* row_counter, int MAX_SIZE, int **queue, int *first, int *last, int **path) {
    wave(matrix, rows, cols, start_position, end_position, MAX_SIZE, queue, first, last);
    int row = end_position[0];
    int col = end_position[1];

    if (matrix[row][col] <= -1) {
        return 0;
    }

    path[*row_counter][0] = row;
    path[*row_counter][1] = col;
    (*row_counter)++;

    while (row != start_position[0] || col != start_position[1]) {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++) {
            int new_row = row + directions[i][0];
            int new_col = col + directions[i][1];
            if (get_value(matrix, rows, cols, new_row, new_col) == matrix[row][col] - 1) {
                row = new_row;
                col = new_col;
                path[*row_counter][0] = row;
                path[*row_counter][1] = col;
                (*row_counter)++;
                break;
            }
        }
    }

    arr_reverse(path, *row_counter);
    return 1;
}

void print_final_path(int** matrix, int rows, int cols, int* start_position, int* end_position, int MAX_SIZE, int **queue, int *first, int *last, int **path) {
    int row_counter = 0;

    if (!get_path(matrix, rows, cols, start_position, end_position, &row_counter, MAX_SIZE, queue, first, last, path)) {
        printf("No path found\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int curr_point[2] = {i, j};

            if (i == start_position[0] && j == start_position[1]) {
                printf("@");
            } else if (i == end_position[0] && j == end_position[1]) {
                printf("$");
            } else if (matrix_cmp(path, curr_point, row_counter)) {
                printf("*");
            } else if (matrix[i][j] == -7) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}


