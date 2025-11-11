#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum TokenType {
    TOK_ID, TOK_IF, TOK_PLUS, TOK_MINUS,
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE,
    TOK_ASSIGN, TOK_SEMI,
    TOK_END, TOK_INVALID
};

struct Token {
    enum TokenType type;
    char text[32];
};

struct Token tokens[100];
int tok_index = 0;
int tok_count = 0;

// ---------------- TOKENIZER ----------------

void addToken(enum TokenType type, const char *text) {
    tokens[tok_count].type = type;
    strcpy(tokens[tok_count].text, text);
    tok_count++;
}

void tokenize(const char *input) {
    int i = 0, n = (int)strlen(input);
    while (i < n) {
        if (isspace((unsigned char)input[i])) { i++; continue; }

        if (isalpha((unsigned char)input[i])) { // id or keyword
            char buf[32]; int j = 0;
            while (isalnum((unsigned char)input[i])) buf[j++] = input[i++];
            buf[j] = '\0';
            if (strcmp(buf, "if") == 0) addToken(TOK_IF, "if");
            else addToken(TOK_ID, buf);
        } else {
            switch (input[i]) {
                case '+': addToken(TOK_PLUS, "+"); break;
                case '-': addToken(TOK_MINUS, "-"); break;
                case '(': addToken(TOK_LPAREN, "("); break;
                case ')': addToken(TOK_RPAREN, ")"); break;
                case '{': addToken(TOK_LBRACE, "{"); break;
                case '}': addToken(TOK_RBRACE, "}"); break;
                case '=': addToken(TOK_ASSIGN, "="); break;
                case ';': addToken(TOK_SEMI, ";"); break;
                default:  addToken(TOK_INVALID, "?"); break;
            }
            i++;
        }
    }
    addToken(TOK_END, "EOF");
}

// ---------------- PARSER CORE ----------------

struct Token getToken() { return tokens[tok_index]; }
void advance() { if (tok_index < tok_count) tok_index++; }

void error() {
    printf("Invalid Program\n\n");
    exit(1);
}

void match(enum TokenType expected) {
    if (getToken().type == expected) advance();
    else error();
}

// ---------------- GRAMMAR ----------------

// Forward declarations
void Program();
void Stmts();
void Stmt();
void Expr();
void Etail();

// Program → { Stmts }
void Program() {
    match(TOK_LBRACE);
    Stmts();
    match(TOK_RBRACE);
}

// Stmts → Stmt Stmts | ε
void Stmts() {
    enum TokenType la = getToken().type;
    if (la == TOK_ID || la == TOK_IF) {
        Stmt();
        Stmts();
    } else {
        // ε when next is '}' or EOF
    }
}

// Stmt → id = Expr ; | if ( Expr ) Stmt
void Stmt() {
    enum TokenType la = getToken().type;
    if (la == TOK_ID) {
        match(TOK_ID);
        match(TOK_ASSIGN);
        Expr();
        match(TOK_SEMI);
    } else if (la == TOK_IF) {
        match(TOK_IF);
        match(TOK_LPAREN);
        Expr();
        match(TOK_RPAREN);
        Stmt();  // single-statement body
    } else {
        error();
    }
}

// Expr → id Etail
void Expr() {
    match(TOK_ID);
    Etail();
}

// Etail → + Expr | - Expr | ε
void Etail() {
    enum TokenType la = getToken().type;
    if (la == TOK_PLUS || la == TOK_MINUS) {
        advance();   // consume + or -
        Expr();
    } else {
        // ε on ), ;, }, EOF
    }
}

// ---------------- MAIN ----------------

int main() {
    char input[1024];
    printf("\nEnter program > ");
    if (!fgets(input, sizeof(input), stdin)) return 0;

    tokenize(input);
    Program(); // start symbol

    if (getToken().type == TOK_END)
        printf("Valid Program\n\n");
    else
        error();

    return 0;
}
