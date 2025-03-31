#ifndef STACK_H
#define STACK_H

#include "constants.h"

ErrorToken push(int value, int* stack, int* top);
ErrorToken pop(int* value, int* stack, int* top);

ErrorToken push_operator(char op, char* operator_stack, int* operator_top);
ErrorToken pop_operator(char* op, char* operator_stack, int* operator_top);
ErrorToken take_operator(char* op, char* operator_stack, int* operator_top);

#endif


