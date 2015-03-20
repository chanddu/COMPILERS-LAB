typedef struct tNode{
	int value;
	char nodeType;
	char op;
	struct tNode *right;
	struct tNode *left;
}node;

#define YYSTYPE node *

node* makeINTERIORnode(node *root,node *l,node *r){
	root->left = l;
	root->right = r;
	return root;
}

node* makeLEAFnode(node *leaf){
	return leaf;
}

int evaluate(node *nd){
	if(nd->nodeType == 'L')
		return nd->value;
	else{
		if(nd->op == '+')
			return (evaluate(nd->left) + evaluate(nd->right));
		else if(nd->op == '-')
			return (evaluate(nd->left) - evaluate(nd->right));
		else if(nd->op == '*')
			return (evaluate(nd->left) * evaluate(nd->right));
		else if(nd->op == '/')
			return (evaluate(nd->left) / evaluate(nd->right));
	}
}

void mkNode(node *nd,int v,char t,char o,node *l,node *r){
	nd->value = v;
	nd->nodeType = t;
	nd->op = o;
	nd->left = l;
	nd->right = r;
}
