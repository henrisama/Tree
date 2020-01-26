#include <stdio.h>
#include <stdlib.h>

typedef struct setnode{
	int key;
	struct setnode *left, *right;
}node;

node* nodebuild(int value){
	node* aux = (node*) malloc(sizeof(node));
	aux->key = value;
	aux->left = aux->right = NULL;
	return aux;
}

void destroytree(node* root){
	if(root != NULL){
		destroytree(root->left);
		destroytree(root->right);
		free(root);
	}
}

void nodeinsertion(node** root, int value){
	if(*root == NULL)
		*root = nodebuild(value);
	else
		((*root)->key > value)? nodeinsertion(&((*root)->left), value) : nodeinsertion(&((*root)->right), value);
}

node** successor(node** root){
	node** paux = &((*root)->right);
	while((*paux)->left != NULL)
		paux = &((*paux)->left);
	return paux;
}

void noderemove(node** root){
	node *aux, **paux;
	if((*root)->left == NULL && (*root)->right == NULL){
		aux = (*root);
		(*root) = NULL;
		free(aux);
	}
	else if((*root)->left != NULL && (*root)->right == NULL){
		aux = (*root);
		(*root) = (*root)->left;
		free(aux);
	}
	else if((*root)->left == NULL && (*root)->right != NULL){
		aux = (*root);
		(*root) = (*root)->right;
		free(aux);
	}
	else{
		paux = successor(root);
		(*root)->key = (*paux)->key;
		noderemove(paux);
	}
}

void removeodd(node** root){
	if((*root) != NULL){
		removeodd(&((*root)->left));
		removeodd(&((*root)->right));
		if((*root)->key%2 == 1)
			noderemove(root);
	}
}

void printpreorder(node* root){
	if(root != NULL){
		printf("%d ", root->key);
		printpreorder(root->left);
		printpreorder(root->right);
	}
}

int main(){
	node* Tree = NULL;
	int cases, value;
	scanf("%d", &cases);
	for(; cases>0; --cases){
		scanf("%d", &value);
		nodeinsertion(&Tree, value);
	}
	removeodd(&Tree);
	printpreorder(Tree);
	printf("\n");
	destroytree(Tree);
	return 0;
}