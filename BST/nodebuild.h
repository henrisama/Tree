//Construction of a new node. //Construção de um novo nó.
node* nodebuild(int value){ //Function that returns a node-type variable. //Função que retorna uma variável do tipo nó.
    node* aux = (node*) malloc(sizeof(node)); //The *aux pointer receives the address of a dynamic allocation. //O ponteiro * aux recebe o endereço de uma alocação dinâmica.
    aux->key = value; //The node receives the value passed in the function. //O nó recebe o valor passado na função.
    aux->left = aux->right = NULL; //Placing null values ​​for the two children. //Colocando valores nulos para os dois filhos.
    return aux; //Returns the address of the new node. //Retorna o endereço do novo nó.
}