#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    char P[100];
    int N;

    if (fgets(P, 100, stdin) == NULL) {
        printf("bad input\n");
        return 0;
    }

    size_t len = strlen(P);
    if (len > 0 && P[len - 1] == '\n') {
        P[len - 1] = '\0';
    }

    if (is_valid(P) == -1) {
        printf("bad input\n");
        return 0;
    }

    if (scanf("%d", &N) != 1) {
        printf("bad input\n");
        return 0;
    }
    
    int count = 0;
    while (count < N && next_permutation(P)) {
        printf("%s\n", P);
        count++;
    }

    return 0;
}



