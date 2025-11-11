#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    switch (c) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
    }
    return -1;
}

void infixToPostfix(char* infix, char* postfix) {
    int i, k = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];
        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        } else { // operator
            while (top != -1 && precedence(stack[top]) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }

    while (top != -1)
        postfix[k++] = pop();
    postfix[k] = '\0';
}

void generateCode(char* postfix) {
    char temp[10];
    char stackVar[MAX][10];
    int t = 1, topVar = -1;
    char c;

    for (int i = 0; postfix[i] != '\0'; i++) {
        c = postfix[i];
        if (isalnum(c)) {
            char operand[2];
            operand[0] = c; operand[1] = '\0';
            strcpy(stackVar[++topVar], operand);
        } else { // operator
            char op2[10], op1[10];
            strcpy(op2, stackVar[topVar--]);
            strcpy(op1, stackVar[topVar--]);

            sprintf(temp, "t%d", t++);
            printf("%s = %s %c %s\n", temp, op1, c, op2);

            strcpy(stackVar[++topVar], temp);
        }
    }
    // Final result
    printf("Result stored in %s\n", stackVar[topVar]);
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    printf("Intermediate Code:\n");
    generateCode(postfix);

    return 0;
}