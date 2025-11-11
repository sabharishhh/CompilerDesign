#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main()
{
    FILE *input, *output;

    int i, flag;
    int l=1, t = 0, j = 0;

    char ch, next, str[20];
    char keyword[30][30] = {"int","main","if","else","do","while"};
    
    input = fopen("input.txt","r");
    output = fopen("output.txt","w");

    fprintf(output, "Line\t   Token No.\tToken\t\t\t\t\t Lexeme\n\n");

    while (!feof(input)) {
        i=0;
        flag=0;
        
        ch = fgetc(input);

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            fprintf(output,"%7d\t\t%7d\t\tArithmetic Operator\t\t%7c\n", l, t, ch);
            t++;
        } else if (ch == '<' || ch == '>' || ch == '=' || ch == '!')	{
            next = fgetc(input);
            
            if (next == '=') {
                // Dual Symbol Rel op
                fprintf(output,"%7d\t\t%7d\t\tRelational Operator\t\t%7c%c\n", l, t, ch, next);
            } else {
                // Single character relational operator: < >
                fprintf(output,"%7d\t\t%7d\t\tRelational Operator\t\t%7c\n", l, t, ch);
                ungetc(next, input);
            }
            
            t++;
        } 
        
        else if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '?' || ch == '@' || ch == '!')
            fprintf(output,"%7d\t\t%7d\t\tSpecial Symbol\t\t\t%7c\n", l, t++, ch);
        
        else if (isdigit(ch))
            fprintf(output,"%7d\t\t%7d\t\tDigit\t\t\t\t\t%7c\n", l, t++, ch);
        
        else if (isalpha(ch)) {
            str[i++] = ch;
            ch = fgetc(input);

            while (isalnum(ch)) {
                str[i] = ch;
                i++;
                ch = fgetc(input);
            }

            str[i] = '\0';

            for (j = 0; j < 6; j++) {
                if (strcmp(str, keyword[j]) == 0) {
                    flag = 1;
                    break;
                }
            }

            if (flag == 1)
                fprintf(output,"%7d\t\t%7d\t\tKeyword\t\t\t\t\t%7s\n", l, t++, str);
            else 
                fprintf(output,"%7d\t\t%7d\t\tIdentifier\t\t\t\t%7s\n", l, t++, str);
            
            ungetc(ch, input);
            
        } 
        else if (ch == '\n')	l++;
    }

    fclose(input);
    fclose(output);
    return 0;
}
