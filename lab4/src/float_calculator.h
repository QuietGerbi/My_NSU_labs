#ifndef FLOAT_CALCULATOR_H
#define FLOAT_CALCULATOR_H

#include "constants.h"

int f_operator_priority(char op);
ErrorToken f_infix_to_rpn(const char* expression, char* output, int* operator_top, char* operator_stack);
ErrorToken calculate_float_expression(const char* expression, double* result, double* stack, int* top);
int float_mode(double* stack, int* top, char* operator_stack, int* operator_top);

#endif

