%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token IDENTIFIER INVALID

%%

input:
      IDENTIFIER '\n'   { printf("Valid Identifier\n"); }
    | INVALID '\n'      { yyerror("Invalid Identifier"); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
    printf("\nEnter an identifier: ");
    yyparse();
    return 0;
}

