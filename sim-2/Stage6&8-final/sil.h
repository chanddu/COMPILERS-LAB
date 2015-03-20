#define INT_TYPE		1
#define BOOLEAN_TYPE	2
#define VOID_TYPE		3

#define DUMMY_TYPE 	0
#define DUMMY_NODETYPE	0

#define NUMBER_NODETYPE	0
#define PLUS_NODETYPE		1
#define MINUS_NODETYPE		2
#define MULT_NODETYPE		3
#define DIV_NODETYPE		4
#define ASSIGN_NODETYPE	5
#define MODULO_NODETYPE	6

#define READ_NODETYPE	1
#define WRITE_NODETYPE	2
#define ID_NODETYPE	4
#define IF_NODETYPE	6
#define WHILE_NODETYPE	9
#define RETURN_NODETYPE 11

#define LT_NODETYPE         1
#define LE_NODETYPE         2
#define GT_NODETYPE         3
#define GE_NODETYPE         4
#define EQ_NODETYPE         5
#define NE_NODETYPE         6
#define AND_NODETYPE        7
#define OR_NODETYPE         8
#define TRUE_NODETYPE       9
#define	FALSE_NODETYPE     10
#define NOT_NODETYPE        11

#define BOOL_VARTYPE   0
#define INT_VARTYPE	1



typedef struct Lsymbol  {
	char *NAME;
	int TYPE;
	int *BINDING;			// Address of the Identifier in Memory
	struct Lsymbol *NEXT;		// Pointer to next Symbol Table Entry 

}lsymbol;

typedef struct Tnode {
	int TYPE; 
	int NODETYPE;
	char* NAME; 
	int VALUE; 
	struct Tnode *ArgList;
	struct Tnode *Ptr1, *Ptr2, *Ptr3;
	struct Lsymbol *Lentry; 
	struct Gsymbol *Gentry; 
}tnode;

typedef struct Gsymbol {

	char *NAME;
	int TYPE;
	int SIZE;
	int *BINDING; 
	struct Gsymbol *NEXT;
}gsymbol;

int mem_loc;

tnode	*thead = NULL;

lsymbol *lhead = NULL;
lsymbol *llast = NULL;                      //head and last pointers

gsymbol *ghead = NULL;
gsymbol *glast = NULL;

void yyerror (char *msg)	{
    fprintf (stderr, "%s\n", msg);              // yyerror function
    exit(1);
}

lsymbol *Llookup(char *name)	{
    lsymbol *temp = lhead;
    while(temp)	{                                           //local symbol table lookup
        if(strcmp(name,temp->NAME)==0)
            return temp;
        temp = temp->NEXT;
    }
    return NULL;
}

void Linstall(char *name,int type)	{
    lsymbol *temp;
    temp = Llookup(name);
    if(temp)	{
        printf("You have already declared : %s ",name);
        yyerror("");
    }
    else	{                                                       //local symboltable install
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
    while(temp)	{                           //global lookup
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
        printf("You have already declared : %s ",name);
        yyerror("");
    }
    else	{
        temp = (gsymbol *)malloc(sizeof(gsymbol));              //global install
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

