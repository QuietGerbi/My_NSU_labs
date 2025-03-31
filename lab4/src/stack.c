#include "constants.h"

ErrorToken push(int value, int* stack, int* top) {
    if (*top >= STACK_SIZE - 1) {
        return SYNTAX_ERROR;
    }
    stack[++(*top)] = value;
    return NO_ERROR;
}

ErrorToken pop(int* value, int* stack, int* top) {
    if (*top < 0) {
        return SYNTAX_ERROR;
    }
    *value = stack[(*top)--];
    return NO_ERROR;
}

ErrorToken push_operator(char op, char* operator_stack, int* operator_top) {
    if (*operator_top >= STACK_SIZE - 1) {
        return SYNTAX_ERROR;
    }
    operator_stack[++(*operator_top)] = op;
    return NO_ERROR;
}

ErrorToken pop_operator(char* op, char* operator_stack, int* operator_top) {
    if (*operator_top < 0) {
        return SYNTAX_ERROR;
    }
    *op = operator_stack[(*operator_top)--];
    return NO_ERROR;
}

ErrorToken take_operator(char* op, char* operator_stack, int* operator_top) {
    if (*operator_top < 0) {
        return SYNTAX_ERROR;
    }
    *op = operator_stack[*operator_top];
    return NO_ERROR;
}

