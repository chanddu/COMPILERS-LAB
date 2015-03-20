#include<stdio.h>
#include<stdlib.h>
#include"Gsymbol.h"

#define TRUE 1;
#define FALSE 0;

char keywords[15][50] = {"if","then","else","endif","while","do","endwhile","decl","enddecl","read","write","integer","boolean","TRUE","FALSE"};
int sizeKeywords = 15;
int regcount=-1;
int label=-1;
FILE *fp;
int getreg()
{
	regcount++;
	if(regcount>=8)
	{
		printf("register count is exceeded\n");
		exit(1);
	}
	return regcount;
}

int freereg()
{
	regcount--;
	if(regcount < -1)
	{
		printf("trying to free invalid register\n");
		exit(1);
	}
}

int getlabel()
{
	label++;
	return label;
}


struct tnode
{
	char *opt_type;						//operation type
	int val;							// value 
	int type;							// type->  0=bool,1=int,2=void,3=others
	struct gsymbol *variable;			// pointer to variable name
	struct tnode *left;					// left tree node
	struct tnode *middle;				// middle tree node (in case of if then else endif)
	struct tnode *right; 				//right tree node
};

/*
struct tnode* CreatePgmNode(struct tnode* left, struct tnode* right)
{
	struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));
	temp->opt_type = "PGM";
	temp->val=0;
	temp->type=3;
	temp->variable = NULL;
	temp->left=left;
	temp->right=right;
	temp->middle = NULL;
	return temp;
}
*/

struct tnode* CreateLogicalConst(int type)
{
	struct tnode* temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->opt_type = "LOGICALCONST";

	if(type == 1)
		temp->val=1;
	else
		temp->val=0;
	
	temp->type=0;
	temp->variable=NULL;
	temp->left=NULL;
	temp->right=NULL;
	temp->middle=NULL;
	return temp;
}

struct tnode* CreateDlistNode(struct tnode* left, struct tnode* right)
{
	struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));
	temp->opt_type = "DLIST";
	temp->val=0;
	temp->type=3;
	temp->variable = NULL;
	temp->left=left;
	temp->right=right;
	temp->middle = NULL;
	return temp;
}

void InstallId(char* type, char* varname)
{
	int i,flag=0;
	for(i=0;i<sizeKeywords;i++)
	{
		if(strcmp(keywords[i],varname)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("variable name %s is a keyword\n",varname);
		exit(1);
	}
	if(glookup(varname)==NULL)
		if(strcmp(type,"INTEGER")==0)
			ginstall(varname, 1,1);
		else 
			ginstall(varname,0,1);
	else
	{
		printf("variable name %s has already been declared\n",varname);
		exit(1);
	}
}

void InstallArray(char* type, char* varname,int size)
{
	int i,flag=0;
	for(i=0;i<sizeKeywords;i++)
	{
		if(strcmp(keywords[i],varname)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("variable name %s is a keyword\n",varname);
		exit(1);
	}
	if(glookup(varname)==NULL)
		if(strcmp(type,"INTEGER")==0)
			ginstall(varname, 1,size);
		else
			ginstall(varname,0,size);
	else
	{
		printf("variable name %s has already been declared\n",varname);
		exit(1);
	}
}

struct tnode* CreateSlistNode(struct tnode* left, struct tnode* right)
{
	struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));
	temp->opt_type = "SLIST";
	temp->val=0;
	temp->type=3;
	temp->variable = NULL;
	temp->left=left;
	temp->right=right;
	temp->middle = NULL;
	return temp;
}

struct tnode* CreateReadNode(char* varname)
{
	struct tnode* temp = (struct tnode*)malloc(sizeof(struct  tnode));
	struct gsymbol* temp1 = glookup(varname);
	if(temp1 == NULL)
	{
		printf("variable name %s is not declared\n",varname);
		exit(1);
	}
	temp->opt_type="READ";
	temp->val=0;
	temp->type=3;
	temp->variable = temp1;
	temp->left=NULL;
	temp->right=NULL;
	temp->middle=NULL;
	return temp;
}

struct tnode* CreateReadArrayNode(char* varname, struct tnode* left)
{
	struct tnode* temp = (struct tnode*)malloc(sizeof(struct  tnode));
	struct gsymbol* temp1 = glookup(varname);
	if(temp1 == NULL)
	{
		printf("variable name %s is not declared\n",varname);
		exit(1);
	}
	temp->opt_type="READARR";
	temp->val=0;
	temp->type=3;
	temp->variable = temp1;
	temp->left=left;
	temp->right=NULL;
	temp->middle=NULL;
	return temp;
}


struct tnode* CreateStmtNode(char *opt, struct tnode* left, struct tnode* middle, struct tnode* right)
{
	struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));	
	temp->opt_type = opt;
	temp->val=0;
	temp->type=3;
	temp->variable=NULL;
	temp->left=left;
	temp->right=right;
	temp->middle=middle;
	return temp;
}

struct tnode* CreateAssignNode(struct tnode* left, struct tnode* right)
{
	if(left->variable->type == right->type)
	{
		struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));	
		temp->opt_type = "=";
		temp->val=0;
		temp->type=3;
		temp->variable=NULL;
		temp->left=left;
		temp->right=right;
		temp->middle=NULL;
		return temp;
	}
	else
	{
			printf("type conflict for %s\n",left->variable->name);
			exit(1);
	}
}

struct tnode* CreateExprNode( char *opt, struct tnode* left, struct tnode* right)
{
	if((strcmp(opt,"+")==0) || (strcmp(opt,"-")==0) || (strcmp(opt,"*")==0) || (strcmp(opt,"/")==0)||(strcmp(opt,"%")==0))
	{
		if((left->type == right->type) && (left->type == 1))
		{
			struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));	
			temp->opt_type = opt;
			temp->val=0;
			temp->type=1;
			temp->variable=NULL;
			temp->left=left;
			temp->right=right;
			temp->middle=NULL;
			return temp;
		}
		else
		{
			printf("type conflict for %s\n",opt);
			exit(1);
		}
	}
	else if((strcmp(opt,"<")==0) || (strcmp(opt,">")==0)|| (strcmp(opt,"<=")==0)||(strcmp(opt,">=")==0)||(strcmp(opt,"==")==0))
	{
		if(left->type == right->type  && (left->type==0 || left->type == 1))
		{
			struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));	
			temp->opt_type = opt;
			temp->val=0;
			temp->type=0;
			temp->variable=NULL;
			temp->left=left;
			temp->right=right;
			temp->middle=NULL;
			return temp;
		}
		else
		{
			printf("type conflict for %s\n",opt);
			exit(1);
		}
	}

        else if((strcmp(opt,"AND")==0) || (strcmp(opt,"OR")==0))
	{
		if(left->type == right->type  && (left->type==0))
		{
			struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));	
			temp->opt_type = opt;
			temp->val=0;
			temp->type=0;
			temp->variable=NULL;
			temp->left=left;
			temp->right=right;
			temp->middle=NULL;
			return temp;
		}
		else
		{
			printf("type conflict for %s\n",opt);
			exit(1);
		}
	}
	else if((strcmp(opt,"NOT")==0))
	{
		struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));	
		temp->opt_type = opt;
		temp->val=0;
		temp->type=0;
		temp->variable=NULL;
		temp->left=left;
		temp->right=NULL;
		temp->middle=NULL;
		return temp;
	}
}

struct tnode* CreateNumNode(int val)
{
	struct tnode* temp = (struct tnode*) malloc(sizeof(struct tnode));
	temp->opt_type = "NUM";
	temp->val=val;
	temp->type=1;
	temp->variable=NULL;
	temp->left=NULL;
	temp->right=NULL;
	temp->middle=NULL;
	return temp;
}

struct tnode* CreateIdNode(char *var)
{
	struct tnode* temp = (struct tnode *)malloc(sizeof(struct tnode));
	temp->opt_type="ID";
	temp->val=0;
	struct gsymbol* temp1 = glookup(var);	
	if(temp1 == NULL)
	{
		printf("Variable %s was undeclared\n",var);
		exit(1);
	}
	temp->type=temp1->type;
	temp->variable=temp1;
	temp->left=NULL;
	temp->right=NULL;
	temp->middle=NULL;
	return temp;
}

struct tnode* CreateArrayNode( char *var, struct tnode* left)
{
	struct tnode* temp = (struct tnode *)malloc(sizeof(struct tnode));
	temp->opt_type="ARRAY";
	temp->val=0;
	struct gsymbol* temp1 = glookup(var);	
	if(temp1 == NULL)
	{
		printf("Variable %s was undeclared\n",var);
		exit(1);
	}
	if(left->type != 1)
	{
		printf("index type can only be integer\n");
		exit(1);
	}
	temp->type=temp1->type;
	temp->variable=temp1;
	temp->left=left;
	temp->right=NULL;
	temp->middle=NULL;
	return temp;
}

/*
int evalTree(struct tnode* root)
{	
	if(strcmp(root->opt_type,"SLIST")==0)
	{
		evalTree(root->left);
		evalTree(root->right);
	}
	else if(strcmp(root->opt_type,"IF")==0)
	{
		if (evalTree(root->left))
			evalTree(root->middle);
	}
	else if(strcmp(root->opt_type,"IFELSE")==0)
	{
		if(evalTree(root->left))
			evalTree(root->middle);
		else
			evalTree(root->right);
	}
	else if(strcmp(root->opt_type,"WHILE")==0)
	{
		while(evalTree(root->left))
			evalTree(root->middle);
	}
	else if(strcmp(root->opt_type,"LOGICALCONST")==0)
	{	return root->val;}
	else if(strcmp(root->opt_type,"+")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 0))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left)+evalTree(root->right);
	}

        else if(strcmp(root->opt_type,"AND")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 1))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left) && evalTree(root->right);
	}
        
        else if(strcmp(root->opt_type,"OR")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 1))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left)||evalTree(root->right);
	}

	else if(strcmp(root->opt_type,"-")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 0))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left)-evalTree(root->right);
	}
	else if(strcmp(root->opt_type,"*")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 0))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left)*evalTree(root->right);
	}
	else if(strcmp(root->opt_type,"/")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 0))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left)/evalTree(root->right);
	}
	else if(strcmp(root->opt_type,">")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 0))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left) > evalTree(root->right);
	
	}else if(strcmp(root->opt_type,">=")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 0))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left)>=evalTree(root->right);
	}
	else if(strcmp(root->opt_type,"<")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 0))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left)<evalTree(root->right);
	}
	else if(strcmp(root->opt_type,"<=")==0)
	{
		if((root->left->type != root->right->type) || (root->left->type == 0))
		{
			printf("logical operation between non matching type\n");
			exit(1);
		}
		
		return evalTree(root->left)<=evalTree(root->right);
	}
	else if(strcmp(root->opt_type,"==")==0)
	{	
		if(root->left->type != root->right->type)
		{	
			printf("logical operation between non matching type\n");
			exit(1);
		}
		return evalTree(root->left)==evalTree(root->right);
	}
	else if(strcmp(root->opt_type,"NUM")==0)
	{	return root->val;}
	else if(strcmp(root->opt_type,"WRITE")==0)
	{	printf("%d\n",evalTree(root->left));}
	else if(strcmp(root->opt_type,"ID")==0)
	{	return root->variable->binding[0];}
	else if(strcmp(root->opt_type,"ARRAY")==0)
	{
		int arrindex = evalTree(root->left);
		if(arrindex<0 || arrindex>=root->variable->size)
		{
			printf("array index out of bound exception\n");
			exit(1);
		}
		return root->variable->binding[arrindex];
	}
	else if(strcmp(root->opt_type,"READ")==0)
	{	
		if(root->variable->type == 1)
			scanf("%d",&root->variable->binding[0]);
		else if(root->variable->type == 0)
		{
			char *str;
			scanf("%s",str);
			if(strcmp(str,"TRUE")==0)
			{	root->variable->binding[0]=TRUE;}
			else if(strcmp(str,"FALSE")==0)
			{	root->variable->binding[0]=FALSE;}
			else
			{
				printf("boolean type variable can have only TRUE/FALSE\n"); 
				exit(1);
			}
		}
	}
	else if(strcmp(root->opt_type,"READARR")==0)
	{
		int arrindex = evalTree(root->left);
		if(arrindex<0 || arrindex >= root->variable->size)
		{
			printf("array index out of bound exception\n");
			exit(1);
		}
		if(root->variable->type == 1)
		{	scanf("%d",&root->variable->binding[arrindex]);}
		else if(root->variable->type == 0)
		{
			char *str;
			scanf("%s",str);
			if(strcmp(str,"TRUE")==0)
			{	root->variable->binding[arrindex]=TRUE;}
			else if(strcmp(str,"FALSE")==0)
			{	root->variable->binding[arrindex]=FALSE;}
			else
			{
				printf("boolean type array can have only TRUE/FALSE\n");
				exit(1);
			}
		}
	}
	else if(strcmp(root->opt_type,"=")==0)
	{
		
		if(root->left->variable->type != root->right->type)
		{
			
			printf("assignment between non-matching types\n");
			exit(1);
		}
		if(strcmp(root->left->opt_type,"ID")==0)
		{	root->left->variable->binding[0] = evalTree(root->right);}
		else if(strcmp(root->left->opt_type,"ARRAY")==0)
		{
			int arrindex = evalTree(root->left->left);
			if(arrindex < 0 || arrindex >= root->left->variable->size)
			{
				printf("array index out of bound exception\n");
				exit(1);
			}
			root->left->variable->binding[arrindex]=evalTree(root->right);
		}
	}
}

*/


int codegen(struct tnode* temp)
{
	if(strcmp(temp->opt_type,"SLIST")==0)
	{
        codegen(temp->left);
	    codegen(temp->right);						
	}
	else if(strcmp(temp->opt_type,"IF")==0)
	{
		int r1 = codegen(temp->left);
		int l1 = getlabel();
		int l2= getlabel();
		fprintf(fp,"JZ R%d, L%d\n",r1,l1);
		freereg();	
		codegen(temp->middle);
		fprintf(fp,"L%d:\n",l1);
	}
	else if(strcmp(temp->opt_type,"IFELSE")==0)
	{
		int r1=codegen(temp->left);
		int l1=getlabel();
		int l2=getlabel();

		fprintf(fp,"JZ R%d, L%d\n",r1,l1);
		freereg();
		codegen(temp->middle);
		fprintf(fp,"JMP L%d\n",l2);
		fprintf(fp,"L%d:\n",l1);
		codegen(temp->right);
		fprintf(fp,"L%d:\n",l2);
	}
	else if(strcmp(temp->opt_type,"WHILE")==0)
	{
		
		int l1=getlabel();
		fprintf(fp,"L%d:\n",l1);
		int r1=codegen(temp->left);
		int l2=getlabel();
		fprintf(fp,"JZ R%d L%d\n",r1,l2);
		freereg();
		codegen(temp->middle);
		fprintf(fp,"JMP L%d\n",l1);
		fprintf(fp,"L%d:\n",l2);
	}
	else if(strcmp(temp->opt_type,"LOGICALCONST")==0)
	{	
		int r1 = getreg();
		fprintf(fp, "MOV R%d, %d\n", r1, temp->val);
	        return r1;
	}
        else if(strcmp(temp->opt_type,"%")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "MOD R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,"+")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "ADD R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,"%")==0)
	{
		int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
	 	fprintf(fp, "MOD R%d, R%d\n", r1, r2);
	 	freereg();
	 	return r1;  
	}
	else if(strcmp(temp->opt_type,"-")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "SUB R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,"*")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "MUL R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,"/")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "DIV R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,"<")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "LT R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,">")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "GT R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,"<=")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "LE R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,">=")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "GE R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,"==")==0)
	{
	 	int r1 = codegen(temp->left);
	 	int r2 = codegen(temp->right);
		fprintf(fp, "EQ R%d, R%d\n", r1, r2);
		freereg();
		return r1;   
	}
	else if(strcmp(temp->opt_type,"NUM")==0)
	{	
		int r1 = getreg();
		fprintf(fp, "MOV R%d, %d\n",r1, temp->val);
		return r1;	
	}
	else if(strcmp(temp->opt_type,"WRITE")==0)
	{	
		int r1 = codegen(temp->left);
	    fprintf(fp, "OUT R%d\n",r1);
	    freereg();
    }
    else if(strcmp(temp->opt_type,"ID")==0)
	{	
		int r1 = getreg();
    	fprintf(fp,"MOV R%d [%d]\n",r1,temp->variable->binding);
		return r1;
	}
	else if(strcmp(temp->opt_type,"ARRAY")==0)
	{
		int r1 = getreg();
		int r2=codegen(temp->left);
		fprintf(fp,"MOV R%d ,%d\n",r1,temp->variable->binding);
		fprintf(fp,"ADD R%d ,R%d\n",r1,r2);
		freereg();
		fprintf(fp,"MOV R%d ,[R%d]\n",r1,r1);
		return r1;
	}
	else if(strcmp(temp->opt_type,"READ")==0)
	{	
		int r1 = getreg();
		fprintf(fp, "IN R%d\n",r1);
		fprintf(fp,"MOV [%d] ,R%d\n",temp->variable->binding,r1);
		freereg();				
	}
	else if(strcmp(temp->opt_type,"READARR")==0)
	{
		int r1 = getreg();
		fprintf(fp, "IN R%d\n",r1);
		int r2 = getreg();
		int r3= codegen(temp->left);
		fprintf(fp, "MOV R%d, %d\n",r2, temp->variable->binding);
		fprintf(fp, "ADD R%d, R%d\n",r2,r3);
		freereg();
		fprintf(fp, "MOV [R%d], R%d\n",r2, r1);
		freereg();
		freereg();
	}
	else if(strcmp(temp->opt_type,"=")==0)
	{
		if(temp->left->left != NULL)	
		{
			int r1=getreg();
			int r2=codegen(temp->left->left);
									
			fprintf(fp,"MOV R%d ,%d\n",r1,temp->left->variable->binding);
			fprintf(fp,"ADD R%d ,R%d\n",r1,r2);
			freereg();
			int r3=codegen(temp->right);
			fprintf(fp,"MOV [R%d] ,R%d\n",r1,r3);  										
			freereg();
			freereg();
		}
		else	
		{
			int r1=codegen(temp->right);
			fprintf(fp,"MOV [%d] ,R%d\n",temp->left->variable->binding,r1);
			freereg();
		}			
    }
    else if(strcmp(temp->opt_type,"AND")==0)
	{
		int r1 = codegen(temp->left);
		int r2 = codegen(temp->right);
	 	fprintf(fp, "MUL R%d, R%d\n", r1, r2);
	 	freereg();
	 	return r1;
	}

    else if(strcmp(temp->opt_type,"OR")==0)
	{
		int r1 = codegen(temp->left);
		int r2 = codegen(temp->right);
	 	fprintf(fp, "ADD R%d, R%d\n", r1, r2);
                int l1=getlabel();
                fprintf(fp, "JZ R%d LABEL%d\n",r1,l1);
                fprintf(fp, "MOV R%d 1\n",r1);
                int l2=getlabel();
                fprintf(fp, "JMP LABEL%d\n",l2);
                fprintf(fp, "LABEL%d:\n",l1);
                fprintf(fp, "MOV R%d 0\n",r1);
                fprintf(fp, "LABEL%d:\n",l2);
	 	freereg();
	 	return r1;
	}
	else if(strcmp(temp->opt_type,"NOT")==0)
	{
		int r1 = codegen(temp->left);
		int l1 = getlabel();
		fprintf(fp,"JZ R%d L%d\n",r1,l1);
		fprintf(fp,"MOV R%d 0\n",r1);
		int l2 = getlabel();
		fprintf(fp,"JMP L%d\n",l2);
		fprintf(fp,"L%d:\n",l1);
		fprintf(fp,"MOV R%d 1\n",r1);
		fprintf(fp,"L%d:\n",l2);		
  		return r1;
	}
}
