#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

struct elem{
	char *nome;
	int idade;
	int criterio;
};

struct fila{
	int inicio, fim, total;
	elem_t itens[TamFila];
};

fila_t *criar(){
	fila_t *f;
	f = (fila_t *) malloc(sizeof(fila_t));
	assert(f != NULL);
	f->total = 0;
	f->inicio = 0;
	f->fim = 0;
	return f;
}

int isEmpity(fila_t *f){
	assert(f != NULL);

	if(f->total == 0)
		return 1;
	else
		return 0;
}

int isFull(fila_t *f){
	assert(f != NULL);

	if(f->total == TamFila)
		return 1;
	else
		return 0;
}

int inserir(fila_t *f, char *nome, int idade, int criterio){
	if(isFull(f) == 1)
		return 0;

	f->itens[f->fim].nome = (char *) malloc(strlen(nome) * sizeof(char));
	strcpy(f->itens[f->fim].nome, nome);
	f->itens[f->fim].idade = idade;
	f->itens[f->fim].criterio = criterio;

	f->fim = (f->fim + 1) % TamFila;
	f->total++;
	return 1;
}

int remover(fila_t *f){
	if (isEmpity(f) == 1)
		return 0;
	free(f->itens[f->inicio].nome);
	f->itens[f->inicio].nome = NULL;
	f->itens[f->inicio].idade = 0;
	f->itens[f->inicio].criterio = 0;

	f->inicio = (f->inicio + 1) % TamFila;
	f->total--;
	return 1;
}

void destruir(fila_t *f){
	if (f != NULL){
		for (int i = 0; i < f->total; i++)
		{
			if (f->itens[i].nome != NULL)
			{
				free(f->itens[i].nome);
			}
		}
	}
		free(f);
}

/*O comportamento dessa função é similar ao Bubble sort, os critérios de ordenação são:
	1- ter idade >= 60 e variavel criterio == 1 (problema de saúde)
	2- ter variavel criterio == 1 (problema de saúde) mesmo não sendo idoso
	3- ter idade >= 60 mesmo com variavel critério == 0 (sem problema de saúde)
	4- Qualquer indivíduo

	Os elementos serão permutados para que a ordem siga sempre essa prioridade
*/

fila_t *ordenar(fila_t *f){
	assert(f != NULL);
	elem_t elemento_auxiliar;
	elemento_auxiliar.nome = NULL;

	for (int j = 0; j < f->total; j++)
	{
		for (int i = f->fim - 1; i > f->inicio; i--)
		{
			if ((f->itens[i].idade >= 60 && f->itens[i].criterio == 1) &&
					(f->itens[i-1].idade < 60 || f->itens[i-1].criterio != 1))
			{
				elemento_auxiliar.nome = (char *) realloc(elemento_auxiliar.nome, strlen(f->itens[i].nome) * sizeof(char));
				strcpy(elemento_auxiliar.nome, f->itens[i-1].nome);
				elemento_auxiliar.idade = f->itens[i-1].idade;
				elemento_auxiliar.criterio = f->itens[i-1].criterio;


				strcpy(f->itens[i-1].nome, f->itens[i].nome);
				f->itens[i-1].idade = f->itens[i].idade;
				f->itens[i-1].criterio = f->itens[i].criterio;

				strcpy(f->itens[i].nome, elemento_auxiliar.nome);
				f->itens[i].idade = elemento_auxiliar.idade;
				f->itens[i].criterio = elemento_auxiliar.criterio;

			} else if ((f->itens[i].criterio == 1) && (f->itens[i-1].criterio != 1))
			{
				elemento_auxiliar.nome = (char *) realloc(elemento_auxiliar.nome, strlen(f->itens[i].nome) * sizeof(char));
				strcpy(elemento_auxiliar.nome, f->itens[i-1].nome);
				elemento_auxiliar.idade = f->itens[i-1].idade;
				elemento_auxiliar.criterio = f->itens[i-1].criterio;


				strcpy(f->itens[i-1].nome, f->itens[i].nome);
				f->itens[i-1].idade = f->itens[i].idade;
				f->itens[i-1].criterio = f->itens[i].criterio;

				strcpy(f->itens[i].nome, elemento_auxiliar.nome);
				f->itens[i].idade = elemento_auxiliar.idade;
				f->itens[i].criterio = elemento_auxiliar.criterio;

			}else if ((f->itens[i].idade >= 60) && (f->itens[i-1].idade < 60) && (f->itens[i-1].criterio != 1))
			{
				elemento_auxiliar.nome = (char *) realloc(elemento_auxiliar.nome, strlen(f->itens[i].nome) * sizeof(char));
				strcpy(elemento_auxiliar.nome, f->itens[i-1].nome);
				elemento_auxiliar.idade = f->itens[i-1].idade;
				elemento_auxiliar.criterio = f->itens[i-1].criterio;


				strcpy(f->itens[i-1].nome, f->itens[i].nome);
				f->itens[i-1].idade = f->itens[i].idade;
				f->itens[i-1].criterio = f->itens[i].criterio;

				strcpy(f->itens[i].nome, elemento_auxiliar.nome);
				f->itens[i].idade = elemento_auxiliar.idade;
				f->itens[i].criterio = elemento_auxiliar.criterio;
			}else{

			}
		}
	}
	return f;
}



