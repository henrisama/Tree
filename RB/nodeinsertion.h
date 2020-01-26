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