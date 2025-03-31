#include "constants.h"

ErrorToken f_push(double value, double* stack, int* top) {
    if (*top >= STACK_SIZE - 1) {
        return SYNTAX_ERROR;
    }
    stack[++(*top)] = value;
    return NO_ERROR;
}

ErrorToken f_pop(double* value, double* stack, int* top) {
    if (*top < 0) {
        return SYNTAX_ERROR;
    }
    *value = stack[(*top)--];
    return NO_ERROR;
}

ErrorToken f_push_operator(char op, char* operator_stack, int* operator_top) {
    if (*operator_top >= STACK_SIZE - 1) {
        return SYNTAX_ERROR;
    }
    operator_stack[++(*operator_top)] = op;
    return NO_ERROR;
}

ErrorToken f_pop_operator(char* op, char* operator_stack, int* operator_top) {
    if (*operator_top < 0) {
        return SYNTAX_ERROR;
    }
    *op = operator_stack[(*operator_top)--];
    return NO_ERROR;
}

ErrorToken f_take_operator(char* op, char* operator_stack, int* operator_top) {
    if (*operator_top < 0) {
        return SYNTAX_ERROR;
    }
    *op = operator_stack[*operator_top];
    return NO_ERROR;
}

