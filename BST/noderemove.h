//Function that removes a specific node. //Função que remove um nó específico.

node** successor(node** root){//Function that returns the successor of the node to be removed. (case 3). //Função que devolve o sucessor do nó a ser removido. (caso 3).
    node *aux, **paux;  //Two variables to help. //Duas variáveis para auxiliar.
    aux = (*root)->right;
    paux = &((*root)->right);
    while(aux->left != NULL){
        paux = &(aux->left);
        aux = aux->left;
    }
    return paux; //Return the successor. //Retorna o sucessor.
}

void noderemove(node** root){
    node *aux, **paux; //Two variables to help. //Duas variáveis para auxiliar.

    //Case 1: When the node to be removed has no children.
    //Caso 1: Quando o nó a ser removido não tem filhos.
    if((*root)->left == NULL && (*root)->right == NULL){
        aux = *root; //AUX receives the memory address. //AUX recebe o endereço de memória.
        *root = NULL; //The root becomes NULL. //A raiz se torna NULL.
        free(aux); //Free memory. //Libera memória.
    }
    //Case 2: When the node to be removed has a left child.
    //Caso 2: Quando o nó a ser removido tem um filho esquerdo.
    else if((*root)->left != NULL && (*root)->right == NULL){
        aux = *root; //AUX receives the memory address. //AUX recebe o endereço de memória.
        *root = (*root)->left;  //The root becomes the left child. //A raiz se torna o filho esquerdo.
        free(aux); //Free memory. //Libera memória.
    }
    //Case 3: When the node to be removed has a right child.
    //Caso 3: Quando o nó a ser removido tem um filho direito.
    else if((*root)->left == NULL && (*root)->right != NULL){
        aux = *root; //AUX receives the memory address. //AUX recebe o endereço de memória.
        *root = (*root)->right;  //The root becomes the right child. //A raiz se torna o filho direito.
        free(aux); //Free memory. //Libera memória.
    }
    //Case 4: When the node to be removed has left and right child.
    //Caso 4: Quando o nó a ser removido tem filho esquerdo e direito.
    else{
        paux = successor(root); //PAUX receives the successor of the node to be removed. //PAUX recebe o sucessor do nó a ser removido.
        (*root)->key = (*paux)->key; //The root receives the value contained in the PAUX. //A raiz recebe o valor contido no PAUX.
        noderemove(paux); //Calls the same function, but now for PAUX. //Chama a mesma função, mas agora para o PAUX.
    }
}