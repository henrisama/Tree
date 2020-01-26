//Insertion of the node in the tree. //Inserçao do nó na arvore.
void nodeinsertion(node** root, int value){
    if(*root == NULL)
        *root = nodebuild(value); //The root receives a function that returns the address of a new node with the value passed in the function. //A raiz recebe uma função que retorna o endereço de um novo nó com o valor passado na função.
    else{
        if((*root)->key > value) //Verifies that the value is less than the value of the last node passed in the function. //Verifica se o valor é menor que o valor do último nó passado na função.
            nodeinsertion(&((*root)->left), value); //If yes, it opens the same insert function for the left node. //Se sim, abre a mesma função de inserção para o nó esquerdo.
        else
            nodeinsertion(&((*root)->right), value); //Otherwise, it opens the same insert function for the right node. //Caso contrário, abre a mesma função de inserção para o nó direito.
    }
}