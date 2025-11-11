%option noyywrap

%{
int lines = 0, words = 0, characters = 0;
%}

%%

\n      { lines++; characters++; }
[ \t]+  { characters += yyleng; }
[A-Za-z]+ { words++; characters += yyleng; }


%%

int main() {
    
    yylex();
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);
    return 0;
}

