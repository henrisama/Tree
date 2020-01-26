typedef struct setnode{
	int key, color;
	struct setnode *left, *right, **father;
}node;