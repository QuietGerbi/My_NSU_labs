#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "node.h"
#include "constants.h"

int main(int argc, char* argv[]) {
    node* root = NULL;
    int32_t N;
    pool node_pool = {NULL, 0};
    int8_t* rotations = NULL;
    int32_t rotation_count = 0;
    int32_t rotation_capacity = 8;

    if (scanf("%d", &N) != 1) {
        printf("Empty input\n");
        return 0;
    }

    if (is_valid(N) == -1) {
        printf("Bad input\n");
        return 0;
    }

    init_pool(&node_pool);

    rotations = malloc(rotation_capacity * sizeof(int16_t));
    if (!rotations) return 0;

    for (int i = 0; i < N; ++i) {
        int32_t a;
        if (scanf("%d", &a) != 1) {
            printf("Bad input\n");
            free(rotations);
            free_tree(&node_pool);
            return 0;
        }
        root = insert(root, a, &node_pool, &rotations, &rotation_count, &rotation_capacity);
    }

    if (argc > 1) {
        char mode[3] = "";
        strncpy(mode, argv[1], sizeof(mode) - 1);
        int print_path = (strcmp(mode, "-p") == 0);
        if (print_path==1){
            char path[100];
            print_leaf_paths(root, path, 0);
        return 0;
    }
    }

    if (N<=100){
        for (int i = 0; i < rotation_count; ++i) {
            printf("%s ", rotation_to_string(rotations[i]));
        }
    }
    printf("%d", height(root));

    free(rotations);
    free_tree(&node_pool);
    return 0;
}



