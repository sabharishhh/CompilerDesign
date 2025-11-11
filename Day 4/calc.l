%{
#include "calc.tab.h"
#include <stdlib.h>
%}

digit   [0-9]
number  {digit}+(\.{digit}+)?

%%

{number}   { yylval.dval = atof(yytext); return NUMBER; }
[\t ]      ;
\n         { return '\n'; }
"+"        { return '+'; }
"-"        { return '-'; }
"*"        { return '*'; }
"/"        { return '/'; }
"("        { return '('; }
")"        { return ')'; }

.          { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}


