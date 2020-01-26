//Definition of AVL tree node. //Definição do nó da arvore AVL.
typedef struct setnode{
    int key, height; //Value and height of the node respectively. //Valor e altura do nó respectivamente.
    struct setnode *left, *right; //Definition of children left and right. //Definição dos filhos esquerdo e direito.
}node; //Node-type structure. //Estrutura do tipo nó.