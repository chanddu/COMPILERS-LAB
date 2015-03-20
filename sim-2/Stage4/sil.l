%{
#include<stdlib.h>
#include<string.h>
#include "y.tab.h"
#include "sil.h"

void yyerror(char *);

typedef struct Tnode tnode;
tnode *TreeCreate(int ,int ,char ,int ,tnode *, tnode *, tnode *) ;

%}

%%

" "		{ }

"-"			{	yylval.ptr=TreeCreate(INT_TYPE,MINUS_NODETYPE,'$',0,NULL,NULL,NULL);
				return *yytext;

			}

[;}{,)('\n']			{
				return *yytext;
			}

		
[0-9]+			{	
				yylval.ptr = TreeCreate(INT_TYPE,NUMBER_NODETYPE,'$',atoi(yytext),NULL,NULL,NULL);
				return CONST;
			}
				
"read"			{	
				yylval.ptr = TreeCreate(VOID_TYPE,READ_NODETYPE,'$',0,NULL,NULL,NULL);
				return READ;
			}
				
"write"			{	
				yylval.ptr = TreeCreate(VOID_TYPE,WRITE_NODETYPE,'$',0,NULL,NULL,NULL);
				return WRITE;
			}

			
"if"			{	
				yylval.ptr = TreeCreate(VOID_TYPE,IF_NODETYPE,'$',0,NULL,NULL,NULL);
				return IF;
			}

"then"			{	return THEN; 		}

"else"			{	return ELSE; 		}

"endif"			{	return ENDIF; 		}

"while"			{	
				yylval.ptr = TreeCreate(VOID_TYPE,WHILE_NODETYPE,'$',0,NULL,NULL,NULL);
				return WHILE;
			}

"do"			{	return DO; 		}

"endwhile"		{	return ENDWHILE; 	}

[a-z]			{	
				char name =  yytext[0];
				yylval.ptr = TreeCreate(VOID_TYPE,ID_NODETYPE,name,0,NULL,NULL,NULL);
				printf("ID\n");
				return ID;
			}

"<"			{	yylval.ptr = TreeCreate(BOOLEAN_TYPE,LT_NODETYPE,'$',0,NULL,NULL,NULL);
				return LT;
			}


">"			{
				yylval.ptr = TreeCreate(BOOLEAN_TYPE,GT_NODETYPE,'$',0,NULL,NULL,NULL);
				return GT;
			}

"=="			{
				yylval.ptr = TreeCreate(BOOLEAN_TYPE,EQ_NODETYPE,'$',0,NULL,NULL,NULL);
				return EQ;
			}

[+%*/=]			{	
				int temp;
				switch(*yytext) {
					case '+' : temp=PLUS_NODETYPE;	break;
					case '*' : temp=MULT_NODETYPE;	break;
					case '/' : temp=DIV_NODETYPE;	break;
					case '=' : temp=ASSIGN_NODETYPE;break;
				}
				yylval.ptr=TreeCreate(INT_TYPE,temp,'$',0,NULL,NULL,NULL);
				printf ("%c\n",yytext[0]);
				return *yytext;
			}

.			{}	

%%

int yywrap(void) {
	return(1);
}

tnode *TreeCreate(int type,int nodetype,char name,int value,tnode *ptr1, tnode *ptr2, tnode *ptr3) {
	tnode *temp=(tnode *)malloc(sizeof(tnode));
	temp->TYPE=type;
	temp->NODETYPE=nodetype;
	temp->NAME=name;
	temp->VALUE=value;
	temp->Ptr1=ptr1;
	temp->Ptr2=ptr2;
	temp->Ptr3=ptr3;
	return(temp);
 }
