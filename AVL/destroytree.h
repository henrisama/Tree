//Destruction of the tree in a recursive way. //Destruiçao da arvore de uma forma recursiva.
void destroytree(node* root){
    if(root != NULL){
        destroytree(root->left); //Opens the same function for the left node. //Abre a mesma função para o nó a esquerda.
        destroytree(root->right); //Opens the same function for the right node. //Abre a mesma função para o nó a direita.
        free(root); //Releases the allocated memory. //Libera a memória alocada.
    }
}