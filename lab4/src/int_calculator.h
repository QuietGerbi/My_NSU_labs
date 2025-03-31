#ifndef INT_CALCULATOR_H
#define INT_CALCULATOR_H

#include "constants.h"

ErrorToken infix_to_rpn(const char* expression, char* output, int* operator_top, char* operator_stack);
ErrorToken calculate_expression(const char* expression, int* result, int* stack, int* top);
int interactive_mode(int mode, int last_result, int* stack, int* top, char* operator_stack, int* operator_top);
int default_mode(int* stack, int* top, char* operator_stack, int* operator_top);

#endif

