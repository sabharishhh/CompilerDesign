%option noyywrap

%{
    #include <stdio.h>
%}

%%
[a-zA-Z0-9._%+-]+@[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*\.[a-zA-Z]{2,} {
    printf("Valid email: %s\n", yytext);
}

[^ \t\n]+ {
    printf("Invalid email: %s\n", yytext);
}

[ \t]+ ;      /* ignore spaces and tabs */
\n    { return 0; }   /* stop after each line */
%%

int main() {
    while (1) {
        printf("Enter email (Ctrl+C to exit): ");
        fflush(stdout);
        yylex();   // process one line, then return
    }
    return 0;
}
