%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(char *s);

    int valid = 0;
%}

%token A B

%%
S
  : A A A A A AS B { valid = 1; }
  ;

AS
  :
  | AS A
  ;
%%

void yyerror(char *s) {
    /* do nothing */
}

int main() {
    printf("Enter string: ");
    yyparse();

    if (valid)
        printf("Valid\n");
    else
        printf("Invalid\n");

    return 0;
}