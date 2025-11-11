#include <stdio.h>
#include <string.h>

void generateAssembly(char *tac) {
    char result[20], op1[20], op2[20], op;

    if (sscanf(tac, " %[^=]=%s %c %s", result, op1, &op, op2) == 4 ||
        sscanf(tac, " %[^=]=%s%c%s", result, op1, &op, op2) == 4) {
        // Remove trailing spaces in result
        for (int i = 0; result[i]; i++) {
            if (result[i] == ' ') { result[i] = '\0'; break; }
        }

        printf("MOV R0, %s\n", op1);   
        switch (op) {
            case '+': printf("ADD R0, %s\n", op2); break;
            case '-': printf("SUB R0, %s\n", op2); break;
            case '*': printf("MUL R0, %s\n", op2); break;
            case '/': printf("DIV R0, %s\n", op2); break;
        }
        printf("MOV %s, R0\n", result); 
    }
    else if (sscanf(tac, " %[^=]=%s", result, op1) == 2) {
        for (int i = 0; result[i]; i++) {
            if (result[i] == ' ') { result[i] = '\0'; break; }
        }
        printf("MOV %s, %s\n", result, op1);
    }
}

int main() {
    int n;
    char tac[100][100];

    printf("Enter number of TAC statements: ");
    scanf("%d", &n);
    getchar(); // consume newline

    printf("Enter TAC statements one per line:\n");
    for (int i = 0; i < n; i++) {
        fgets(tac[i], sizeof(tac[i]), stdin);
        tac[i][strcspn(tac[i], "\n")] = '\0';
    }

    printf("\nGenerated Assembly Code:\n");
    for (int i = 0; i < n; i++) {
        generateAssembly(tac[i]);
    }

    return 0;
}
