void destroytree(node* root){
	if(root != NULL){
		destroytree(root->left);
		destroytree(root->right);
		free(root);
	}
}