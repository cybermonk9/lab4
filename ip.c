#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_SIZE 20

char stack[MAX_SIZE];
int top = -1;

void push(char op);
char pop();
int precedence(char op);
void conversion(char infix[], char postfix[]);

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];
    stack[++top] = '#';

    printf("Enter infix expression: ");
    scanf("%s", infix);

    conversion(infix, postfix);

    printf("Postfix expression is %s\n", postfix);

    return 0;
}

void push(char op) {
    stack[++top] = op;
}

char pop() {
    if (top == -1) {
        printf("Invalid expression\n");
        exit(1);
    } else {
        return stack[top--];
    }
}

int precedence(char op) {
    switch (op) {
        case '^': return 4;
        case '%':
        case '/':
        case '*': return 3;
        case '+':
        case '-': return 2;
        case '(': return 1;
        case '#': return 0;
        default:
            printf("Invalid choice\n");
            exit(1);
    }
}

void conversion(char infix[], char postfix[]) {
    int i = 0, j = 0;
    char token;

    while (infix[i] != '\0') {
        token = infix[i];

        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(token);
        } else if (token == ')') {
            while (stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop(); 
        } else {
            while (precedence(stack[top]) >= precedence(token)) {
                if (stack[top] == '^' && token == '^') {
                    break;
                }
                postfix[j++] = pop();
            }
            push(token);
        }

        i++;
    }

    while (stack[top] != '#') {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}
