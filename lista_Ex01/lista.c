#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lista.h"

typedef struct no no_t;

struct no {
	elem info;
	no_t *prox;
};

struct lista{
	no_t *ini, *fim;
	int tam;
};

lista_t *cria(){
	lista_t *l;
	l = (lista_t *) malloc(sizeof(lista_t));
	assert(l != NULL);

	l->ini = NULL;
	l->fim = NULL;
	l->tam = 0;

	return l;
}

void liberar(lista_t *l){
	if (l != NULL)
	{
		no_t *p = l->ini;
		while(p != NULL){
			l->ini = p->prox;
			free(p);
			p = l->ini;
		}
	}
	free(l);
}

void insere(lista_t *l, elem x){
	assert(l != NULL);

	no_t *p = (no_t *) malloc(sizeof(no_t));
	p->info = x;
	p->prox = NULL;

	if (l->ini == NULL)
	{
		l->ini = p;
		l->fim = p;
	}else{
		l->fim->prox = p;
	}

	l->fim = p;
	l->tam++;
}

int tamanho(lista_t *l){
	assert(l != NULL);
	return l->tam;
}

void imprimir(lista_t *l){
	assert( l != NULL);

	no_t *p = l->ini;
	while(p != NULL){
		printf("%d ", p->info);
		p = p->prox;
	}
	printf("\n");
}