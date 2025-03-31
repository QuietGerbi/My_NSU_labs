#include "float_calculator.h"
#include "float_stack.h"
#include "constants.h"
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int f_operator_priority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

ErrorToken f_infix_to_rpn(const char* expression, char* output, int* operator_top, char* operator_stack) {
    int i = 0, j = 0;
    int inside_brackets = 0;
    int has_content_inside = 0;
    *operator_top = -1;

    while (expression[i] != '\0') {
        if (isdigit(expression[i]) || expression[i]=='.') {
            if (inside_brackets == 1) {
                has_content_inside = 1;
            }
            while (isdigit(expression[i]) || expression[i]=='.') {
                output[j++] = expression[i++];
            }
            output[j++] = ' ';
            i--;
        }

        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            char top_op;
            while ((f_take_operator(&top_op, operator_stack, operator_top) + 1) && *operator_top >= 0 && f_operator_priority(top_op) >= f_operator_priority(expression[i])) {
                if (f_pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                output[j++] = top_op;
                output[j++] = ' ';
            }
            if (f_push_operator(expression[i], operator_stack, operator_top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
        }

        if (expression[i] == '^') {
            char top_op;
            while ((f_take_operator(&top_op, operator_stack, operator_top) + 1) && *operator_top > 0 && f_operator_priority(top_op) > f_operator_priority(expression[i])) {
                if (f_pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                output[j++] = top_op;
                output[j++] = ' ';
            }
            if (f_push_operator(expression[i], operator_stack, operator_top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
        }

        else if (expression[i] == '(') {
            if (f_push_operator(expression[i], operator_stack, operator_top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
            inside_brackets = 1;
            has_content_inside = 0;
        }

        else if (expression[i] == ')') {
            char top_op;
            if (inside_brackets && !has_content_inside) {
                return SYNTAX_ERROR;
            }
            while (f_take_operator(&top_op, operator_stack, operator_top) != SYNTAX_ERROR && top_op != '(') {
                if (f_pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                output[j++] = top_op;
                output[j++] = ' ';
            }
            if (f_pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
        }
        i++;
    }

    char top_op;
    while (*operator_top >= 0) {
        if (f_pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
            return SYNTAX_ERROR;
        }
        output[j++] = top_op;
        output[j++] = ' ';
    }

    output[j] = '\0';
    return NO_ERROR;
}

ErrorToken calculate_float_expression(const char* expression, double* result, double* stack, int* top) {
    *top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (isdigit(expression[i]) || expression[i] == '.') {
            double number = 0;
            double fraction = 0.1;
            int is_fraction = 0;

            while (isdigit(expression[i]) || expression[i] == '.') {
                if (expression[i] == '.') {
                    if (is_fraction) {
                        return SYNTAX_ERROR;
                    }
                    is_fraction = 1;
                    i++;
                    continue;
                }

                if (is_fraction) {
                    number += (expression[i] - '0') * fraction;
                    fraction *= 0.1;
                } else {
                    number = number * 10 + (expression[i] - '0');
                }
                i++;
            }
            i--;

            if (f_push(number, stack, top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
            double b, a;
            if (f_pop(&b, stack, top) == SYNTAX_ERROR || f_pop(&a, stack, top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
            switch (expression[i]) {
            case '+':
                if (f_push(a + b, stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            case '-':
                if (f_push(a - b, stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            case '*':
                if (f_push(a * b, stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            case '/':
                if (b == 0) {
                    return DIVISION_BY_ZERO;
                }
                if (f_push(a / b, stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            case '^':
                if (f_push(pow(a, b), stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            }
        }
    }

    if (*top != 0) {
        return SYNTAX_ERROR;
    }

    if (f_pop(result, stack, top) == SYNTAX_ERROR) {
        return SYNTAX_ERROR;
    }

    return NO_ERROR;
}
int float_mode(double* stack, int* top, char* operator_stack, int* operator_top) {
    char expression[DEF_SIZE];
    char expression_in_rpn[DEF_SIZE];
    double result;

    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        printf("syntax error\n");
        return 0;
    }

    expression[strcspn(expression, "\n")] = '\0';

    ErrorToken error = f_infix_to_rpn(expression, expression_in_rpn, operator_top, operator_stack);
    if (error != NO_ERROR) {
        printf("syntax error\n");
        return 0;
    }

    error = calculate_float_expression(expression_in_rpn, &result, stack, top);
    if (error == SYNTAX_ERROR) {
        printf("syntax error\n");
        return 0;
    } else if (error == DIVISION_BY_ZERO) {
        printf("division by zero\n");
        return 0;
    }

    printf("%f\n", result);
    return 0;
}



