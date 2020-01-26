#define RED 1
#define BLACK 0

typedef struct setnode{
	int key, color;
	struct setnode *left, *right, **father;
}node;

node* nodebuild(int value, node** father){
	node* aux = (node*) malloc(sizeof(node));
	aux->key = value;
	aux->color = RED;
	aux->father = father;
	aux->left = aux->right = NULL;
	return aux;
}

void destroytree(node* root){
	if(root != NULL){
		destroytree(root->left);
		destroytree(root->right);
		free(root);
	}
}

int color(node* root){
	return (root == NULL)? 0 : root->color;
}

void leftrotation(node** root){
	printf("RE %d\n", (*root)->key);
	node* aux = (*root)->right;
	(*root)->right = aux->left;
	aux->left = (*root);
	(*root) = aux;

	(*root)->color = BLACK;
	(*root)->father = (*root)->left->father;
	(*root)->left->color = RED;
	(*root)->left->father = root;

	if((*root)->right != NULL)
		(*root)->right->father = root;
	if((*root)->left->left != NULL)
		(*root)->left->left->father = &((*root)->left);
	if((*root)->left->right != NULL)
		(*root)->left->right->father = &((*root)->left);
}

void rightrotation(node** root){
	printf("RD %d\n", (*root)->key);
	node* aux = (*root)->left;
	(*root)->left = aux->right;
	aux->right = (*root);
	(*root) = aux;

	(*root)->color = BLACK;
	(*root)->father = (*root)->right->father;
	(*root)->right->color = RED;
	(*root)->right->father = root;

	if((*root)->left != NULL)
		(*root)->left->father = root;
	if((*root)->right->left != NULL)
		(*root)->right->left->father = &((*root)->right);
	if((*root)->right->right != NULL)
		(*root)->right->right->father = &((*root)->right);
}

void fixup(node** root, node** stub){
	node **father, **grandfather, **son, *uncle;
	int fbson, fbfather;
	father = (*root)->father;
	son = root;

	while(color((*father)) == RED){
		grandfather = (*father)->father;
		uncle = ((*grandfather)->left == *father)? (*grandfather)->right : (*grandfather)->left;
		fbson = ((*father)->left == *son)? 1 : -1;
		fbfather = ((*grandfather)->left == *father)? 1 : -1;

		if(color(uncle) == RED){
			(*father)->color = uncle->color = BLACK;
			(*grandfather)->color = RED;

			if((*father)->father != father){
				son = grandfather;
				father = (*grandfather)->father;
			}
		}
		else{
			if(fbson * fbfather < 0)
				(fbson == 1)? rightrotation(father) : leftrotation(father);
			(fbfather == 1)? rightrotation(grandfather) : leftrotation(grandfather);
		}
		(*stub)->color = BLACK;
	}
}

void nodeinsertion(node** root, int value){
	if(*root == NULL)
		*root = nodebuild(value, root);
	else{
		node **son, **father;
		son = root;
		while(*son != NULL){
			father = son;
			son = ((*father)->key > value)? &((*son)->left) : &((*son)->right);
		}
		*son = nodebuild(value, father);
		fixup(son, root);
	}
	(*root)->color = BLACK;
}

node** searchpointertopointer(node* root, node** stub){
	if((*stub) == root)
		return stub;
	else{
		if((*stub)->key > root->key)
			return searchpointertopointer(root, &((*stub)->left));
		else
			return searchpointertopointer(root, &((*stub)->right));
	}
}

void fixupremove(node** root, node** stub){
	node *son, *father, *brother, *nephew1, *nephew2;
	int fbbrother, colorfather;
	son = (*root);

	while(color(son) == BLACK && son != *stub){
		father = *(son->father);
		brother = (father->left == son)? father->right : father->left;
		fbbrother = (father->left == brother)? 1 : -1;
		nephew1 = (fbbrother == 1)? brother->right : brother->left;
		nephew2 = (brother->left == nephew1)? brother->right : brother->left;

		if(color(brother) == RED){ //caso 1
			printf("C1\n");
			(fbbrother == 1)? rightrotation(son->father) : leftrotation(son->father);
		}
		else if(color(nephew1) == BLACK && color(nephew2) == BLACK){ //caso 2
			printf("C2\n");
			brother->color = RED;
			son = father;
		}
		else{
			if(color(nephew1) == RED && color(nephew2) == BLACK){ //caso 3
				printf("C3\n");
				(fbbrother == 1)? leftrotation(searchpointertopointer(brother, stub)) : rightrotation(searchpointertopointer(brother, stub));
				brother = (father->left == *root)? father->right : father->left;
				fbbrother = (father->left == brother)? 1 : -1;
				nephew1 = (fbbrother == 1)? brother->right : brother->left;
				nephew2 = (brother->left == nephew1)? brother->right : brother->left;
			}
			printf("C4\n"); //caso 4
			colorfather = father->color;
			(fbbrother == 1)? rightrotation(searchpointertopointer(father, stub)) : leftrotation(searchpointertopointer(father, stub));
			brother->color = colorfather;
			father->color = BLACK;
			nephew2->color = BLACK;
			break;
		}
	}
	son->color = BLACK;
}


node** successor(node** root){
	node** paux = &((*root)->right);
	while((*paux)->left != NULL)
		paux = &((*paux)->left);
	return paux;
}

void noderemove(node** root, node** stub){
	node *aux, **paux;
	aux = (*root);
	if((*root)->left != NULL && (*root)->right == NULL){
		(*root) = (*root)->left;
		(*root)->father = aux->father;
		(*root)->color = BLACK;
		free(aux);
	}
	else if((*root)->left == NULL && (*root)->right != NULL){
		(*root) = (*root)->right;
		(*root)->father = aux->father;
		(*root)->color = BLACK;
		free(aux);
	}
	else if((*root)->left != NULL && (*root)->right != NULL){
		paux = successor(root);
		(*root)->key = (*paux)->key;
		noderemove(paux, stub);
	}
	else{
		if(root == stub){
			(*root) = NULL;
			free(aux);
		}
		else{
			fixupremove(root, stub);
			paux = ((*stub)->key > aux->key)? searchpointertopointer(aux, &((*stub)->left)) : searchpointertopointer(aux, &((*stub)->right));
			aux = (*paux);
			(*paux) = NULL;
			free(aux);
		}
	}
}