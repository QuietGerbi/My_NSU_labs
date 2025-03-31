#ifndef SET_VALID_FUNC_H
#define SET_VALID_FUNC_H

#include "constants.h"

int is_valid(int N, int M);
int comparator(const void *a, const void *b);
void make_set(int parent[], int rank[], int n);
int find_parent(int parent[], int component);
void union_set(int u, int v, int parent[], int rank[]);

#endif

