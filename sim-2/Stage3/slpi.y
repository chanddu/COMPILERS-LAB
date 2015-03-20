%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "lex.yy.c"
	int yylex(void);
	void yyerror(char *s);
	
%}

%token DIGIT ID READ WRITE
%left '+'  '-' 
%left '*'  '/'

%%

program	:	Slist '\n'		{evaluate($1); exit(1);}
			;
Slist	:	Slist stmt ';'	{ node *temp = malloc(sizeof(node)); mkNode(temp,0,'T','$','$',$1,$2); $$ = makeLEAFnode(temp);}
			| stmt ';'		{ $$ = makeLEAFnode($1); }
			;
stmt	:	ID '=' expr		{ $$ = makeINTERIORnode($2,$1,$3); }
			| READ '(' ID ')'	{ node *temp = malloc(sizeof(node)); temp->nodeType = 'R';$$ = makeINTERIORnode(temp,$3,NULL); }
			| WRITE '(' expr ')'	{ node *temp = malloc(sizeof(node)); temp->nodeType = 'W'; $$ = makeINTERIORnode(temp,$3,NULL); }
			;
			
expr	:	DIGIT	{ $$ = makeLEAFnode($1); }
			| ID	{ $$ = makeLEAFnode($1); }
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