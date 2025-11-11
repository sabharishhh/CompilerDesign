#!/bin/bash

echo "File name > "
read filename

bison -d "$filename.y"
flex "$filename.l"
gcc "$filename.tab.c" lex.yy.c  -lm -o "$filename"
./"$filename"
