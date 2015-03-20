//
//  typecheck.h
//  
//
//  Created by Chandra Sekhar on 19/02/15.
//
//

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