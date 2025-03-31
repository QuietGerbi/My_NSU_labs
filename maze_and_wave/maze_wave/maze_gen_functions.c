#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze_gen_functions.h"

#define WALL '#'
#define PATH '.'
#define START 'A'
#define END 'B'

typedef struct {
    int dx;
    int dy;
} Direction;

Direction directions[] = {
    {0, -1},  // UP
    {0, 1},   // DOWN
    {-1, 0},  // LEFT
    {1, 0}    // RIGHT
};


void initialize_maze(int HEIGHT, int WIDTH, char maze[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze[y][x] = WALL;
        }
    }
}


int is_within_bounds(int HEIGHT, int WIDTH, int x, int y) {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

void drunkard_walk(int HEIGHT, int WIDTH, char maze[HEIGHT][WIDTH], int start_x, int start_y, int end_x, int end_y) {
    int x = start_x;
    int y = start_y;
    maze[y][x] = START;
    while (x != end_x || y != end_y) {
        int dir_index = rand() % 4;
        int new_x = x + directions[dir_index].dx;
        int new_y = y + directions[dir_index].dy;

        if (is_within_bounds(HEIGHT, WIDTH, new_x, new_y)) {
            if (maze[new_y][new_x] == WALL) {
                maze[new_y][new_x] = PATH;
            }
            x = new_x;
            y = new_y;
        }
    }

    maze[y][x] = END;
}

void write_maze(int HEIGHT, int WIDTH, char maze[HEIGHT][WIDTH], const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fputc(maze[y][x], fp); 
        }
        fputc('\n', fp);
    }

    fclose(fp);
}


