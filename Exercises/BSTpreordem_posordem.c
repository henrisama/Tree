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

void printpostorder(node* root){
	if(root != NULL){
		printpostorder(root->left);
		printpostorder(root->right);
		printf("%d\n", root->key);
	}
}

int main(){
	node* Tree = NULL;
	int value;
	while(scanf("%d", &value) > 0)
		nodeinsertion(&Tree, value);
	printpostorder(Tree);
	destroytree(Tree);
	return 0;
}