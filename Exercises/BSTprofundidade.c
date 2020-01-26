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

int max(int a, int b){
	return (a > b)? a : b;
}

int nodedepth(node* root){
	return (root == NULL)? -1 : 1 + max(nodedepth(root->left), nodedepth(root->right));
}

int main(){
	node* Tree;
	int cases1, cases2, value;
	scanf("%d", &cases1);
	for(; cases1>0; --cases1){
		Tree = NULL;
		scanf("%d", &cases2);
		for(; cases2>0; --cases2){
			scanf("%d", &value);
			nodeinsertion(&Tree, value);
		}
		printf("%d\n", nodedepth(Tree));
		destroytree(Tree);
	}
	return 0;
}