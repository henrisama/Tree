//A function that looks for a value contained in a node. //Uma função que procura por um valor contido em um nó.
node** nodesearch(node** root, int value){
    if(*root == NULL)
        return NULL; //If the node is null it means that the tree does not contain the requested value. //Se o nó for nulo, significa que a árvore não contém o valor solicitado.
    else if((*root)->key == value)
        return root; //If the node contains the same value as the VALUE variable, then it returns the address of that node. //Se o nó contiver o mesmo valor que a variável VALUE, ele retornará o endereço desse nó.
    else{
        if((*root)->key > value)
            return nodesearch(&((*root)->left), value); //Opens the same function for the left child. //Abre a mesma função para o filho esquerdo.
        else
            return nodesearch(&((*root)->right), value); //Opens the same function for the right child. //Abre a mesma função para o filho direito.
    }
}