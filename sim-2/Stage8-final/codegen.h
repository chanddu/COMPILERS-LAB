int regcount = -1,label = -1;
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

int codegen(tnode *temp){
	int dummy;
if(temp){
switch(temp->TYPE){
case DUMMY_TYPE :	
	codegen(temp->Ptr1);
	codegen(temp->Ptr2);
	break;
case VOID_TYPE : 
	switch(temp->NODETYPE){
		case READ_NODETYPE :
			{dummy = 0;
			
			if(temp->Ptr1->Gentry){
				if((temp->Ptr1->Gentry->SIZE)>1){
					int r1 = getreg();
					fprintf(fp, "\nIN R%d",r1);
					int r2 = getreg();
					int r3= codegen(temp->Ptr1->Ptr1);
					fprintf(fp, "\nMOV R%d, %d",r2, (temp->Ptr1->Gentry->BINDING));
					fprintf(fp, "\nADD R%d, R%d",r2,r3);
					freereg();
					fprintf(fp, "\nMOV [R%d], R%d",r2, r1);
					freereg();
					freereg();
				}
				else{
					int r1 = getreg();
					fprintf(fp, "\nIN R%d",r1);
					fprintf(fp, "\nMOV [%d], R%d", (temp->Ptr1->Gentry->BINDING),r1);
					freereg();
				}
			}
			else if(temp->Ptr1->Lentry){
				int r1 = getreg();
				fprintf(fp, "\nIN R%d",r1);
				fprintf(fp, "\nMOV [%d], R%d", (temp->Ptr1->Lentry->BINDING),r1);
				freereg();
			}
			}
			break;
		case WRITE_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			fprintf(fp, "\nOUT R%d",r1);
			freereg();}
			break;
		case ID_NODETYPE :
			{dummy = 0;
			int r1 = getreg();
			if(temp->Gentry){
				if((temp->Gentry->SIZE)>1){
					
					int r2 = codegen(temp->Ptr1);
					fprintf(fp, "\nMOV R%d, %d",r1, (temp->Gentry->BINDING));
					fprintf(fp, "\nADD R%d, R%d",r1,r2);
					freereg();
					fprintf(fp,"\nMOV R%d ,[R%d]",r1,r1);
				}
				else
					fprintf(fp, "\nMOV R%d, [%d]", r1, (temp->Gentry->BINDING));
			}
			else if(temp->Lentry)
				fprintf(fp, "\nMOV R%d, [%d]", r1, (temp->Lentry->BINDING));
			
			return r1;}
			break;
		case IF_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int l1 = getlabel();
			int l2 = getlabel();
			fprintf(fp, "\nJZ R%d, LABEL%d",r1,l1);
			freereg();
			codegen(temp->Ptr2);
			fprintf(fp, "\nJMP LABEL%d",l2);
			fprintf(fp, "\nLABEL%d :",l1);
			codegen(temp->Ptr3);
			fprintf(fp, "\nLABEL%d :",l2);}
			break;
		case WHILE_NODETYPE :
			{dummy = 0;
			int l1 = getlabel();
			fprintf(fp, "\nLABEL%d :",l1);
			int r1 = codegen(temp->Ptr1);
			int l2 = getlabel();
			fprintf(fp, "\nJZ R%d, LABEL%d",r1,l2);
			freereg();
			codegen(temp->Ptr2);
			fprintf(fp, "\nJMP LABEL%d",l1);
			fprintf(fp, "\nLABEL%d :", l2);}
			break;
		case RETURN_NODETYPE : 
			fprintf(fp, "\n");
			break;
	}
	break;
case INT_TYPE : 
	switch(temp->NODETYPE){
		case NUMBER_NODETYPE :
			{dummy = 0;
			int r1 = getreg();
			fprintf(fp, "\nMOV R%d, %d",r1, temp->VALUE);
			return r1;}
			break;
		case PLUS_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nADD R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case MINUS_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nSUB R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case MULT_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nMUL R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case DIV_NODETYPE :
			{dummy = 0;	
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nDIV R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case ASSIGN_NODETYPE :
			{dummy = 0;
			int r1 = getreg();
			if(temp->Ptr1->Lentry)
				fprintf(fp, "\nMOV R%d, %d", r1, (temp->Ptr1->Lentry->BINDING));
			else if(temp->Ptr1->Gentry){
				if((temp->Ptr1->Gentry->SIZE)>1){
					fprintf(fp, "\nMOV R%d, %d", r1, (temp->Ptr1->Gentry->BINDING));
					int r2 = codegen(temp->Ptr1->Ptr1);
					fprintf(fp, "\nADD R%d, R%d", r1, r2);
					freereg();
				}
				else
					fprintf(fp, "\nMOV R%d, %d", r1, (temp->Ptr1->Gentry->BINDING));
			}
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nMOV [R%d], R%d", r1, r2);
			freereg();
			freereg();}
			break;
		case MODULO_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nMOD R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		}
	break;
case BOOLEAN_TYPE : 
	switch(temp->NODETYPE){
		case NOT_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = getreg();
			int r3 = getreg();
			fprintf(fp, "\nMOV R%d, 1",r2);
			fprintf(fp, "\nMOV R%d, 2",r3);
			fprintf(fp, "\nADD R%d, R%d", r1, r2);
			fprintf(fp, "\nMOD R%d, R%d", r1, r3);
			freereg();
			freereg();
			return r1;}
			break;
		case LT_NODETYPE :
			{dummy = 0;	
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nLT R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case LE_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nLE R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case GT_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nGT R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case GE_NODETYPE :
			{dummy = 0;	
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nGE R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case EQ_NODETYPE :
			{dummy = 0;	
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nEQ R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case NE_NODETYPE :
			{dummy = 0;	
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nNE R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case AND_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nMUL R%d, R%d", r1, r2);
			freereg();
			return r1;}
			break;
		case OR_NODETYPE :
			{dummy = 0;
			int r1 = codegen(temp->Ptr1);
			int r2 = codegen(temp->Ptr2);
			fprintf(fp, "\nADD R%d, R%d", r1, r2);
			int l1 = getlabel();
			fprintf(fp, "\nJZ R%d LABEL%d",r1,l1);
                	fprintf(fp, "\nMOV R%d 1",r1);
                	int l2=getlabel();
                	fprintf(fp, "\nJMP LABEL%d",l2);
                	fprintf(fp, "\nLABEL%d:",l1);
                	fprintf(fp, "\nMOV R%d 0",r1);
                	fprintf(fp, "\nLABEL%d:",l2);
	 		freereg();
			return r1;}
			break;
		case TRUE_NODETYPE :
			{dummy = 0;
			int r1 = getreg();
			fprintf(fp, "\nMOV R%d, %d", r1, 1);
			return r1;}
			break;
		case FALSE_NODETYPE :
			{dummy = 0;
			int r1 = getreg(); 
			fprintf(fp, "\nMOV R%d, %d", r1, 0);
			return r1;}
			break;
	}
	break;
}
}
}
