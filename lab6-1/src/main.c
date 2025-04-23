#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "functions.h"

int main() {
    NodePool pool;
    initialize_pool(&pool);
    int32_t root = -1;
    int32_t N;
    
    if (scanf("%d", &N) != 1 || N < 0 || N > MAX_NODES) {
        printf("bad input\n");
        free(pool.node_pool);
        return 0;
    }

    for (int32_t i = 0; i < N; i++) {
        int32_t key;
        if (scanf("%d", &key) != 1) {
            printf("bad key\n");
            free(pool.node_pool);
            return 0;
        }
        
        int32_t parent = -1;
        int32_t current = root;
        
        while (current != -1) {
            parent = current;
            current = (key < pool.node_pool[current].key) ? 
                      pool.node_pool[current].left : 
                      pool.node_pool[current].right;
        }
        
        int32_t new_node = create_node(&pool, key);
        pool.node_pool[new_node].parent_color.parent = parent;
        
        if (parent == -1) {
            root = new_node;
        } else if (key < pool.node_pool[parent].key) {
            pool.node_pool[parent].left = new_node;
        } else {
            pool.node_pool[parent].right = new_node;
        }
        
        insert_fixup(&root, &pool, new_node);
    }

    printf("%d\n", get_black_height(root, &pool));
    free(pool.node_pool);
    return 0;
}



