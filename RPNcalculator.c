#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100


typedef struct {
    int top;
    double items[MAX_EXPR_LENGTH];
} Stack;


void push(Stack *s, double value) {
    if (s->top < MAX_EXPR_LENGTH - 1) {
        s->top++;
        s->items[s->top] = value;
    } else {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
}

double pop(Stack *s) {
    if (s->top >= 0) {
        return s->items[s->top--];
    } else {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
}

double evaluatePostfix(char *expr) {
    Stack s;
    s.top = -1;
    double operand1, operand2, result;

    while (*expr) {
        if (isdigit(*expr)) {
            push(&s, atof(expr));
            while (isdigit(*expr) || *expr == '.') {
                expr++;
            }
        } else if (*expr == '+' || *expr == '-' || *expr == '*' || *expr == '/') {
            operand2 = pop(&s);
            operand1 = pop(&s);
            switch (*expr) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
            }
            push(&s, result);
            expr++;
        } else {
            expr++; 
        }
    }
    return pop(&s);
}

int main() {
    char infix[MAX_EXPR_LENGTH];

    printf("Enter the expression in infix notation: ");
    fgets(infix, MAX_EXPR_LENGTH, stdin);

   
    infix[strcspn(infix, "\n")] = '\0';

    
    double result = evaluatePostfix(infix);
    printf("Result: %.2f\n", result);

    return 0;
}
