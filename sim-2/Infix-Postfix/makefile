postfix: lex.yy.c y.tab.c
	gcc -g lex.yy.c y.tab.c -o postfix

lex.yy.c: y.tab.c postfix.l
	lex postfix.l

y.tab.c: postfix.y
	yacc -d postfix.y

clean: 
	rm -f lex.yy.c y.tab.c y.tab.h postfix

