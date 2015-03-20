%option noyywrap%{
	#include<stdio.h>
	#include<stdlib.h>
	
%}

number[0-9]+

%%

{number} {return atoi(yytext);}
 
%%

int main()
{
	int num = yylex();
	if(num%2 == 0)
		printf("Even Number\n");
	else
		printf("Odd Number\n");
	return 1;
}