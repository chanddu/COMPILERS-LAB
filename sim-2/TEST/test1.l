%option noyywrap

number [0-8]+

%%
 
{number} {return atoi(yytext);}
 
%%
 
int main()
{
	int num = yylex();
	return 1;
}