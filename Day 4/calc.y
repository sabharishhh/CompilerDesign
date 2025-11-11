%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);

%}

%union {
    double dval;
}

%token <dval> NUMBER
%type <dval> expr

%left '+' '-'
%left '*' '/'
%left UMINUS

%%

input:
    | input line
    ;

line:
      '\n'
    | expr '\n' { printf("Result = %.2f\n\n", $1); }
    ;

expr:
      NUMBER { $$ = $1; }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { $$ = ($3 != 0) ? $1 / $3 : (yyerror("Division by zero"), 0); }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')' { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
	printf("Press Ctrl + D to exit\n");
    printf("Enter input: ");
    return yyparse();
}
