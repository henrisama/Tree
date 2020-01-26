//Print orders. //Ordens de impressão.
void preorder(node* root){ //Print the father first, then the children. //Imprime primeiro o pai, depois os filhos.
    if(root != NULL){
        printf("%d\n", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(node* root){ //Print in order. //Imprime em ordem.
    if(root != NULL){
        inorder(root->left);
        printf("%d\n", root->key);
        inorder(root->right);
    }
}

void postorder(node* root){ //Print the children first, then the father. //Imprime primeiro os filhos, depois o pai.
    if(root != NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d\n", root->key);
    }
}