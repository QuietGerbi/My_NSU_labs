#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "node.h"
#include "constants.h"

int main(int argc, char* argv[]) {
    node* root = NULL;
    int32_t N;

    __u_short* rotations = NULL;
    int32_t rotation_count = 0;
    int32_t rotation_capacity = 0;

    if (scanf("%d", &N) != 1) {
        printf("Empty input\n");
        return 0;
    }

    if(is_valid(N)==-1){
        printf("Bad input\n");
        return 0;
    }

    rotation_capacity = 16;
    rotations = malloc(rotation_capacity * sizeof(__u_short));
    if (!rotations) {
        return 0;
    }

    for (int i = 0; i < N; i++) {
        int a;
        if (scanf("%d", &a) != 1) {
            printf("Bad input\n");
            free(rotations);
            return 0;
        }
        root = insert(root, a, &rotations, &rotation_count, &rotation_capacity);
    }

    for (int i = 0; i < rotation_count; i++) {
        printf("%s ", rotation_to_string(rotations[i]));
    }

    printf("%d ", height(root));

    if (argc > 1) {
        char mode[3] = "";
        strncpy(mode, argv[1], sizeof(mode) - 1);
        if (strcmp(mode, "-p") == 0){
            printf("\n");
            __u_char path[100];
            PrintPaths(root, path, 0);
        }
        else if (strcmp(mode, "-t") == 0){
            printf("\n");
            in_order_traversal(root);
            printf("\n");
        }
    }

    free(rotations);
    free_tree(root);
    return 0;
}


