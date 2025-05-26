#include "functions.h"

void solve_knapsack(int32_t N, int32_t W, item items[]) {
    int32_t dp[N + 1][W + 1];
    int32_t keep[N + 1][W + 1];
    
    memset(dp, 0, sizeof(dp));
    memset(keep, 0, sizeof(keep));
    
    for (int32_t i = 1; i <= N; i++) {
        for (int32_t w = 0; w <= W; w++) {
            if (items[i - 1].weight <= w) {
                int32_t new_value = dp[i - 1][w - items[i - 1].weight] + items[i - 1].value;
                if (new_value > dp[i - 1][w]) {
                    dp[i][w] = new_value;
                    keep[i][w] = 1;
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    printf("%d\n", dp[N][W]);
    
    int32_t selected[N];
    int32_t count = 0;
    int32_t w = W;
    for (int32_t i = N; i >= 1; i--) {
        if (keep[i][w]) {
            selected[count++] = i - 1;
            w -= items[i - 1].weight;
        }
    }
    
    for (int32_t i = 0; i < count; i++) {
        for (int32_t j = i + 1; j < count; j++) {
            if (selected[j] < selected[i]) {
                int32_t temp = selected[i];
                selected[i] = selected[j];
                selected[j] = temp;
            }
        }
    }
    
    for (int32_t i = 0; i < count; i++) {
        int32_t idx = selected[i];
        printf("%d %d\n", items[idx].weight, items[idx].value);
    }
}


