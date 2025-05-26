#include "functions.h"

int compare_points(const void* a, const void* b) {
    point* p1 = (point*)a;
    point* p2 = (point*)b;
    if (p1->x != p2->x) {
        return (p1->x > p2->x) ? 1 : -1;
    } else {
        return (p1->y > p2->y) ? 1 : -1;
    }
}

double vector_multiplying(point a, point b, point c) {
    return (double)(b.x - a.x) * (c.y - a.y) - (double)(b.y - a.y) * (c.x - a.x);
}

convexhull andrew_algorithm(pointarray input) {
    convexhull result = {NULL, 0};
    
    if (input.size <= 1) {
        result.size = input.size;
        if (input.size == 1) {
            result.points = (point*)malloc(sizeof(point));
            result.points[0] = input.points[0];
        }
        return result;
    }

    qsort(input.points, input.size, sizeof(point), compare_points);

    point* hull = (point*)malloc(2 * input.size * sizeof(point));
    if (hull == NULL) {
        return result;
    }
    int32_t k = 0;

    for (int32_t i = 0; i < input.size; ++i) {
        while (k >= 2 && vector_multiplying(hull[k-2], hull[k-1], input.points[i]) <= 0) {
            k--;
        }
        hull[k++] = input.points[i];
    }

    for (int32_t i = input.size - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && vector_multiplying(hull[k-2], hull[k-1], input.points[i]) <= 0) {
            k--;
        }
        hull[k++] = input.points[i];
    }

    result.points = hull;
    result.size = k - 1;
    return result;
}


