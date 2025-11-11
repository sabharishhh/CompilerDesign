%{
#include "identifier.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]*   { return IDENTIFIER; }   
[ \t]                  { }
\n                     { return '\n'; }         
.                      { return INVALID; }     

%%

int yywrap() {
    return 1; 
}

