typedef struct tNode{
	int value;
	char nodeType;
	char op;
	char variable;
	struct tNode *right;
	struct tNode *left;
}node;

#define YYSTYPE node *
int array[26];
int buffer;

node* makeINTERIORnode(node *root,node *l,node *r){
	root->left = l;
	root->right = r;
	return root;
}

node* makeLEAFnode(node *leaf){
	return leaf;
}

int evaluate(node *nd){
	if(nd->nodeType == 'O'){
		if(nd->op == '+')
			return (evaluate(nd->left) + evaluate(nd->right));
		else if(nd->op == '-')
			return (evaluate(nd->left) - evaluate(nd->right));
		else if(nd->op == '*')
			return (evaluate(nd->left) * evaluate(nd->right));
		else if(nd->op == '/')
			return (evaluate(nd->left) / evaluate(nd->right));
		else if(nd->op == '=')
			array[(int)nd->left->variable - 'a'] = evaluate(nd->right);
	}
	else if(nd->nodeType == 'I')
		return nd->value;
	else if(nd->nodeType == 'V')
		return array[(int)nd->variable - 'a'];
	else if(nd->nodeType == 'R'){
		printf("READ %c :",nd->left->variable);
		scanf("%d",&buffer);
		array[(int)nd->left->variable - 'a'] = buffer;
		return 1;
	}
	else if(nd->nodeType == 'W'){
		printf("%d\n",evaluate(nd->left));
	}
	else if(nd->nodeType == 'T'){
		evaluate(nd->left);
		evaluate(nd->right);
		return 1;
	}
		
}

void mkNode(node *nd,int v,char t,char o,char var,node *l,node *r){
	nd->value = v;
	nd->nodeType = t;
	nd->op = o;
	nd->variable = var;
	nd->left = l;
	nd->right = r;
}
