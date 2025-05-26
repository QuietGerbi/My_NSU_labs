#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int64_t x, y;
} point;

typedef struct {
    point* points;
    int32_t size;
} pointarray;

typedef struct {
    point* points;
    int32_t size;
} convexhull;


int32_t compare_points(const void *a, const void *b);
double vector_multiplying(point a, point b, point c);
convexhull andrew_algorithm(pointarray input);


#endif


