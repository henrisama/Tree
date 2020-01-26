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