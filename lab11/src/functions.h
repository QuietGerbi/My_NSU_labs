#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int32_t weight;
    int32_t value;
    int32_t index;
} item;

void solve_knapsack(int32_t N, int32_t W, item items[]);

#endif


