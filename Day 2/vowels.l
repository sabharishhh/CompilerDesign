%{
int vowels = 0, consonants = 0;
%}

%%

[aAeEiIoOuU]   { vowels++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { consonants++; }
.|\n          ;  

%%

int main() {
    printf("Enter a string:\n");
    yylex();
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    return 0;
}

int yywrap() {
    return 1;
}
 
 
