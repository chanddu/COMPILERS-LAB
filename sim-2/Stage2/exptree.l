%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "exptree.h"
	#include "y.tab.h"
	
%}

%%

[\t]	;

[0-9]+ 	{ 	yylval = malloc(sizeof(node));
		 	mkNode(yylval,atoi(yytext),'L','X',NULL,NULL);
		 	return DIGIT;
		}

[-+*/]	{
			yylval = malloc(sizeof(node));
			mkNode(yylval,0,'I',yytext[0],NULL,NULL);
			return *yytext;
		}

[\(\)\n]	{
				return yytext[0];
			}

.		{ }
		
%%

int yywrap(void){
	return 1;
}