/* Simple calculator v1.2 */

%{
	#include "y.tab.h"
	void yyerror(char *);
	#define YYSTYPE float;
%}

%%

[\t ]+ ;

[0-9]+"."[0-9]+		{
				yylval = atof(yytext);
				return INTEGER;
			}

[-+*\/\(\)\n]	{
				return (float) yytext[0];
				}

. { yyerror("Unknown input"); }

%%

int yywrap(void) {
	return 1;
}

