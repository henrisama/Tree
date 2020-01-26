//A function that returns the height of a specific node in a recursive way. //Uma função que retorna a altura de um nó específico de maneira recursiva.
int max(int a, int b){
    return (a > b)? a : b; //Returns greater value between a and b. //Retorna maior valor entre a e b.
}

int nodedepth(node* root){
    if(root == NULL)
        return -1; //If my root contains null, it returns -1. //Caso minha raiz contenha valor nulo, retorna -1.
    return 1 + max(nodedepth(root->left), nodedepth(root->right)); //It opens the same function for the left and right child and returns the greater depth between the two, and so on. //Abre a mesma função para o filho esquerdo e direito e retorna a maior profundidade entre os dois, e assim por diante.
}