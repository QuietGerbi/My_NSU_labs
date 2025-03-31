#ifndef FLOAT_STACK_H
#define FLOAT_STACK_H

#include "constants.h"

ErrorToken f_push(double value, double* stack, int* top);
ErrorToken f_pop(double* value, double* stack, int* top);

ErrorToken f_push_operator(char op, char* operator_stack, int* operator_top);
ErrorToken f_pop_operator(char* op, char* operator_stack, int* operator_top);
ErrorToken f_take_operator(char* op, char* operator_stack, int* operator_top);

#endif


