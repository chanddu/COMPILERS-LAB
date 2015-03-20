#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct gsymbol
{
    char *name;
    int type;								// type -> 0=bool, 1=int, 2=void
    int size;
    int binding;
    struct gsymbol *next;
};
int mem_loc = 0;

struct gsymbol* head = NULL;
struct gsymbol* tail = NULL;

struct gsymbol* glookup (char *str)
{
	struct gsymbol* temp;
	temp = head;
	while(temp != NULL)
	{
		if(strcmp(temp->name,str)==0)
			return temp;
		temp=temp->next;
	}
	return NULL;
}

void ginstall (char * name, int type, int size)
{
	struct gsymbol* temp;
	temp = head;
	if(glookup( name)== NULL)
	{
		
		struct gsymbol *temp1 = (struct gsymbol *)malloc(sizeof(struct gsymbol));
		temp1->name = name;
		temp1->type = type;
		temp1->size = size;
		temp1->binding = mem_loc;
		mem_loc = mem_loc + size;
		if(tail == NULL )
		{
			head = temp1;
			tail=temp1;
		}
		else
		{
			tail->next = temp1;
			tail = temp1;
		}
	}
	else
	{
		printf("name %s has already been used\n",name);
		exit(1);
	}
}

