%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "y.tab.h"
%}

%%

[0-9]+ {
			yylval.temp = malloc(50*sizeof(char));
			strcpy(yylval.temp,yytext);
			return INTEGER;
		}
[-+*\/\(\)\n] {
					return (int) yytext[0];
		}

%%

int yywrap(){
	return 1;
}