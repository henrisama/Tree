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

void printpreorder(node* root){
	if(root != NULL){
		printf("%d ", root->key);
		printpreorder(root->left);
		printpreorder(root->right);
	}
}

int main(){
	node* Tree = nodebuild(NULL);
	int cases, value;
	scanf("%d", &cases);
	for(; cases>0; --cases){
		scanf("%d", &value);
		(value%2 == 0)? nodeinsertion(&(Tree->left), value) : nodeinsertion(&(Tree->right), value);
	}
	printpreorder(Tree->left);
	printf("\n");
	printpreorder(Tree->right);
	printf("\n");
	destroytree(Tree);
	return 0;
}