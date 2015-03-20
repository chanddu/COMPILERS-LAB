%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "slpi.h"
	#include "y.tab.h"
	
%}

%%

[\t]	;

" " ;

[0-9]+ 	{ 	yylval = malloc(sizeof(node));
		 	mkNode(yylval,atoi(yytext),'I','$','$',NULL,NULL);
		 	return DIGIT;
		}

[-+*/=]	{
			yylval = malloc(sizeof(node));
			mkNode(yylval,0,'O',yytext[0],'$',NULL,NULL);
			return *yytext;
		}
[;] { return yytext[0];}

[\(\)\n]	{
				return yytext[0];
			}

[a-z]	{	yylval = malloc(sizeof(node));
		 	mkNode(yylval,0,'V','$',yytext[0],NULL,NULL);
		 	return ID;
		}
		
"read" 	{	yylval = malloc(sizeof(node));
		 	mkNode(yylval,0,'R','$','$',NULL,NULL);
		 	return READ;	
		}

"write" {	yylval = malloc(sizeof(node));
		 	mkNode(yylval,0,'W','$','$',NULL,NULL);
		 	return WRITE;	
		}

.		{ }
		
%%

int yywrap(void){
	return 1;
}