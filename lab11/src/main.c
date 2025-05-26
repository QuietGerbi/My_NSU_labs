#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int32_t main() {
    int32_t N, W;
    if (scanf("%d %d", &N, &W)!=2) return 0;
    
    item items[N];
    for (int32_t i = 0; i < N; i++) {
        if (scanf("%d %d", &items[i].weight, &items[i].value)!=2) return 0;
        items[i].index = i + 1;
    }
    
    solve_knapsack(N, W, items);
    
    return 0;
}


