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