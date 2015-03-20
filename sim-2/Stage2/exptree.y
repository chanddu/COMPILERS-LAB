%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "lex.yy.c"
	int yylex(void);
	void yyerror(char *s);
	
%}

%token DIGIT
%left '+'  '-' 
%left '*'  '/'

%%

program	:	program expr '\n'		{$$ = $2; printf("%d\n",evaluate($$));}
			|
			;
			
expr	:	DIGIT	{ $$ = makeLEAFnode($1); }
			| '(' expr ')'	{ $$=$2; }
			| expr '+' expr	{ $$ = makeINTERIORnode($2,$1,$3); }
			| expr '-' expr	{ $$ = makeINTERIORnode($2,$1,$3); }
			| expr '*' expr	{ $$ = makeINTERIORnode($2,$1,$3); }
			| expr '/' expr	{ $$ = makeINTERIORnode($2,$1,$3); }
			;

%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

int main(void) {
	yyparse();
	return 0;
}