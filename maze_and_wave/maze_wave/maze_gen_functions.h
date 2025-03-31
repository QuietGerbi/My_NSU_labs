#ifndef MAZE_GEN_FUNCTIONS_H
#define MAZE_GEN_FUNCTIONS_H

void initialize_maze(int HEIGHT, int WIDTH, char maze[HEIGHT][WIDTH]);
int is_within_bounds(int HEIGHT, int WIDTH, int x, int y);
void drunkard_walk(int HEIGHT, int WIDTH, char maze[HEIGHT][WIDTH], int start_x, int start_y, int end_x, int end_y);
void write_maze(int HEIGHT, int WIDTH, char maze[HEIGHT][WIDTH], const char* filename);


#endif