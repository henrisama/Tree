//Returns the height of the node. //Devolve a altura do nó.
int nodeheight(node* root){
    if(root == NULL) //If the node is null, returns -1. //Se o nó for nulo devolve -1.
        return -1;
    return root->height;
}