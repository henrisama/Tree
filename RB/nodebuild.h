node* nodebuild(int value, node** father){
	node* aux = (node*) malloc(sizeof(node));
	aux->key = value;
	aux->color = RED;
	aux->father = father;
	aux->left = aux->right = NULL;
	return aux;
}