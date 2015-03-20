%{
#include<limits.h>
#include"lex.yy.c"
#include"exprtree.h"
int yylex();
#define OutFile "sim.xsm"
%}

%union{
	int ival;
	char *var;
	struct tnode *ptr;
};

%token <ival> NUM;
%token <var> ID;
%token READ WRITE IF THEN ELSE ENDIF WHILE DO ENDWHILE INTEGER BOOLEAN DECL ENDDECL LOGICAL_TRUE LOGICAL_FALSE AND OR NOT
%type <ptr> slist stmt expr  
%left ','
%right '='
%left EQ 
%left LT GT LE GE
%left AND OR NOT
%left '+' '-'
%left '*' '/' '%'
%left '(' ')' '[' ']' 

%%
 
program:	gdlist slist			{codegen($2); }		
	;

gdlist:		DECL dlist ENDDECL	
	;

dlist: dlist list					
	| list							
	;

list: INTEGER varlisti ';'			
	| BOOLEAN varlistb ';'			
	;

varlisti: varlisti ',' ID 			{InstallId("INTEGER",$3);}
	|   varlisti ',' ID '[' NUM ']'	{InstallArray("INTEGER",$3,$5);}
	|	ID 							{InstallId("INTEGER",$1);}
	|   ID '[' NUM ']' 				{InstallArray("INTEGER",$1,$3);}
	;

varlistb : varlistb ',' ID			{InstallId("BOOLEAN",$3);}
	| varlistb ',' ID '[' NUM ']' 	{InstallArray("BOOLEAN",$3,$5);}
	| ID							{InstallId("BOOLEAN",$1);}
	| ID '[' NUM ']'				{InstallArray("BOOLEAN",$1,$3);}
	;

slist : slist stmt  	{$$ = CreateSlistNode($1,$2);}
	| stmt				{$$ = $1;}
	;
	
stmt: ID '=' expr ';' 									{$$=CreateAssignNode(CreateIdNode($1),$3);}
	| ID '[' expr ']' '=' expr ';'						{$$=CreateAssignNode(CreateArrayNode($1,$3),$6);}
	| READ '(' ID ')' ';' 								{$$=CreateReadNode($3);}
	| READ '(' ID '[' expr ']' ')' ';'					{$$=CreateReadArrayNode($3,$5);}
	| WRITE '(' expr ')' ';'							{$$=CreateStmtNode("WRITE",$3,NULL,NULL);}
	| IF '(' expr ')' THEN slist ELSE slist ENDIF ';'	{$$=CreateStmtNode("IFELSE",$3,$6,$8);}
	| IF '(' expr ')' THEN slist ENDIF ';'				{$$=CreateStmtNode("IF",$3,$6,NULL);}
	| WHILE '(' expr ')' DO slist ENDWHILE ';'  		{$$=CreateStmtNode("WHILE",$3,$6,NULL);}
	| expr ';'											{$$=$1;}
	;
	

expr: expr '+' expr		{$$=CreateExprNode("+",$1,$3);}
    | expr AND expr     {$$=CreateExprNode("AND",$1,$3);}
    | expr OR expr      {$$=CreateExprNode("OR",$1,$3);}
	| NOT expr {$$=CreateExprNode("NOT",$2,NULL);}
	| expr '-' expr		{$$=CreateExprNode("-",$1,$3);}
	| expr '*' expr		{$$=CreateExprNode("*",$1,$3);}
	| expr '/' expr		{$$=CreateExprNode("/",$1,$3);}
        | expr '%' expr         {$$=CreateExprNode("%",$1,$3);}
	| '(' expr ')'		{$$=$2;}
	| expr LT expr  	{$$=CreateExprNode("<",$1,$3);}
	| expr GT expr  	{$$=CreateExprNode(">",$1,$3);}
	| expr LE expr  	{$$=CreateExprNode("<=",$1,$3);}
	| expr GE expr  	{$$=CreateExprNode(">=",$1,$3);}
	| expr EQ expr 		{$$=CreateExprNode("==",$1,$3);}
	| NUM 				{$$=CreateNumNode($1);}
	| ID 				{$$=CreateIdNode($1);}
	| ID '[' expr ']'   {$$=CreateArrayNode($1,$3);}
	| LOGICAL_TRUE 		{$$=CreateLogicalConst(1);}
	| LOGICAL_FALSE		{$$=CreateLogicalConst(0);}
	;	

%%

void yyerror( char * s)
{
	
	fprintf(stderr,"yyerror: %s line:%d \n",s,yylineno);
}


int main (int argc, char* argv[]) {
	if(argc > 1)
	{
		FILE *f = fopen(argv[1], "r");
		if(f)
			yyin = f;
	}
	
	fp = fopen(OutFile,"w+"); 
	fprintf(fp, "START\n");
	fclose(fp);
	fp = fopen(OutFile,"a+");
	yyparse();
	fprintf(fp,"HALT\n");
	fclose(fp);
	return 0;
}

/*int codegen(struct tnode* temp)
{	int temp_label;
	if(strcmp(temp->opt_type,"SLIST")==0)
	{
        codegen(temp->left);
	    codegen(temp->right);						
	}
	else if(strcmp(temp->opt_type,"IF")==0)
	{
		codegen(temp->left);
		label = label + 2;
		temp_label = label;
		fprintf(fp, "\nJZ R%d, LABEL%d",regcount-1,temp_label-2);
		regcount--;
	        codegen(temp->middle);
		fprintf(fp, "\nJMP LABEL%d",temp_label-1);
		fprintf(fp, "\nLABEL%d :",temp_label-2);
		label++;
	}
	else if(strcmp(temp->opt_type,"IFELSE")==0)
	{
                codegen(temp->left);
		label = label + 2;
	        temp_label = label;
                fprintf(fp, "\nJZ R%d, LABEL%d",regcount-1,temp_label-2);
		regcount--;
		codegen(temp->middle);
		fprintf(fp, "\nJMP LABEL%d",temp_label-1);
		fprintf(fp, "\nLABEL%d :",temp_label-2);
		label++;
		codegen(temp->right);
		fprintf(fp, "\nLABEL%d :",temp_label-1);
		label++;
	}
	else if(strcmp(temp->opt_type,"WHILE")==0)
	{
		fprintf(fp, "\nLABEL%d :",label);
		label=label+2;
		temp_label = label-1;
		codegen(temp->left);
		fprintf(fp, "\nJZ R%d, LABEL%d",regcount-1, temp_label);
		regcount--;
		codegen(temp->middle);
		fprintf(fp, "\nJMP LABEL%d",temp_label-1);
		fprintf(fp, "\nLABEL%d :", temp_label);
	}
	else if(strcmp(temp->opt_type,"LOGICALCONST")==0)
	{	fprintf(fp, "\nMOV R%d, %d", regcount-1, temp->val);
	        regcount--;
	}
	else if(strcmp(temp->opt_type,"+")==0)
	{
	 codegen(temp->left);
	 codegen(temp->right);
	 fprintf(fp, "\nADD R%d, R%d", regcount-2, regcount-1);
	 regcount--;   
	}
	else if(strcmp(temp->opt_type,"-")==0)
	{
	 codegen(temp->left);
	codegen(temp->right);
	fprintf(fp, "\nSUB R%d, R%d", regcount-2, regcount-1);
	regcount--;	 
	} 
	else if(strcmp(temp->opt_type,"*")==0)
	{
		 codegen(temp->left);
		 codegen(temp->right);
 		 fprintf(fp, "\nMUL R%d, R%d", regcount-2, regcount-1);
	         regcount--;
	}
	else if(strcmp(temp->opt_type,"/")==0)
	{
 	 codegen(temp->left);
	codegen(temp->right);
	fprintf(fp, "\nDIV R%d, R%d", regcount-2, regcount-1);
	regcount--;
	}
	else if(strcmp(temp->opt_type,">")==0)
	{
		codegen(temp->left);
		codegen(temp->right);
		fprintf(fp, "\nGT R%d, R%d", regcount-2, regcount-1);
		regcount--;
	
	}
	else if(strcmp(temp->opt_type,">=")==0)
	{
		codegen(temp->left);
		codegen(temp->right);
		fprintf(fp, "\nGE R%d, R%d", regcount-2, regcount-1);
		regcount--;
	}
	
	else if(strcmp(temp->opt_type,"<")==0)
	{
		codegen(temp->left);
		codegen(temp->right);
		fprintf(fp, "\nLT R%d, R%d", regcount-2, regcount-1);
		regcount--;
	}
	else if(strcmp(temp->opt_type,"<=")==0)
	{
		 codegen(temp->left);
		codegen(temp->right);
		fprintf(fp, "\nLE R%d, R%d", regcount-2, regcount-1);
		regcount--;
	}

	else if(strcmp(temp->opt_type,"==")==0)
	{	
		codegen(temp->left);
		codegen(temp->right);
		fprintf(fp, "\nEQ R%d, R%d", regcount-2, regcount-1);
		regcount--;
	}
	else if(strcmp(temp->opt_type,"NUM")==0)
	{	fprintf(fp, "\nMOV R%d, %d",regcount, temp->val);
	        regcount++;}
	else if(strcmp(temp->opt_type,"WRITE")==0)
	{	codegen(temp->left);
	        fprintf(fp, "\nOUT R%d",regcount-1);
	        regcount--;
        }
	else if(strcmp(temp->opt_type,"ID")==0)
	{	
          fprintf(fp, "\nMOV R%d, %d", regcount, *(temp->variable->binding));
	  regcount++;
	  fprintf(fp, "\nMOV R%d, R%d", regcount, regcount-1);
		regcount++;
		fprintf(fp, "\nMOV R%d, [R%d]", regcount-2, regcount-1);
		regcount--;
	}

	else if(strcmp(temp->opt_type,"ARRAY")==0)
	{
		fprintf(fp, "\nMOV R%d, %d",regcount, *(temp->variable->binding));
		regcount++;
		codegen(temp->left);
										// now regcount-1 stores the array index
		fprintf(fp, "\nADD R%d, R%d",regcount-2,regcount-1);
		regcount--;
		fprintf(fp, "\nMOV R%d, R%d", regcount, regcount-1);
		regcount++;
		fprintf(fp, "\nMOV R%d, [R%d]", regcount-2, regcount-1);
		regcount--;
		
	}
	else if(strcmp(temp->opt_type,"READ")==0)
	{	
		fprintf(fp, "\nIN R%d",regcount);
		regcount++;                
		fprintf(fp, "\nMOV R%d, %d", regcount, *(temp->variable->binding));
		regcount++;
		fprintf(fp, "\nMOV [R%d], R%d",regcount-1, regcount-2);
		regcount = regcount-2;
									
	}
	else if(strcmp(temp->opt_type,"READARR")==0)
	{
		fprintf(fp, "\nIN R%d",regcount);
		regcount++;
		if(temp->variable)	{
				fprintf(fp, "\nMOV R%d, %d",regcount, *(temp->variable->binding));
				regcount++;
				codegen(temp->left);
				fprintf(fp, "\nADD R%d, R%d",regcount-2,regcount-1);
				regcount--;			
		}
		
                 else
                        fprintf(fp , "invalid");
			fprintf(fp, "\nMOV [R%d], R%d",regcount-1, regcount-2);
			regcount = regcount-2; 
}
	else if(strcmp(temp->opt_type,"=")==0)
	{
		
         if(temp->left->variable->binding){
		if((temp->left->variable->size)>1)	{
			fprintf(fp, "\nMOV R%d, %d", regcount, *(temp->left->variable->binding));
			regcount++;
			codegen(temp->left->left);
			fprintf(fp, "\nADD R%d, R%d", regcount-2, regcount-1);
			regcount--;
		}
		else	{
			fprintf(fp, "\nMOV R%d, %d", regcount, *(temp->left->variable->binding));
			regcount++;
		}
	}
	codegen(temp->right);
	fprintf(fp, "\nMOV [R%d], R%d", regcount-2, regcount-1);
	regcount = regcount - 2;
					
    }
     else if(strcmp(temp->opt_type,"AND")==0)
	{
	 codegen(temp->left);
	 codegen(temp->right);
	 fprintf(fp, "\nMUL R%d, R%d", regcount-2, regcount-1);
	 regcount--;   
	}

     else if(strcmp(temp->opt_type,"OR")==0)
       {
        codegen(temp->left);
	codegen(temp->right);
	fprintf(fp, "\nMOV R%d, 2", regcount);
	regcount++;
	fprintf(fp, "\nADD R%d, R%d", regcount-3, regcount-2);
	fprintf(fp, "\nMOD R%d, R%d", regcount-3, regcount-1);
	regcount = regcount - 2;

      }
} 
*/


