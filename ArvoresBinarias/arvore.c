#include "arvore.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct no{
	elem info;
	no_t *esq;
	no_t *dir;
};

arvore_t *criaArvore(){
	arvore_t *a = (arvore_t *) malloc(sizeof(arvore_t));
	a->raiz = NULL;
	return a;
}

int esta_vazia(arvore_t *a){
	assert(a != NULL);
	if (a->raiz == NULL) return 1;
	else return 0;
}

void finalizar(no_t *raiz){
	if (raiz != NULL)
	{
		finalizar(raiz->esq);
		finalizar(raiz->dir);
		free(raiz);
	}
}

void imprimir (no_t *raiz){
	if (raiz != NULL)
	{
		printf("%d(", raiz->info);
		imprimir(raiz->esq);
		printf(", ");
		imprimir(raiz->dir);
	}
	else{
		printf("null");
	}
	printf(")");
}

int altura(no_t *raiz){
	if (raiz == NULL)
		return 0;
	int alt_esq = 1 + altura(raiz->esq);
	int alt_dir = 1 + altura(raiz->dir);

	if(alt_esq > alt_dir)
		return alt_esq;
	else
		return alt_dir;
}

no_t *busca(no_t *raiz, elem x){
	if(raiz == NULL)
		return NULL;

	if (raiz->info == x)
		return raiz;

	no_t *p = busca(raiz->esq, x);
	if(p == NULL)
		p = busca(raiz->dir, x);

	return p;
}
no_t *busca_pai(no_t *raiz, elem x){
	if (raiz == NULL)
		return NULL;

	if(raiz->esq != NULL && raiz->esq->info == x)
		return raiz;

	if (raiz->dir != NULL && raiz->dir->info == x)
		return raiz;

	no_t *p = busca_pai(raiz->esq, x);
	if(p == NULL)
		p = busca_pai(raiz->dir, x);
	return p;
}

//se o pai == -1, inserir na raiz
//caso contrário, insere do lado esquerdo de pai
int inserir_esq(arvore_t *a, elem x, elem pai){
	no_t *p = (no_t *) malloc(sizeof(no_t));
	p->esq = NULL;
	p->dir = NULL;
	p->info = x;
	if(pai == -1){
		if(a->raiz == NULL){
			a->raiz = p;
		}else{
			free(p);
			return 0;
		}
	}else{
		no_t *aux = busca(a->raiz, pai);
		if (aux != NULL && aux->esq == NULL){
			aux->esq = p;
		}
		else{
			free(p);
			return 0;
		}
	}
	return 1;
}
int inserir_dir(arvore_t *a, elem x, elem pai){
	no_t *p = (no_t *) malloc(sizeof(no_t));
	p->esq = NULL;
	p->dir = NULL;
	p->info = x;
	if(pai == -1){
		if(a->raiz == NULL){
			a->raiz = p;
		}else{
			free(p);
			return 0;
		}
	}else{
		no_t *aux = busca(a->raiz, pai);
		if (aux != NULL && aux->dir == NULL){
			aux->dir = p;
		}
		else{
			free(p);
			return 0;
		}
	}
	return 1;
}
int remover(arvore_t *a, elem x){
	return 0;
}