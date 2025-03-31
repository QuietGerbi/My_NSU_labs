#include "int_calculator.h"
#include "stack.h"
#include "constants.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int operator_priority(char op) {
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

int power(int a, int b){
    int res = 1;
    for (int i=0;i<b;i++){
        res*=a;
    }
    return res;
}

ErrorToken infix_to_rpn(const char* expression, char* output, int* operator_top, char* operator_stack) {
    int i = 0, j = 0;
    int inside_brackets = 0;
    int has_content_inside = 0;
    *operator_top = -1;

    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            if (inside_brackets == 1) {
                has_content_inside = 1;
            }
            while (isdigit(expression[i])) {
                output[j++] = expression[i++];
            }
            output[j++] = ' ';
            i--;
        }

        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            char top_op;
            while ((take_operator(&top_op, operator_stack, operator_top) + 1) && *operator_top >= 0 && operator_priority(top_op) >= operator_priority(expression[i])) {
                if (pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                output[j++] = top_op;
                output[j++] = ' ';
            }
            if (push_operator(expression[i], operator_stack, operator_top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
        }

        if (expression[i] == '^') {
            char top_op;
            while ((take_operator(&top_op, operator_stack, operator_top) + 1) && *operator_top > 0 && operator_priority(top_op) > operator_priority(expression[i])) {
                if (pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                output[j++] = top_op;
                output[j++] = ' ';
            }
            if (push_operator(expression[i], operator_stack, operator_top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
        }

        else if (expression[i] == '(') {
            if (push_operator(expression[i], operator_stack, operator_top) == SYNTAX_ERROR) {
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
            while (take_operator(&top_op, operator_stack, operator_top) != SYNTAX_ERROR && top_op != '(') {
                if (pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                output[j++] = top_op;
                output[j++] = ' ';
            }
            if (pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
        }
        i++;
    }

    char top_op;
    while (*operator_top >= 0) {
        if (pop_operator(&top_op, operator_stack, operator_top) == SYNTAX_ERROR) {
            return SYNTAX_ERROR;
        }
        output[j++] = top_op;
        output[j++] = ' ';
    }

    output[j] = '\0';
    return NO_ERROR;
}

ErrorToken calculate_expression(const char* expression, int* result, int* stack, int* top) {
    *top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (isdigit(expression[i])) {
            int number = 0;
            while (isdigit(expression[i])) {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            if (push(number, stack, top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
            int b, a;
            if (pop(&b, stack, top) == SYNTAX_ERROR || pop(&a, stack, top) == SYNTAX_ERROR) {
                return SYNTAX_ERROR;
            }
            switch (expression[i]) {
            case '+':
                if (push(a + b, stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            case '-':
                if (push(a - b, stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            case '*':
                if (push(a * b, stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            case '/':
                if (b == 0) {
                    return DIVISION_BY_ZERO;
                }
                if (push(a / b, stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            case '^':
                if (push(power(a, b), stack, top) == SYNTAX_ERROR) {
                    return SYNTAX_ERROR;
                }
                break;
            }
        }
    }

    if (*top != 0) {
        return SYNTAX_ERROR;
    }

    if (pop(result, stack, top) == SYNTAX_ERROR) {
        return SYNTAX_ERROR;
    }

    return NO_ERROR;
}

int default_mode(int* stack, int* top, char* operator_stack, int* operator_top) {
    char expression[DEF_SIZE];
    char expression_in_rpn[DEF_SIZE];
    int result;

    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        printf("syntax error\n");
        return 0;
    }

    expression[strcspn(expression, "\n")] = '\0';

    ErrorToken error = infix_to_rpn(expression, expression_in_rpn, operator_top, operator_stack);
    if (error != NO_ERROR) {
        printf("syntax error\n");
        return 0;
    }

    error = calculate_expression(expression_in_rpn, &result, stack, top);
    if (error == SYNTAX_ERROR) {
        printf("syntax error\n");
        return 0;
    } else if (error == DIVISION_BY_ZERO) {
        printf("division by zero\n");
        return 0;
    }

    printf("%d\n", result);
    return 0;
}

int interactive_mode(int mode, int last_result, int* stack, int* top, char* operator_stack, int* operator_top) {
    if (mode == 0) {
        default_mode(stack, top, operator_stack, operator_top);
        return 0;
    }

    char expression[DEF_SIZE];
    char expression_in_rpn[DEF_SIZE];

    while (mode) {
        fputs("> ", stdout);
        if (fgets(expression, sizeof(expression), stdin) == NULL) {
            printf("syntax error\n");
            return 0;
        }
        expression[strcspn(expression, "\n")] = '\0';

        if (strcmp(expression, "exit") == 0) {
            return 0;
        }

        char modified_expression[DEF_SIZE];
        int j = 0;
        for (int i = 0; expression[i] != '\0'; i++) {
            if (expression[i] == '$') {
                j += sprintf(modified_expression + j, "%d", last_result);
            } else {
                modified_expression[j++] = expression[i];
            }
        }
        modified_expression[j] = '\0';

        ErrorToken error = infix_to_rpn(modified_expression, expression_in_rpn, operator_top, operator_stack);
        if (error != NO_ERROR) {
            printf("syntax error\n");
            continue;
        }

        int result;
        error = calculate_expression(expression_in_rpn, &result, stack, top);
        if (error == SYNTAX_ERROR) {
            printf("syntax error\n");
        } else if (error == DIVISION_BY_ZERO) {
            printf("division by zero\n");
        } else {
            last_result = result;
            fputs("< ", stdout);
            printf("%d\n", result);
        }
    }
    return 0;
}

