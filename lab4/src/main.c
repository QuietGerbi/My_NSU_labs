#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "stack.h"
#include "float_stack.h"
#include "int_calculator.h"
#include "float_calculator.h"

int main(int argc, char* argv[]) {
    char mode[3] = "";

    int stack[STACK_SIZE];
    int top = -1;
    char operator_stack[STACK_SIZE];
    int operator_top = -1;

    if (argc > 1) {
        strncpy(mode, argv[1], sizeof(mode) - 1);
    }

    int float_mode_check = (strcmp(mode, "-f") == 0);
    if (float_mode_check==1){
        double float_stack[STACK_SIZE];
        float_mode(float_stack, &top, operator_stack, &operator_top);
        return 0;
    }
    int interactive_mode_check = (strcmp(mode, "-i") == 0);
    interactive_mode(interactive_mode_check, 0, stack, &top, operator_stack, &operator_top);
    return 0;
}
