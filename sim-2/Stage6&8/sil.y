%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.yy.c"
int yylex(void);
void yyerror(char *);

tnode	*thead = NULL;

lsymbol *lhead = NULL;
lsymbol *llast = NULL;

gsymbol *ghead = NULL;
gsymbol *glast = NULL;

int vartype;
int label=1,regcount=0,mem_loc;
int val,arr;

int evaltree(tnode *);
void typecheck(tnode *,tnode *,tnode *);

struct Tnode *treecreate(int ,int ,char *,int ,tnode *, tnode *, tnode *,lsymbol *);

lsymbol *Llookup(char *);
void Linstall(char *,int);
gsymbol *Glookup(char *);
void Ginstall(char *,int,int);
void typecheck(tnode *,tnode *,tnode *);

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

Prog	:		GDefblock Mainblock			{ return evaltree($2); }
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
	yyparse();
	return 0;
}

void yyerror (char *msg)	{
	fprintf (stderr, "%s\n", msg);
	exit(1);
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

lsymbol *Llookup(char *name)	{
	lsymbol *temp = lhead;
	while(temp)	{
		if(strcmp(name,temp->NAME)==0) 
			return temp;
		temp = temp->NEXT;
	}
	return NULL;
}

void typecheck(tnode *t1,tnode *t2,tnode *t3) {
	int flag = 1; int type;
	switch(t2->TYPE)	{
		case INT_TYPE :
					switch(t2->NODETYPE)	{
						case PLUS_NODETYPE :
						case MINUS_NODETYPE :
						case MULT_NODETYPE :
						case DIV_NODETYPE :
						case MODULO_NODETYPE :
									if((t1->TYPE==BOOLEAN_TYPE)||(t3->TYPE==BOOLEAN_TYPE))		// no boolean for -+* and div
										flag=0;
									if(t1->TYPE==VOID_TYPE)	{
										if(t1->Lentry!=NULL)	{							//check for entry in local symbol table
											if(t1->Lentry->TYPE!=INT_VARTYPE)
												flag=0;
										}
									else{
										if(t1->Gentry->TYPE!=INT_VARTYPE)
											flag=0;
									}
									}
									if(t3->TYPE==VOID_TYPE)	{
										if(t3->NODETYPE!=ID_NODETYPE)
											flag=0;
									if(t3->Lentry)	{
										if(t3->Lentry->TYPE!=INT_VARTYPE)
											flag=0;
									}
									else	{
										if(t3->Gentry->TYPE!=INT_VARTYPE)
											flag=0;
									}
									}
									break;
					case ASSIGN_NODETYPE :
									if(t1->Lentry!=NULL)	{
										type=t1->Lentry->TYPE;
									}
									else	{
										type=t1->Gentry->TYPE;
									}
									if(type==INT_VARTYPE) { 
										if(t3->TYPE==BOOLEAN_TYPE)	{
											flag=0;
										}
										else if(t3->TYPE==VOID_TYPE)	{
											if(t3->Lentry)	{
												if(t3->Lentry->TYPE==BOOL_VARTYPE)	{
													flag=0;
												}
											}
											else	{
												if(t3->Gentry->TYPE==BOOL_VARTYPE)	{
													flag=0;
												}
											}
										}
									}
									else	{
										if(t3->TYPE==INT_TYPE)	{
											flag=0;
										}
										else if(t3->TYPE==VOID_TYPE) {
										if(t3->Lentry) {
											if(t3->Lentry->TYPE==INT_VARTYPE)	{
												flag=0;
											}
										}
										else	{
											if(t3->Gentry->TYPE==INT_VARTYPE)	{
												flag=0;
											}
										}
										}
									}
									if(!flag)	{
										printf("ERR : Type mismatch for %s \n",t1->Lentry->NAME);
										yyerror("");
									}
									break;
					}
					break;
		case BOOLEAN_TYPE :
					switch(t2->NODETYPE)	{
						case LT_NODETYPE :
						case LE_NODETYPE :
						case GT_NODETYPE :
						case GE_NODETYPE :
						case EQ_NODETYPE :
						case NE_NODETYPE :
										if((t1->TYPE==BOOLEAN_TYPE)||(t3->TYPE==BOOLEAN_TYPE))
												flag=0;

											else if(t1->TYPE==VOID_TYPE)	{
								if(t1->NODETYPE!=ID_NODETYPE)
											flag=0;

										if(t1->Lentry)	{

											if(t1->Lentry->TYPE!=INT_VARTYPE)
												flag=0;

										}
										else	{
											if(t1->Gentry->TYPE!=INT_VARTYPE)
												flag=0;

										}
										}

										else if(t3->TYPE==VOID_TYPE)	{
									if(t3->NODETYPE!=ID_NODETYPE)
											flag=0;

										if(t3->Lentry)	{

											if(t3->Lentry->TYPE!=INT_VARTYPE)
												flag=0;
										}
										else	{
											if(t3->Gentry->TYPE!=INT_VARTYPE)
												flag=0;
										}
											}
											break;
						case AND_NODETYPE :
						case OR_NODETYPE :
										if((t1->TYPE==INT_TYPE)||(t3->TYPE==INT_TYPE))
											flag = 0;
										else if(t1->TYPE==VOID_TYPE)	{
								if(t1->NODETYPE!=ID_NODETYPE)
											flag=0;

										if(t1->Lentry)	{
											if(t1->Lentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
										else	{
											if(t1->Gentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
									}
										else if(t3->TYPE==VOID_TYPE)	{
									if(t3->NODETYPE!=ID_NODETYPE)
											flag=0;

										if(t3->Lentry)	{
											if(t3->Lentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
										else	{
											if(t3->Gentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
											}
											break;

							case NOT_NODETYPE :
										if(t1->TYPE==INT_TYPE)
											flag=0;
										else if(t1->TYPE==VOID_TYPE)	{

											if(t1->NODETYPE!=ID_NODETYPE)	{
												flag=0;
											}

											else {

												if(t1->Lentry)	{

													if(t1->Lentry->TYPE!=BOOL_VARTYPE)
														flag=0;
												}

												else if(t1->Gentry)	{
													if(t1->Gentry->TYPE!=BOOL_VARTYPE)
														flag=0;
												}

											}
										}
										break;
					}
					break;
		case VOID_TYPE :
					switch(t2->NODETYPE)	{
						case IF_NODETYPE :
										if(t1->TYPE==INT_TYPE)
											flag=0;
										else if(t1->TYPE==VOID_TYPE)	{
											if(t1->NODETYPE!=ID_NODETYPE)
											flag=0;
										if(t1->Lentry)	{
											if(t1->Lentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
										else {

										if(t1->Gentry->TYPE!=BOOL_VARTYPE)
											flag=0;
										}
									}
										break;
						case WHILE_NODETYPE :
										if(t1->TYPE==INT_TYPE)
											flag=0;
										else if(t1->TYPE==VOID_TYPE)	{
											if(t1->NODETYPE!=ID_NODETYPE)
											flag=0;
										if(t1->Lentry)	{
											if(t1->Lentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
										else {

										if(t1->Gentry->TYPE!=BOOL_VARTYPE)
											flag=0;
										}
									}
										break;
						case RETURN_NODETYPE :
									if(t1->TYPE==BOOLEAN_TYPE)	{
										flag = 0;
									}
									else if(t1->TYPE==VOID_TYPE)	{
										if(t1->NODETYPE!=ID_NODETYPE)	{
											flag = 0;
										}
										if(t1->Lentry)	{
											if(t1->Lentry->TYPE!=INT_VARTYPE)	{
											flag=0;
											}
										}
										else {
											if(t1->Gentry->TYPE!=INT_VARTYPE)
												flag=0;
										}
									}
					}
					break;
	}
	if(!flag)	{
		printf("ERR : Type mismatch at %d %d\n",t2->TYPE,t2->NODETYPE	);
		yyerror("");
	}
}

void Linstall(char *name,int type)	{
	lsymbol *temp;
	temp = Llookup(name);
	if(temp)	{
		printf("You have already declared %s ",name);
		yyerror("");
	}
	else	{
		temp = (lsymbol *)malloc(sizeof(lsymbol));
		temp->NAME = name;
		temp->TYPE = type;
		temp->BINDING = (int *)malloc(sizeof(int));
		*(temp->BINDING) = mem_loc;
		mem_loc = mem_loc + 1;
		temp->NEXT = NULL;
		if(lhead==NULL)
			lhead = llast = temp;
		else	{
			llast->NEXT = temp;
			llast = temp;
		}
	}
}

gsymbol *Glookup(char *name)	{
	gsymbol *temp = ghead;
	while(temp)	{
		if(strcmp(name,temp->NAME)==0) 
			return temp;
		temp = temp->NEXT;
	}
	return NULL;
}

void Ginstall(char *name,int type,int size)	{
	gsymbol *temp;
	temp = Glookup(name);
	if(temp)	{
		printf("You have already declared %s ",name);
		yyerror("");
	}
	else	{
		temp = (gsymbol *)malloc(sizeof(gsymbol));
		temp->NAME = name;
		temp->TYPE = type;
		temp->SIZE = size;
		temp->BINDING = (int *)malloc(sizeof(int));
		*(temp->BINDING) = mem_loc;
		mem_loc = mem_loc+size;
		temp->NEXT = NULL;
		if(ghead==NULL)
			ghead = glast = temp;
		else	{
			glast->NEXT = temp;
			glast = temp;
		}
	}
}

int evaltree(tnode *temp)	{
	int temp_label,*addr;
	if(temp)	{
		switch(temp->TYPE)	{
			case DUMMY_TYPE :	evaltree(temp->Ptr1);
						evaltree(temp->Ptr2);
						break;
			case VOID_TYPE : 
				switch(temp->NODETYPE)	{
					case READ_NODETYPE : 
								printf("READ %s:",temp->Ptr1->NAME);
								scanf("%d",&val);
								if(temp->Ptr1->Gentry)	{
									if((temp->Ptr1->Gentry->SIZE)>1)	{
										arr = evaltree(temp->Ptr1->Ptr1);         // array Index
										addr = temp->Ptr1->Gentry->BINDING;
										addr = addr + arr;
										*addr = val;
									}
									else	{
										*(temp->Ptr1->Gentry->BINDING) = val;
									}
								}
								else if(temp->Ptr1->Lentry)	{
									*(temp->Ptr1->Lentry->BINDING)=val;
								}
								else
									printf("\nNo memory allocated for var");
								//temp->Ptr1->VALUE = val;
								break;
					case WRITE_NODETYPE :
								printf("%d\n",evaltree(temp->Ptr1));
								break;
					case ID_NODETYPE :
								if(temp->Gentry)	{
									if((temp->Gentry->SIZE)>1)	{
										arr = evaltree(temp->Ptr1);
										if((arr<0)||(arr>=(temp->Gentry->SIZE)))	{
											yyerror("Invalid array index");
										}
										addr = temp->Gentry->BINDING;
										addr = addr+arr;
									}
									else	{
										addr = temp->Gentry->BINDING;
									}
								}
								else if(temp->Lentry)	{
									addr = temp->Lentry->BINDING;
								}
								else 
									printf("No memory allocated for variable\n");
								return(*addr);
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
					case RETURN_NODETYPE :
								return evaltree(temp->Ptr1);
								break;
					}
							break;
			case INT_TYPE : 
				switch(temp->NODETYPE)	{
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
							if(temp->Ptr1->Lentry)
								*(temp->Ptr1->Lentry->BINDING) = evaltree(temp->Ptr2);
							else if(temp->Ptr1->Gentry)	{
								if((temp->Ptr1->Gentry->SIZE)>1)	{
									addr = temp->Ptr1->Gentry->BINDING;
									addr = addr + evaltree(temp->Ptr1->Ptr1);
									*addr = evaltree(temp->Ptr2);
								}
								else{
									*(temp->Ptr1->Gentry->BINDING) = evaltree(temp->Ptr2);
								}
							}
							break;
				case MODULO_NODETYPE :	
							return(evaltree(temp->Ptr1)%evaltree(temp->Ptr2));
							break;
				}
				break;
			case BOOLEAN_TYPE : 
				switch(temp->NODETYPE)	{
				case NOT_NODETYPE :	
							val = evaltree(temp->Ptr1);
							return(!val);
							break;
				case LT_NODETYPE :
							val=((evaltree(temp->Ptr1))<(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case LE_NODETYPE :
							val=((evaltree(temp->Ptr1))<=(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case GT_NODETYPE :
							val=((evaltree(temp->Ptr1))>(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case GE_NODETYPE :
							val=((evaltree(temp->Ptr1))>=(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case EQ_NODETYPE :
							val=((evaltree(temp->Ptr1))==(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case NE_NODETYPE :
							val=((evaltree(temp->Ptr1))!=(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case AND_NODETYPE :
							val=((evaltree(temp->Ptr1))&&(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case OR_NODETYPE :
							val=((evaltree(temp->Ptr1))||(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case TRUE_NODETYPE :
							return(1);
							break;
				case FALSE_NODETYPE :
							return(0);
							break;
					}
					break;
		}
	}
}

