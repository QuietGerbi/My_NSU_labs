#ifndef DIJSKTRA_H
#define DIJSKTRA_H

void free_graph(int** graph, int N); 
void param_input(int* N, int* S, int* F, int* M);
long long int is_valid(int N, int S, int F, int M);
void dijkstra(int N, int S, int F, int** graph, int mode, char* output_filename);


#endif


