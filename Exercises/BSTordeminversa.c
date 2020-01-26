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

void printpreorderinverse(node* root){
	if(root != NULL){
		printpreorderinverse(root->right);
		printf("%d ", root->key);
		printpreorderinverse(root->left);
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
	printpreorderinverse(Tree);
	printf("\n");
	destroytree(Tree);
	return 0;
}