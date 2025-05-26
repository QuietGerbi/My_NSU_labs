#include "functions.h"

int main() {
    int32_t n;
    if (scanf("%d", &n) != 1) {
        printf("bad number of points\n");
        return 0;
    }
    
    if (n < 0 || n > 100000) {
        printf("bad number of points\n");
        return 0;
    }
    
    if (n == 0) {
        return 0;
    }

    point* points = (point*)malloc(n * sizeof(point));
    if (points == NULL) {
        return 1;
    }
    
    for (int32_t i = 0; i < n; ++i) {
        if (scanf("%ld %ld", &points[i].x, &points[i].y) != 2) {
            printf("bad number of lines\n");
            free(points);
            return 0;
        }
    }

    if (n == 1) {
        printf("%ld %ld\n", points[0].x, points[0].y);
        free(points);
        return 0;
    }
    
    pointarray input = {points, n};
    convexhull hull = andrew_algorithm(input);
    
    for (int32_t i = 0; i < hull.size; ++i) {
        printf("%ld %ld\n", hull.points[i].x, hull.points[i].y);
    }
    
    free(points);
    free(hull.points);
    
    return 0;
}


