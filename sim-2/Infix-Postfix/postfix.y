/* Infix to Postfix */
%{ 

    #include <stdio.h> 
    #include<stdlib.h>
    int yylex(void);
    #include<math.h>

%} 

%token INTEGER

%left '+' '-'

%left '*' '/'

%left '^'
		 
%% 
program:
		program expr '\n'  {exit(1);} 
		| '\n' |
		;
expr:
		INTEGER    {printf("%d",$$);} 
		| expr '+' expr { printf("+"); }
		| expr '-' expr { printf("-"); }
		| expr '*' expr { printf("*"); }
		| expr '/' expr { printf("/"); }
		| '(' expr ')' 
		| expr '^' expr { printf("^"); }
		;

%% 
    
int yyerror(char *s) { 
	printf("%s",s); 
	return 0;
} 
int main(){ 
	yyparse(); 
	return 1; 
} 