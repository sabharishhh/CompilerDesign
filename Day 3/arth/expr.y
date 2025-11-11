%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex(void);
    void yyerror(const char *s);
%}



%token NUMBER
%token IDENTIFIER

%right '='
%left '+' '-'
%left '*' '/'
%left UMINUS

%%
input:
    /*empty*/
    | input expr '\n' {printf("Expression is valid\n");}
    ;

expr:
        expr '=' expr   {}
    |   expr '+' expr   {}
    |   expr '-' expr   {}
    |   expr '*' expr   {}
    |   expr '/' expr   {}
    |   '-' expr %prec UMINUS
    |   '(' expr ')'
    |   NUMBER
    |   IDENTIFIER
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter arithmetic expr: ");
    yyparse();
    return 0;
}