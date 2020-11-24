#include <stdio.h>
#include <stdlib.h>
#include "dicionario.h"

struct no
{
	int chave;
	no_t **proximo;
};

struct skiplist
{
	int nivelMax;
	float fracao;
	int nivelAtual;
	no_t *inicio;
};

skiplist_t *criar(int nivelMax, float fracao){
	skiplist_t *skiplist = (skiplist_t *) malloc(sizeof(skiplist_t));
	if (skiplist != NULL)
	{
		skiplist->nivelMax = nivelMax;
		skiplist->fracao = fracao;
		skiplist->nivelAtual = 0;

		skiplist->inicio = novoNo(-1, nivelMax);
	}
	return skiplist;
}

no_t *novoNo(int chave, int nivel){
	no_t * no = (no_t *) malloc (sizeof(no_t));
	if (no != NULL)
	{
		no->chave = chave;
		no->proximo = (no_t **) malloc((nivel+1) * sizeof(no_t *));
		for (int i = 0; i < (nivel+1); i++)
		{
			no->proximo[i] = NULL;
		}
	}
	return no;
}

void destruir(skiplist_t *skiplist){
	if (skiplist == NULL)
		return;

	no_t *no, *atual;
	atual = skiplist->inicio->proximo[0];
	while(atual != NULL){
		no = atual;
		atual = atual->proximo[0];
		free(no->proximo);
		free(no);
	}
	free(skiplist->inicio);
	free(skiplist);
}

int buscar(skiplist_t *skiplist, int chave){
	if (skiplist == NULL)
		return 0;

	no_t *atual = skiplist->inicio;

	for (int i = skiplist->nivelAtual; i >= 0; i--)
	{
		while(atual->proximo[i] != NULL && atual->proximo[i]->chave < chave){
			atual = atual->proximo[i];
		}
	}

	atual = atual->proximo[0];
	if (atual != NULL && atual->chave == chave)
		return 1;
	else
		return 0;
}

int inserir(skiplist_t *skiplist, int chave){
	if(skiplist == NULL)
		return 0;
	int indice;
	no_t *atual = skiplist->inicio;

	no_t **aux;
	aux = (no_t**) malloc((skiplist->nivelMax+1) * sizeof(no_t *));
	for (indice = 0; indice <= skiplist->nivelMax; indice++)
	{
		aux[indice] = NULL;
	}

	for (indice = skiplist->nivelAtual; indice >= 0; indice--)
	{
		while(atual->proximo[indice] != NULL && atual->proximo[indice]->chave < chave){
			atual = atual->proximo[indice];
		}
		aux[indice] = atual;
	}

	atual = atual->proximo[0];
	if (atual == NULL || atual->chave != chave)
	{
		int novo_nivel = sorteiaNivel(skiplist);

		no_t *novo = novoNo(chave, novo_nivel);
		if (novo == NULL)
		{
			free(aux);
			return 0;
		}

		if (novo_nivel > skiplist->nivelAtual)
		{
			for (int i = skiplist->nivelAtual+1; i <= novo_nivel; i++)
			{
				aux[i] = skiplist->inicio;
			}
			skiplist->nivelAtual = novo_nivel;
		}

		for (int i = 0; i <= novo_nivel; i++)
		{
			novo->proximo[i] = aux[i]->proximo[i];
			aux[i]->proximo[i] = novo;
		}
		free(aux);
		return 1;
	}
}

int sorteiaNivel(skiplist_t *skiplist){
	float aleatorio = (float) rand()/RAND_MAX;
	int nivel = 0;

	while(aleatorio < skiplist->fracao && nivel < skiplist->nivelMax){
		nivel++;
		aleatorio = (float) rand()/RAND_MAX;
	}
	return nivel;
}

int remover(skiplist_t *skiplist, int chave){
	if (skiplist == NULL)
		return 0;

	int indice;
	no_t *atual = skiplist->inicio;

	no_t **aux;
	aux = (no_t**) malloc((skiplist->nivelMax+1) * sizeof(no_t *));
	for (indice = 0; indice <= skiplist->nivelMax; indice++)
	{
		aux[indice] = NULL;
	}

	for (indice = skiplist->nivelAtual; indice >= 0; indice--)
	{
		while(atual->proximo[indice] != NULL && atual->proximo[indice]->chave < chave){
			atual = atual->proximo[indice];
		}
		aux[indice] = atual;
	}

	atual = atual->proximo[0];
	if (atual != NULL && atual->chave == chave)
	{
		for (int i = 0; i < skiplist->nivelAtual; i++)
		{
			if (aux[i]->proximo[i] != atual)
			{
				break;
			}
			aux[i]->proximo[i] = atual->proximo[i];
		}

		while(skiplist->nivelAtual > 0 && skiplist->inicio->proximo[skiplist->nivelAtual] == NULL){
			skiplist->nivelAtual--;
		}
		free(atual->proximo);
		free(atual);
		free(aux);
		return 1;
	}
}
