/* ============== arvoreb.h ================== */
#ifndef _ARVORE_B_
#define _ARVORE_B_

typedef int tchave;

typedef struct _node{
    int folha;
    int n;
    tchave * chaves;
    struct _node ** c;
}tnode;

typedef struct _arv{
    tnode * raiz;
    int t;
}tarv;

void btree_constroi(tarv * parv, int t);
int btree_insere(tarv *parv, tchave k);


#endif
/* ============ arvoreb.c ==================== */
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

#define check(A,M) if (!(A)) {\
	fprintf(stderr,"[ERROR] Line: %d %s\n", __LINE__, M);\
	goto error; }


int btree_split(tarv * parv,tnode * x, int i);
int btree_insere_naocheio(tarv *parv, tnode * x, tchave k);

tnode * aloca_node(tarv * parv){
	tnode *node = malloc(sizeof(tnode));
	check(node != NULL, "failed to malloc node");

	node->folha = 1;
	node->n = 0;
	int maxKeys = ((parv->t) * 2) - 1;
	
	node->chaves = calloc(maxKeys, sizeof(tchave));
	check(node->chaves != NULL, "failed to malloc chaves");
	
	node->c = calloc(maxKeys + 1, sizeof(tnode *));	
	check(node->c != NULL, "failed to malloc c");

	memset(node->c, 0, maxKeys + 1);
	
error:
	return node;
}

int rightShift(tnode *node, int i) {
	check(i >= 0, "Invalid position to shift");

	memmove(&node->chaves[i + 1], &node->chaves[i], sizeof(tchave) * (node->n - i));
	if (!node->folha) {
		if (i == 0) {
			memmove(&node->c[1], &node->c[0], sizeof(tnode *) * (node->n + 1));
		} else {
			memmove(&node->c[i + 2], &node->c[i + 1], sizeof(tnode *) * (node->n - i));
		}
	}
	node->n++;
	return 0;
error:
	return -1;
}

int leftShift(tnode *node, int i) {
	check(i >= 0, "Invalid position to shift");

	memmove(&node->chaves[i], &node->chaves[i + 1], sizeof(tchave) * (node->n - i - 1));
	if (!node->folha) {
		memmove(&node->c[i + 1], &node->c[i + 2], sizeof(tnode *) * (node->n - i - 1));
	}

	node->n--;
	return 0;
error:
	return -1;
}

void imprime_arvore(tnode * x,int prof,int i){
    int anda = 3;
    int j;
    int k;
    if (x->folha==TRUE){
        for (j=0;j<prof;j++)
            printf(" ");
        for (j=0;j<x->n;j++)
            printf("%d ",x->chaves[j]);
        printf("\n");

    }else{
        imprime_arvore(x->c[0],prof+anda,0);
        for (k=0;k<x->n;k++){ 
            for (j=0;j<prof;j++)
                printf(" ");
            printf("%d\n",x->chaves[k]);
            imprime_arvore(x->c[k+1],prof+anda,k+1);
        }
        if (prof == 0)
            printf("------\n");
    }
}

// Return the position of key if exists, else
// return the position where key should be inserted
int binSearch(tchave key, int size, tchave *arr) {
	int l = -1;
	int m = 0;
	int h = size;

	while (l + 1 < h) {
		m = (l + h) / 2;
		if (key == arr[m]) {
			return m;
		} else if (key > arr[m]) {
			l = m;
		} else {
			h = m;
		}
	}
	
	return h;
}


void btree_constroi(tarv * parv, int t){
    parv->t = t;
    parv->raiz = aloca_node(parv);
    parv->raiz->n = 0;
    parv->raiz->folha = TRUE;
}

tnode *findPlace(tarv *parv, tnode *node, tchave k) {
	if (node->folha) {
		return node;
	}

	int i = binSearch(k, node->n, node->chaves);
	if (node->c[i] == NULL || (node->c[i] && node->c[i]->folha)) {
		return node;
	}
	
	if (node->c[i]->n == (parv->t * 2) - 1) {
		btree_split(parv, node, i);
		return findPlace(parv, node, k);
	} else {
		node = node->c[i];
		return findPlace(parv, node, k);
	}

	return NULL;
}

int btree_insere(tarv *parv, tchave k){
	if (parv->raiz->n == (parv->t * 2) - 1) {
		tnode *newRoot = aloca_node(parv);
		newRoot->c[0] = parv->raiz;
		btree_split(parv, newRoot, 0);
		newRoot->folha = 0;
		newRoot->n = 1;
		parv->raiz = newRoot;
	}
	tnode *node = findPlace(parv, parv->raiz, k);
	if (node->folha) {
		tnode *fakeNode = aloca_node(parv);
		fakeNode->folha = 0;
		fakeNode->c[0] = parv->raiz;
		btree_insere_naocheio(parv, fakeNode, k);
		free(fakeNode->c);
		free(fakeNode->chaves);
		free(fakeNode);
	} else {
		btree_insere_naocheio(parv, node, k);
	}
	
	return 0;
}

int btree_insere_naocheio(tarv *parv, tnode * x, tchave k){
	int i = binSearch(k, x->n, x->chaves);
	
	// Ja existe essa chave
	if (i < x->n && x->chaves[i] == k) {
		return 1;
	}
	
	tnode *node = x->c[i];
	if (node == NULL) {
		node = aloca_node(parv);
		node->chaves[0] = k;
		x->folha = 0;
	} else {
		if (node->n == (parv->t * 2) - 1) {
			btree_split(parv, x, i);
			return btree_insere_naocheio(parv, x, k);
		}
		int j = binSearch(k, node->n, node->chaves);

		rightShift(node, j);
		node->chaves[j] = k;
	}
	
	return 0;
}

int btree_split(tarv * parv,tnode * x, int i){
	tnode *children = x->c[i];
	int mid = children->n / 2;

	tnode *right = aloca_node(parv);
	right->n = children->n - mid - 1;
	right->folha = children->folha;
	

	memmove(right->chaves, &(children->chaves[mid+1]), sizeof(tchave) * right->n);
	if (!children->folha) {
		memmove(right->c, &(children->c[mid+1]), sizeof(tnode *) * (right->n + 1));
	}
	children->n = mid;

	rightShift(x, i);

	x->chaves[i] = children->chaves[mid];
	x->c[i+1] = right;

	return 0;
}

void merge(tarv *parv, tnode *x, int pos) {
	tnode *left = x->c[pos];
	tnode *right = x->c[pos + 1];
	
	int lSize = left->n;
	int rSize = right->n;
	// Copy *right->chaves to the right side of *left->chaves
	// and put father into the middle 
	memmove(&left->chaves[lSize + 1], &right->chaves[0], sizeof(tchave) * rSize);
	left->chaves[lSize] = x->chaves[pos];
	// If *left is not leaf copy the children of *right	to right side of *left
	if (!left->folha) {
		memmove(&left->c[lSize + 1], &right->c[0], sizeof(tnode *) * (rSize + 1));
	}

	left->n = left->n + right->n + 1; // left is full

	leftShift(x, pos);

	if (x->n == 0) {
		memmove(&x->chaves[0], &left->chaves[0], sizeof(tchave) * left->n);
		memmove(&x->c[0], &left->c[0], sizeof(tnode *) * (left->n + 1));
		x->folha = left->folha;
		x->n = left->n;
		free(left);
	}

	free(right);
}

void pega_emprestado_irmao(tnode *x, int pos, int irmao) {
	if (pos < irmao) {
		tnode *left = x->c[pos];
		tnode *right = x->c[pos + 1];

		int lSize = left->n;
		int rSize = right->n;

		left->chaves[lSize] = x->chaves[pos];
		x->chaves[pos] = right->chaves[0];
		left->c[lSize + 1] = right->c[0];

		leftShift(right, 0);

		left->n++;
	} else {
		tnode *left = x->c[pos - 1];
		tnode *right = x->c[pos];

		int lSize = left->n;
		int rSize = right->n;

		rightShift(right, 0);

		right->chaves[0] = x->chaves[pos - 1];
		x->chaves[pos - 1] = left->chaves[lSize - 1];
		right->c[0] = left->c[lSize];

		left->n--;
	}
}

tchave sucessor(tnode *x, tchave k) {
	int i = binSearch(k, x->n, x->chaves);
	tnode *node = x->c[i + 1];
	while (!node->folha) {
		node = node->c[0];
	}
	return node->chaves[0];
}

tchave predecessor(tnode *x, tchave k) {
	int i = binSearch(k, x->n, x->chaves);
	tnode *node = x->c[i];
	while (!node->folha) {
		node = node->c[node->n];
	}
	return node->chaves[node->n - 1];
}


int pega_irmao_maior(tnode *x, int pos) {
	int prev = pos - 1;
	int next = pos + 1;

	if (prev < 0) return next;
	if (next > x->n) return prev;

	return x->c[prev]->n > x->c[next]->n ?
			prev : next;
}

int _btree_remove(tarv *parv, tnode *x, tchave k) {
	int t = parv->t;
	int i = binSearch(k, x->n, x->chaves);
	// Existe a chave nesse no
	if (i < x->n && x->chaves[i] == k) {
		if (x->folha) {
			// remove key
			leftShift(x, i);
			return 1;
		}

		tnode *left = x->c[i];
		tnode *right = x->c[i + 1];

		int lSize = left->n;
		int rSize = right->n;

		if (lSize >= t) {
			tchave newKey = predecessor(x, k);
			x->chaves[i] = newKey;
			return _btree_remove(parv, left, newKey);
		} else if (rSize >= t) {
			tchave newKey = sucessor(x, k);
			x->chaves[i] = newKey;
			return _btree_remove(parv, right, newKey);
		} else {
			merge(parv, x, i);
			return _btree_remove(parv, x, k);
		}
	} else {
		if (x->folha) {
			return 0;
		}
		
		if (x->c[i]->n == t - 1) {
			int irmao_maior = pega_irmao_maior(x, i);
			if (x->c[irmao_maior]->n >= t) {
				pega_emprestado_irmao(x, i, irmao_maior);
				return _btree_remove(parv, x->c[i], k);
			} else {
				merge(parv, x, i < irmao_maior ? i : irmao_maior);
				return _btree_remove(parv, x, k);
			}
		} else {
			return _btree_remove(parv, x->c[i], k);
		}
	}

	return 0;
}

int btree_remove(tarv *parv, tchave k) {
	printf("Removendo %d\n", k);
	return _btree_remove(parv, parv->raiz, k);
}

void test_btree_split(){
    tarv arv;
    int t = 3;
    btree_constroi(&arv,t);

    tnode * x;
    tnode * y;
    tnode * z;

    x = arv.raiz;
    y = aloca_node(&arv);

    y->folha = TRUE;
    y->n = 5;
    y->chaves[0] = 10;
    y->chaves[1] = 20;
    y->chaves[2] = 30;
    y->chaves[3] = 40;
    y->chaves[4] = 50;
    
    x->c[0] = y;
    x->n = 0;
    x->folha = FALSE;
    arv.raiz = x;

    btree_split(&arv,x,0);

    x = arv.raiz;
    y = x->c[0];
    z = x->c[1];
    assert(x->chaves[0] == 30);
    assert(x->folha == FALSE);
    assert(x->n == 1);

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha  == TRUE);

    assert(z->chaves[0] == 40); assert(z->chaves[1] == 50);
    assert(z->n == 2);
    assert(z->folha  == TRUE);
}

void test_btree_insere_naocheio(){
    tarv arv;
    int t = 3;
    btree_constroi(&arv,t);

    tnode * x;
    tnode * y;
    tnode * z;

    x = arv.raiz;
    y = aloca_node(&arv);

    y->folha = TRUE;
    y->n = 5;
    y->chaves[0] = 10;
    y->chaves[1] = 20;
    y->chaves[2] = 30;
    y->chaves[3] = 40;
    y->chaves[4] = 50;
    
    x->c[0] = y;
    x->n = 0;
    x->folha = FALSE;
    arv.raiz = x;

    btree_split(&arv,x,0);
	
    btree_insere_naocheio(&arv,x,23);

    y = x->c[0];

    
    assert(y->chaves[2] == 23);
    assert(y->n == 3);

    btree_insere_naocheio(&arv,x,24);

    y = x->c[0];
    assert(y->chaves[3] == 24);
    assert(y->n == 4);

    btree_insere_naocheio(&arv,x,25);
    btree_insere_naocheio(&arv,x,26);

    x = arv.raiz; 

    assert(x->chaves[0] == 23);
    assert(x->chaves[1] == 30);
    assert(x->n == 2);
    assert(x->folha == FALSE);


    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 24);
    assert(y->chaves[1] == 25);
    assert(y->chaves[2] == 26);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    y = x->c[2];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha == TRUE);
}


void test_btree_insere(){
    tarv arv;
    tnode *x, *y;
    int t; 
    int i;
    t = 3;

    btree_constroi(&arv,t);

    for (i=10;i<=60;i+=10)
        btree_insere(&arv,i);
	

    x=arv.raiz;
    assert(x->chaves[0] == 30);
    assert(x->n == 1);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha==TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->chaves[2] == 60);
    assert(y->n == 3);
    assert(y->folha==TRUE);


    
    for (i=70;i<100;i+=10)
        btree_insere(&arv,i);

    x=arv.raiz;
    assert(x->chaves[0] == 30);
    assert(x->chaves[1] == 60);
    assert(x->n == 2);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha==TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha==TRUE);

    y = x->c[2];

    assert(y->chaves[0] == 70);
    assert(y->chaves[1] == 80);
    assert(y->chaves[2] == 90);
    assert(y->n == 3);
    assert(y->folha==TRUE);

    btree_insere(&arv,21);
    btree_insere(&arv,22);
    btree_insere(&arv,23);
    btree_insere(&arv,24);

    x=arv.raiz;
    assert(x->chaves[0] == 21);
    assert(x->chaves[1] == 30);
    assert(x->chaves[2] == 60);
    assert(x->n == 3);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha==TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 22);
    assert(y->chaves[1] == 23);
    assert(y->chaves[2] == 24);
    assert(y->n == 3);
    assert(y->folha==TRUE);

    btree_insere(&arv,51);
    btree_insere(&arv,52);
    btree_insere(&arv,53);
    btree_insere(&arv,54);

    btree_insere(&arv,91);
    btree_insere(&arv,92);
    btree_insere(&arv,93);
    btree_insere(&arv,94);

    x=arv.raiz;
    assert(x->chaves[0] == 51);
    assert(x->n == 1);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 21);
    assert(y->chaves[1] == 30);
    assert(y->n == 2);
    assert(y->folha==FALSE);

    y = x->c[1];

    assert(y->chaves[0] == 60);
    assert(y->chaves[1] == 90);
    assert(y->n == 2);
    assert(y->folha==FALSE);


}

void test_btree_merge(){
    tarv arv;
    tnode *x, *y;
    int t; 
    int i;
    t = 3;

    btree_constroi(&arv,t);

    for (i=10;i<=60;i+=10)
        btree_insere(&arv,i);


    for (i=70;i<100;i+=10)
        btree_insere(&arv,i);
    btree_insere(&arv,21);
    btree_insere(&arv,22);
    btree_insere(&arv,23);
    btree_insere(&arv,24);

    btree_insere(&arv,51);
    btree_insere(&arv,52);
    btree_insere(&arv,53);
    btree_insere(&arv,54);

    btree_insere(&arv,91);
    btree_insere(&arv,92);
    btree_insere(&arv,93);
    btree_insere(&arv,94);

    x = arv.raiz;
    merge(&arv,x,0);
    
    assert(x->chaves[0] == 21);
    assert(x->chaves[1] == 30);
    assert(x->chaves[2] == 51);
    assert(x->chaves[3] == 60);
    assert(x->chaves[4] == 90);
    assert(x->n == 5);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 22);
    assert(y->chaves[1] == 23);
    assert(y->chaves[2] == 24);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    y = x->c[2];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[3];

    assert(y->chaves[0] == 52);
    assert(y->chaves[1] == 53);
    assert(y->chaves[2] == 54);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    y = x->c[4];

    assert(y->chaves[0] == 70);
    assert(y->chaves[1] == 80);
    assert(y->n == 2);
    assert(y->folha == TRUE);


    y = x->c[5];

    assert(y->chaves[0] == 91);
    assert(y->chaves[1] == 92);
    assert(y->chaves[2] == 93);
    assert(y->chaves[3] == 94);
    assert(y->n == 4);
    assert(y->folha == TRUE);
}

void test_btree_merge2(){
    tarv arv;
    tnode *x, *y;
    int t; 
    int i;
    t = 3;

    btree_constroi(&arv,t);

    for (i=10;i<=60;i+=10)
        btree_insere(&arv,i);


    for (i=70;i<100;i+=10)
        btree_insere(&arv,i);
    btree_insere(&arv,21);
    btree_insere(&arv,22);
    btree_insere(&arv,23);
    btree_insere(&arv,24);

    btree_insere(&arv,51);
    btree_insere(&arv,52);
    btree_insere(&arv,53);
    btree_insere(&arv,54);

    btree_insere(&arv,91);
    btree_insere(&arv,92);
    btree_insere(&arv,93);
    btree_insere(&arv,94);

    x = arv.raiz->c[0];
    x->c[1]->n=2;
    merge(&arv,x,0);
    
    assert(x->chaves[0] == 30);
    assert(x->n == 1);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->chaves[2] == 21);
    assert(y->chaves[3] == 22);
    assert(y->chaves[4] == 23);
    assert(y->n == 5);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha == TRUE);

}
void test_btree_merge3(){
    tarv arv;
    tnode *x, *y; 
    int t; 
    int i;
    t = 3;

    btree_constroi(&arv,t);

    for (i=10;i<=60;i+=10)
        btree_insere(&arv,i);


    for (i=70;i<100;i+=10)
        btree_insere(&arv,i);
    btree_insere(&arv,21);
    btree_insere(&arv,22);
    btree_insere(&arv,23);
    btree_insere(&arv,24);

    btree_insere(&arv,51);
    btree_insere(&arv,52);
    btree_insere(&arv,53);
    btree_insere(&arv,54);

    btree_insere(&arv,91);
    btree_insere(&arv,92);
    btree_insere(&arv,93);
    btree_insere(&arv,94);

    x = arv.raiz->c[0];
    x->c[1]->n=2;
    merge(&arv,x,1);
    
    assert(x->chaves[0] == 21);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];
    assert(y->chaves[0] == 22);
    assert(y->chaves[1] == 23);
    assert(y->chaves[2] == 30);
    assert(y->chaves[3] == 40);
    assert(y->chaves[4] == 50);
    assert(y->n == 5);
    assert(y->folha == TRUE);

}

void test_btree_empresta_irmao(){
    tarv arv;
    tnode *x, *y, *z;
    int t; 
    int i;
    t = 3;

    btree_constroi(&arv,t);

    for (i=10;i<=60;i+=10)
        btree_insere(&arv,i);


    for (i=70;i<100;i+=10)
        btree_insere(&arv,i);
    btree_insere(&arv,21);
    btree_insere(&arv,22);
    btree_insere(&arv,23);
    btree_insere(&arv,24);

    btree_insere(&arv,51);
    btree_insere(&arv,52);
    btree_insere(&arv,53);
    btree_insere(&arv,54);

    btree_insere(&arv,91);
    btree_insere(&arv,92);
    btree_insere(&arv,93);
    btree_insere(&arv,94);

    x = arv.raiz->c[0];
    pega_emprestado_irmao(x,0,1);

    y = x->c[0];
    z = x->c[1];

    assert(x->chaves[0]==22);
    assert(x->chaves[1]==30);
    assert(x->n == 2);
    assert(x->folha == FALSE);

    assert(y->chaves[0]==10);
    assert(y->chaves[1]==20);
    assert(y->chaves[2]==21);
    assert(y->n == 3);
    assert(y->folha == TRUE);


    assert(z->chaves[0]==23);
    assert(z->chaves[1]==24);
    assert(z->n == 2);
    assert(z->folha == TRUE);
}


void test_btree_empresta_irmao2(){
    tarv arv;
    tnode *x, *y, *z;
    int t; 
    int i;
    t = 3;

    btree_constroi(&arv,t);

    for (i=10;i<=60;i+=10)
        btree_insere(&arv,i);


    for (i=70;i<100;i+=10)
        btree_insere(&arv,i);
    btree_insere(&arv,21);
    btree_insere(&arv,22);
    btree_insere(&arv,23);
    btree_insere(&arv,24);

    btree_insere(&arv,51);
    btree_insere(&arv,52);
    btree_insere(&arv,53);
    btree_insere(&arv,54);

    btree_insere(&arv,91);
    btree_insere(&arv,92);
    btree_insere(&arv,93);
    btree_insere(&arv,94);

    x = arv.raiz->c[0];
    pega_emprestado_irmao(x,0,1);

    y = x->c[0];
    z = x->c[1];

    assert(x->chaves[0]==22);
    assert(x->chaves[1]==30);
    assert(x->n == 2);
    assert(x->folha == FALSE);

    assert(y->chaves[0]==10);
    assert(y->chaves[1]==20);
    assert(y->chaves[2]==21);
    assert(y->n == 3);
    assert(y->folha == TRUE);


    assert(z->chaves[0]==23);
    assert(z->chaves[1]==24);
    assert(z->n == 2);
    assert(z->folha == TRUE);
}

void test_btree_remove(){
    tarv arv;
    int t;
    tnode * x;
    t=3;




    btree_constroi(&arv,t);
    btree_insere(&arv,10);
    btree_insere(&arv,20);
    btree_insere(&arv,30);
    btree_insere(&arv,40);
    btree_insere(&arv,50);
    btree_insere(&arv,60);

    x = arv.raiz;


    assert(x->chaves[0] == 30);

    btree_remove(&arv,10);
    btree_remove(&arv,20);
    btree_remove(&arv,30);
    btree_remove(&arv,40);
    btree_remove(&arv,50);

    assert(x->chaves[0] == 60);
    assert(x->n == 1);
    assert(x->folha == TRUE);

    btree_insere(&arv,10);
    btree_insere(&arv,20);
    btree_insere(&arv,30);
    btree_insere(&arv,40);
    btree_insere(&arv,50);

    x = arv.raiz;
    
    imprime_arvore(arv.raiz,0,0);
    assert(x->chaves[0] == 30);
    btree_remove(&arv,10);
    imprime_arvore(arv.raiz,0,0);
    assert(x->chaves[0] == 40);
    btree_remove(&arv,40);
    imprime_arvore(arv.raiz,0,0);
    assert(x->chaves[0] == 20);
}

void test_btree_remove2(){
    tarv arv;
    int t; 
    int i;
    t = 3;

    btree_constroi(&arv,t);

    for (i=10;i<=60;i+=10)
        btree_insere(&arv,i);

   
    for (i=70;i<100;i+=10)
        btree_insere(&arv,i);

    btree_insere(&arv,21);
    btree_insere(&arv,22);
    btree_insere(&arv,23);
    btree_insere(&arv,24);


    btree_insere(&arv,51);
    btree_insere(&arv,52);
    btree_insere(&arv,53);
    btree_insere(&arv,54);

    btree_insere(&arv,91);
    btree_insere(&arv,92);
    btree_insere(&arv,93);
    btree_insere(&arv,94);


    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,24);

    imprime_arvore(arv.raiz,0,0);
    
    btree_remove(&arv,50);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,51);
    imprime_arvore(arv.raiz,0,0);
    
    btree_remove(&arv,54);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,60);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,30);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,21);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,22);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,23);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,80);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,90);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,91);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,92);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,52);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,40);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,20);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,53);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,10);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,70);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,93);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,94);
    imprime_arvore(arv.raiz,0,0);

    btree_remove(&arv,94);
    imprime_arvore(arv.raiz,0,0);


}

int main(void){
    test_btree_split();

    test_btree_insere_naocheio();
    test_btree_insere();

    test_btree_merge();
    test_btree_merge2();
    test_btree_merge3();

    test_btree_empresta_irmao();
    test_btree_empresta_irmao2();

    test_btree_remove();
    test_btree_remove2();
    return 0;
}