%option noyywrap

%{
    #include <stdlib.h>
    #include "expr.tab.h"

    void yyerror(const char *s);
%}

%%
[0-9]+      {yylval = atoi(yytext); return NUMBER;}
[a-zA-Z]+   {return IDENTIFIER;}
[ \t]       {}
\n          {return '\n';}
[+\-*/=()]    {return yytext[0];}
.           {return -1;}
%%
