#include "wave_functions.h" 
#include "maze_gen_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    // Блок вызова функций для генерации лабиринта.
    srand(time(NULL));
    int start = 5;
    int end = 20;

    const char* filename = "maze.txt";

    int HEIGHT = rand() % (end - start + 1) + start;
    int WIDTH = rand() % (end - start + 1) + start;;

    char maze[HEIGHT][WIDTH];
    initialize_maze(HEIGHT, WIDTH, maze);

    int start_x = rand() % ((WIDTH/2)+1), start_y = rand() % ((HEIGHT/2)+1);
    int end_x = rand() % (((WIDTH - 1) - (WIDTH/2)) + (WIDTH/2)), end_y = rand() % (((HEIGHT - 1) - (HEIGHT/2)) + (HEIGHT/2));

    drunkard_walk(HEIGHT, WIDTH, maze, start_x, start_y, end_x, end_y);
    write_maze(HEIGHT, WIDTH, maze, filename);

    // Блок вызова функций для обхода лабиринта
    int rows, cols;

    char** graph_matrix = read_matrix_from_file(filename, &rows, &cols);
    if (!graph_matrix) {
        return 1;
    }

    int MAX_SIZE = rows * cols;

    int **queue = (int**)malloc(MAX_SIZE * sizeof(int*));
    int **path = (int**)malloc(MAX_SIZE * sizeof(int*));
    for (int i = 0; i < MAX_SIZE; i++) {
        queue[i] = (int*)malloc(2 * sizeof(int));
        path[i] = (int*)malloc(2 * sizeof(int));
    }

    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    int start_position[2];
    int end_position[2];

    matrix_value(graph_matrix, matrix, start_position, end_position, rows, cols);

    int first = -1;
    int last = -1;

    print_final_path(matrix, rows, cols, start_position, end_position, MAX_SIZE, queue, &first, &last, path);

    return 0;
}





