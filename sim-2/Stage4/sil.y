%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.yy.c"

int yylex(void);
int evaltree(tnode *);
int buffer[26];
int val,buf;
struct Tnode *treecreate(int ,int ,char ,int ,tnode *, tnode *, tnode *);


%}

%union {
	struct Tnode *ptr;
}

%token CONST ID READ WRITE GT LT EQ IF THEN ELSE ENDIF WHILE DO ENDWHILE
%type <ptr> CONST ID '+' '-' '*' '/' '%' '=' READ WRITE Stmt StmtList expr endif GT LT EQ IF WHILE

%left EQ
%left LT GT
%left '+' '-'
%left '*' '/'

%%

program	: StmtList '\n'		{ evaltree($1); exit(1); }

StmtList :
		 StmtList Stmt ';'				{
									tnode *temp;
									temp = treecreate(DUMMY_TYPE,DUMMY_NODETYPE,'$',0,NULL,NULL,NULL);
										temp->Ptr1=$1;
										temp->Ptr2=$2;
										$$=temp;
									}
		| Stmt ';'			{ $$ = $1;}
		;
		
Stmt :
		READ '(' ID ')'		{		
									$1->Ptr1 = $3;
									$$ = $1;
							}
							
		|WRITE '(' expr ')'	{
								$1->Ptr1=$3;
								$$ = $1;
							}
		|IF '(' expr ')' THEN StmtList endif		{
									$1->Ptr1=$3;
									$1->Ptr2=$6;
									$1->Ptr3=$7;
									$$=$1;
								}
								
		|ID '=' expr		{
								$2->Ptr1=$1;
								$2->Ptr2=$3;
								$$ = $2;
							}
		|WHILE '(' expr ')' DO StmtList ENDWHILE	{
										$1->Ptr1=$3;
										$1->Ptr2=$6;
										$$=$1;
								}
		;
		
endif :		ELSE StmtList ENDIF				{ $$=$2;}
		| ENDIF					{ $$=NULL; }
		;
		
expr :	expr '+' expr		{
								$2->Ptr1=$1;$2->Ptr2=$3;
								$$=$2; 
							}
		|expr '-' expr		{
								$2->Ptr1=$1;$2->Ptr2=$3;
								$$=$2;
							}
		|expr '*' expr		{
								$2->Ptr1=$1;$2->Ptr2=$3;
								$$=$2;
							}
		|expr '/' expr		{
								$2->Ptr1=$1;$2->Ptr2=$3;
								$$=$2;
							}
		|expr LT expr		{
								$2->Ptr1=$1;$2->Ptr2=$3;
								$$=$2;
							}
		|expr GT expr		{
								$2->Ptr1=$1;$2->Ptr2=$3;
								$$=$2;
							}
		|expr EQ expr		{
								$2->Ptr1=$1;$2->Ptr2=$3;
								$$=$2;
							}
		|'(' expr ')'		{ $$=$2;}
		
		| ID				{ $$=$1;}
		
		| CONST				{ $$=$1; }
		
		;

%%

int main (void) {
	yyparse();
	return 0;
}

int evaltree(tnode *temp){
	int temp_label;
	if(temp){
		switch(temp->TYPE){
			case DUMMY_TYPE :	
						evaltree(temp->Ptr1);
						evaltree(temp->Ptr2);
						break;
			case VOID_TYPE : 
				switch(temp->NODETYPE){
					case READ_NODETYPE : 
							printf("READ %c:",temp->Ptr1->NAME);
							scanf("%d", &buf);
							buffer[(int)temp->Ptr1->NAME - 'a'] = buf;
							break;
					case WRITE_NODETYPE :
								printf("%d\n",evaltree(temp->Ptr1));
								break;
					case ID_NODETYPE :
								return buffer[(int)temp->NAME - 'a'];
								break;
					case IF_NODETYPE :
								if(evaltree(temp->Ptr1)==1)	{
									evaltree(temp->Ptr2);
								}
								else	{
									evaltree(temp->Ptr3);
								}
								break;
					case WHILE_NODETYPE : 
								while(evaltree(temp->Ptr1)==1)	{
									evaltree(temp->Ptr2);
								}
								break;
				}
				break;
			case INT_TYPE :
				switch(temp->NODETYPE){
				case NUMBER_NODETYPE :
						return(temp->VALUE);
						break;
				case PLUS_NODETYPE :
						return(evaltree(temp->Ptr1)+evaltree(temp->Ptr2));
						break;
				case MINUS_NODETYPE :
						return(evaltree(temp->Ptr1)-evaltree(temp->Ptr2));
						break;
				case MULT_NODETYPE :
						return(evaltree(temp->Ptr1)*evaltree(temp->Ptr2));
						break;
				case DIV_NODETYPE :
						return(evaltree(temp->Ptr1)/evaltree(temp->Ptr2));
						break;
				case ASSIGN_NODETYPE :
						buffer[(int)temp->Ptr1->NAME - 'a'] = evaltree(temp->Ptr2);
							break;
				}
				break;
			case BOOLEAN_TYPE : 
				switch(temp->NODETYPE){
					case LT_NODETYPE :
							val=((evaltree(temp->Ptr1))<(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
					case GT_NODETYPE :
							val=((evaltree(temp->Ptr1))>(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
					case EQ_NODETYPE :
							val=((evaltree(temp->Ptr1))==(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				}
			break;
		}
	}
}

void yyerror (char *msg)	{
	fprintf (stderr, "%s\n", msg);
	exit(1);
}

struct Tnode *treecreate(int type,int nodetype,char name,int value,tnode *ptr1, tnode *ptr2, tnode *ptr3) {
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