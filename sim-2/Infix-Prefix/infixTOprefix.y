%{

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "lex.yy.c"
	void yyerror(char *s);

%}

%union
{	
	char *temp;
};

%token <temp> INTEGER
%type <temp> expr program
%left '+' '-'
%left '*' '/'
%left '^'

%%

program: expr { printf("%s",$$); exit(1);}
	   ;

expr  : expr '+' expr 	{ $$=malloc(50*sizeof(char)); strcat($$,"+"); strcat($$," "); strcat($$,$1); strcat($$," "); strcat($$,$3);}
      | expr '-' expr	{ $$=malloc(50*sizeof(char)); strcat($$,"-"); strcat($$," "); strcat($$,$1); strcat($$," "); strcat($$,$3);}
      | expr '*' expr	{ $$=malloc(50*sizeof(char)); strcat($$,"*"); strcat($$," "); strcat($$,$1); strcat($$," "); strcat($$,$3);}
      | expr '/' expr	{ $$=malloc(50*sizeof(char)); strcat($$,"/"); strcat($$," "); strcat($$,$1); strcat($$," "); strcat($$,$3);}
      | expr '^' expr	{ $$=malloc(50*sizeof(char)); strcat($$,"^"); strcat($$," "); strcat($$,$1); strcat($$," "); strcat($$,$3);}
      | '(' expr ')'	{ $$ = $2 ; }
      | INTEGER	
      ;
      
%%

void yyerror(char *s){
	printf("%s",s);
}

int main(){
	yyparse();
	return 1;
}