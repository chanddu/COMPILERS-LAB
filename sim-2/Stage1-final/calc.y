/* Simple calculator */

%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	int yylex(void);
	void yyerror(char *);
%}

%token INTEGER

%left '+' '-'
%left '*' '/'
%left '^'

%%

program:
		program expr '\n' { printf("%d\n", $2); }
		| '\n' |
		;
expr:
		INTEGER
		| expr '+' expr { printf("r1\n");$$ = $1 + $3; }
		| expr '-' expr { printf("r2\n");$$ = $1 - $3; }
		| expr '*' expr { printf("r3\n");$$ = $1 * $3; }
		| expr '/' expr { printf("r4\n");$$ = $1 / $3; }
		| '(' expr ')' { printf("r5\n");$$ = $2; }
		| '-' expr { $$ = -1 * $2; }
		| expr '^' expr { $$ = pow($1,$3); }
		;

%%

void yyerror( char *s) {
	printf("%s\n" , s);
}

int main (void) {
	return yyparse();
}