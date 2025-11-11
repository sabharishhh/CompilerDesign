#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum TokenType {
    TOK_ID, TOK_PLUS, TOK_MUL, TOK_LPAREN, TOK_RPAREN,
    TOK_END, TOK_INVALID
};

struct Token {
    enum TokenType type;
    char text[32];
};

struct Token tokens[100];
int tok_index = 0;  // current token position
int tok_count = 0;  // total tokens

void addToken(enum TokenType type, const char *text) {
    tokens[tok_count].type = type;
    strcpy(tokens[tok_count].text, text);
    tok_count++;
}

void tokenize(const char *input) {
    int i = 0, n = strlen(input);
    while (i < n) {
        if (isspace((unsigned char)input[i])) { 
            i++; 
            continue; 
        }

        if (isalpha((unsigned char)input[i])) {   // id
            char buf[32]; 
            int j = 0;
            while (isalnum((unsigned char)input[i])) 
                buf[j++] = input[i++];
            buf[j] = '\0';
            addToken(TOK_ID, buf);
        }
        else {
            switch (input[i]) {
                case '+': addToken(TOK_PLUS, "+"); break;
                case '*': addToken(TOK_MUL, "*"); break;
                case '(': addToken(TOK_LPAREN, "("); break;
                case ')': addToken(TOK_RPAREN, ")"); break;
                default:  addToken(TOK_INVALID, "?"); break;
            }
            i++;
        }
    }
    addToken(TOK_END, "EOF");
}

// ------------------ PARSER ------------------

struct Token getToken() {
    return tokens[tok_index];
}
 
void advance() { 
    if (tok_index < tok_count) 
        tok_index++; 
}

void error() {
    printf("Invalid Expression\n\n");
    exit(1);
}

void match(enum TokenType expected) {
    if (getToken().type == expected) {
        advance();
    } else {
        error();
    }
}

// Grammar functions
void E();
void Eprime();
void T();
void Tprime();
void F();

// E → T E'
void E() {
    T();
    Eprime();
}

// E' → + T E' | ε
void Eprime() {
    if (getToken().type == TOK_PLUS) {
        match(TOK_PLUS);
        T();
        Eprime();
    }
}

// T → F T'
void T() {
    F();
    Tprime();
}

// T' → * F T' | ε
void Tprime() {
    if (getToken().type == TOK_MUL) {
        match(TOK_MUL);
        F();
        Tprime();
    }
}

// F → ( E ) | id
void F() {
    if (getToken().type == TOK_LPAREN) {
        match(TOK_LPAREN);
        E();
        match(TOK_RPAREN);
    } else if (getToken().type == TOK_ID) {
        match(TOK_ID);
    } else {
        error();
    }
}

// ------------------ MAIN ------------------

int main() {
    char input[100];
    printf("\nEnter expression > ");
    fgets(input, sizeof(input), stdin);

    tokenize(input);

    E();  // start symbol

    if (getToken().type == TOK_END) {
        printf("Valid Expression\n\n");
    } else {
        error();
    }

    return 0;
}