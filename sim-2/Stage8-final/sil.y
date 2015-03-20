%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.yy.c"
#include "typecheck.h"
#include "codegen.h"
int yylex(void);
int vartype;
int val,arr;


#define OutFile "sim.xsm"

int codegen(tnode *);
void typecheck(tnode *,tnode *,tnode *);

struct Tnode *treecreate(int ,int ,char *,int ,tnode *, tnode *, tnode *,lsymbol *);

lsymbol *Llookup(char *);
void Linstall(char *,int);
gsymbol *Glookup(char *);
void Ginstall(char *,int,int);
void typecheck(tnode *,tnode *,tnode *);
int getreg();
int freereg();
int getlabel();

FILE *fp;

%}

%union {
	struct Tnode *ptr;
}

%token CONST ID READ WRITE INTEGER GT GE LT LE EQ AND OR NE BOOLEAN TRUE FALSE IF THEN ELSE ENDIF WHILE DO ENDWHILE RETURN DECL ENDDECL BEGINING END MAIN	NOT
%type <ptr> CONST ID '+' '-' '*' '/' '%' '=' READ WRITE Mainblock Stmt Body StmtList expr endif GT GE LT LE EQ AND OR NE TRUE FALSE IF WHILE RETURN NOT

%left OR
%left AND
%left EQ NE
%left LT LE GT GE
%left '+' '-'
%left '*' '/' '%'
%right NOT

%%

Prog	:		GDefblock Mainblock			{ codegen($2); }
		;

GDefblock :		DECL GDefList ENDDECL
		;

GDefList :
		 | GDefList GDecl
		;

GDecl :		Type GIdList ';'
		;

GIdList :	GId 
		|GIdList ',' GId 				// Future Chandra Sekhar be careful with commas
		;

GId :	ID '[' CONST ']'			{ Ginstall($1->NAME,vartype,$3->VALUE); }
		|ID								{ Ginstall($1->NAME,vartype,1); }
		;

Type :	INTEGER						{ vartype = INT_VARTYPE; }
		|BOOLEAN						{ 	vartype = BOOL_VARTYPE; }
		;

Mainblock :	INTEGER MAIN '(' ')' '{' LDefblock Body '}'		{ $$ = $7; }
		;

LDefblock :	DECL LDefList ENDDECL
		;

LDefList :
		|LDefList LDecl ';'
		;

LDecl :		Type LIdList
		;

LIdList :	LId 
		|LIdList ',' LId 
		;

LId :	ID						{ Linstall($1->NAME,vartype); }
		;

Body :		BEGINING StmtList RetStmt END			{ $$ = $2;} 
		;

StmtList :							{ $$ = NULL; }
		| StmtList Stmt ';'				{
									tnode *temp;
									temp = treecreate(DUMMY_TYPE,DUMMY_NODETYPE,NULL,0,NULL,NULL,NULL,NULL);
										temp->Ptr1=$1;
										temp->Ptr2=$2;
										$$=temp;
									}
		;

expr :		NOT expr					{
									typecheck($2,$1,NULL);
									$1->Ptr1 = $2;
									$$ = $1;
								}
		|expr '+' expr					{
									typecheck($1,$2,$3);
									$2->Ptr1=$1;$2->Ptr2=$3;
									$$=$2; 
								}
		|expr '-' expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr '*' expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr '/' expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr '%' expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr LT expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr LE expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr GT expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr GE expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr EQ expr					{
									typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr NE expr					{ typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr AND expr					{ typecheck($1,$2,$3);
									$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|expr OR expr					{ typecheck($1,$2,$3);
										$2->Ptr1=$1;$2->Ptr2=$3;
										$$=$2;
								}
		|'(' expr ')'					{ $$=$2;}
		|CONST						{ $$=$1;}
		| ID '[' expr ']'				{
									gsymbol *gtemp;
									gtemp = Glookup($1->NAME);
									if(gtemp)	{
										$1->Gentry = gtemp;
										if($3->TYPE==BOOLEAN_TYPE)
											yyerror("invalid array index");
										else if ($3->TYPE == VOID_TYPE){
											if ($3->NODETYPE==ID_NODETYPE)	{
											if($3->Gentry)	{
												if($3->Gentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
											else	{
												if($3->Lentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
											}
											else	{
												yyerror("not id type right child");
											}
										}
									}
									else	{
									printf("\nYou have not declared %s ",$1->NAME);
										yyerror("");
									}
									$1->Ptr1 = $3;
									$$ = $1;
								}
		|ID						{
								lsymbol *ltemp;
									gsymbol *gtemp;
									ltemp = Llookup($1->NAME);
									if(!ltemp)	{
										gtemp = Glookup($1->NAME) ;
										if(gtemp)	{
											$1->Gentry = gtemp;
											if((gtemp->SIZE)>1)	{
												yyerror("Invalid array index\n");
											}
										}
										else	{
											printf("\nYou have not declared %s ",$1->NAME);
											yyerror("");
										}
									}
									else	{
										$1->Lentry = ltemp;
									}
									$$ = $1;
								}
		|TRUE						{ $$=$1;}
		|FALSE						{ $$=$1;}
		;

endif :		ELSE StmtList ENDIF				{ $$=$2;}
		| ENDIF					{ $$=NULL; }
		;

Stmt :		READ '(' ID '[' expr ']' ')'			{
									gsymbol *gtemp;
									gtemp = Glookup($3->NAME);
									if(gtemp)	{
										$3->Gentry = gtemp;
										if($3->Gentry->TYPE==BOOL_VARTYPE)	{
											printf("ERR : Trying to read value for boolean variable %s \n",$3->NAME);
												yyerror("");
										}
										if($5->TYPE==BOOLEAN_TYPE)
											yyerror("invalid array index");
										else if(($5->TYPE==VOID_TYPE) && ($5->NODETYPE==ID_NODETYPE))	{
											if($5->Gentry)	{
												if($5->Gentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
											else	{
												if($5->Lentry->TYPE==BOOL_VARTYPE) 
													yyerror("invalid array index");
											}
										}
									}
									else	{
									printf("\nYou have not declared %s ",$3->NAME);
										yyerror("");
									}
									$3->Ptr1 = $5;
									$1->Ptr1 = $3;
									$$ = $1;
								}
		|READ '(' ID ')'				{
									lsymbol *ltemp;
									gsymbol *gtemp;
									ltemp = Llookup($3->NAME);
									if(!ltemp)	{
										gtemp = Glookup($3->NAME) ;
										if(gtemp)	{
											$3->Gentry = gtemp;
											if((gtemp->SIZE)>1)	{
												yyerror("\nInvalid array index");
											}
											if(gtemp->TYPE!=INT_VARTYPE)	{
												printf("ERR : Trying to read value for boolean variable %s \n",$3->NAME);
												yyerror("ERR : Trying to read value for boolean variable ");
										}
										}
										else	{
											printf("\nYou have not declared %s ",$3->NAME);
											yyerror("");
										}
									}
									else	{
										$3->Lentry = ltemp;
										if($3->Lentry->TYPE!=INT_VARTYPE)	{
											printf("ERR : Trying to read value for boolean variable %s \n",$3->NAME);
											yyerror("ERR : Trying to read value for boolean variable");
										}
									}
									$1->Ptr1 = $3;
									$$ = $1;
								}
		|WRITE '(' expr ')'				{
									if($3->TYPE==BOOLEAN_TYPE)
												yyerror("ERR : Writing boolean value");
										if($3->TYPE==VOID_TYPE)	{
											if($3->NODETYPE==ID_NODETYPE)	{
												if($3->Lentry)	{
												if($3->Lentry->TYPE==BOOL_VARTYPE)	{
													yyerror("ERR : Writing boolean value");
												}
											}
											else if($3->Gentry)	{
												if($3->Gentry->TYPE==BOOL_VARTYPE)	{
													yyerror("ERR : writing boolean value");
												}
											}
										}
									}
									$1->Ptr1=$3;
										$$ = $1;
								}
		|IF '(' expr ')' THEN StmtList endif		{
									typecheck($3,$1,NULL);
									$1->Ptr1=$3;
									$1->Ptr2=$6;
									$1->Ptr3=$7;
									$$=$1;
								}
		|WHILE '(' expr ')' DO StmtList ENDWHILE	{
									typecheck($3,$1,NULL);
										$1->Ptr1=$3;
										$1->Ptr2=$6;
										$$=$1;
								}
		|ID '[' expr ']' '=' expr			{
									gsymbol *gtemp;
									gtemp = Glookup($1->NAME);
									if(gtemp)	{
										$1->Gentry = gtemp;
										if($3->TYPE==BOOLEAN_TYPE)
											yyerror("ERR : invalid array index");
										else if (($3->TYPE==VOID_TYPE) && ($3->NODETYPE=ID_NODETYPE))	{
											if($3->Gentry)	{
												if($3->Gentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
											else	{
												if($3->Lentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
										}
									}
									else	{
									printf("\nYou have not declared %s ",$1->NAME);
										yyerror("");
									}
									typecheck($1,$5,$6);
									$1->Ptr1 = $3;
									$5->Ptr1 = $1;
									$5->Ptr2 = $6;
									$$ = $5;
								}
		|ID '=' expr					{
								lsymbol *ltemp;
									gsymbol *gtemp;
									ltemp = Llookup($1->NAME);
									if(!ltemp)	{
										gtemp = Glookup($1->NAME) ;
										if(gtemp)	{
											$1->Gentry = gtemp;
											if((gtemp->SIZE)>1)	{
												yyerror("\nInvalid array index");
											}
										}
										else	{
											printf("\nYou have not declared %s ",$1->NAME);
											yyerror("");
										}
									}
									else	{
										$1->Lentry = ltemp;
									}
									typecheck($1,$2,$3);
									$2->Ptr1=$1;
									$2->Ptr2=$3;
									$$ = $2;
								}
		;

RetStmt :	RETURN	expr ';'				{ typecheck($2,$1,NULL); }
		;


%%

int main (int argc, char* argv[]) {
	if(argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if(fp)
			yyin = fp;
	}
	fp = fopen(OutFile,"w+"); 
	fprintf(fp, "START");
	fclose(fp);
	fp = fopen(OutFile,"a+");
	yyparse();
	fprintf(fp, "\nHALT");
	fclose(fp);
	return 0;
}


struct Tnode *treecreate(int type,int nodetype,char *name,int value,tnode *ptr1, tnode *ptr2, tnode *ptr3,lsymbol *lentry) {
	tnode *temp=(tnode *)malloc(sizeof(tnode));
	temp->TYPE=type;
	temp->NODETYPE=nodetype;
	temp->NAME=name;
	temp->VALUE=value;
	temp->Ptr1=ptr1;
	temp->Ptr2=ptr2;
	temp->Ptr3=ptr3;
	temp->Lentry=lentry;
	return(temp);
}
