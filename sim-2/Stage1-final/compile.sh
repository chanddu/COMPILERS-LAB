lex calc.l
yacc -d calc.y
gcc -g lex.yy.c y.tab.c -o calc
./calc
