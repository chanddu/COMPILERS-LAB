%option yylineno
%{
#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
#include<string.h>
void yyerror(char *s);

%}

digit [0-9]
%%
"<"			{return LT;}
">"			{return GT;}
"<="		{return LE;}
">="		{return GE;}
"=="		{return EQ;}
{digit}+	{yylval.ival = atoi(yytext); return NUM;}
"TRUE"		{return LOGICAL_TRUE;}
"FALSE"		{return LOGICAL_FALSE;}
"read" 		{return READ;}
"write"		{return WRITE;}
"if"		{return IF;}
"then"		{return THEN;}
"else"		{return ELSE;}
"endif"		{return ENDIF;}
"while"		{return WHILE;}
"do"		{return DO;}
"endwhile"	{return ENDWHILE;}
"decl"		{return DECL;}
"enddecl"	{return ENDDECL;}
"integer"	{return INTEGER;}
"boolean"	{return BOOLEAN;}
"AND"           {return AND;}
"OR"           {return OR;}
"NOT" 		{return NOT;}
[_a-zA-Z][a-zA-Z0-9]*		{ yylval.var = strdup(yytext); return ID;}
[-+*/,();=\[\]%]	{return *yytext;}
[ \t\n] 		{}
.			{printf("%s is invalid character\n",yytext);exit(1);}
%%

int yywrap()
{
	return 1;
}


