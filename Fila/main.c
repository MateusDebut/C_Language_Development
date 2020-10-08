#include <stdio.h>
#include "fila.h"
#include "util.h"

struct elem{
	char *nome;
	int idade;
	int criterio;
};

struct fila{
	int inicio, fim, total;
	elem_t itens[TamFila];
};

typedef struct elem elem_t;
typedef struct fila fila_t;

int main(int argc, char const *argv[])
{
	int n = 0;
	char *entrada = NULL;
	elem_t elemento;
	scanf(" %d ", &n);
	fila_t *fila;
	fila = criar();

	for (int i = 0; i < n; i++)
	{
		entrada = readline(stdin);
		if (identificaEntrada(entrada) == 1)
		{
			if(!(isFull(fila) == 1))
			{
				elemento = separaEmPartes(entrada, elemento);
				inserir(fila, elemento.nome, elemento.idade, elemento.criterio);
				fila = ordenar(fila);
			}else{
				printf("FILA CHEIA\n");
			}
		}else if (identificaEntrada(entrada) == 0)
		{
			if(!(isEmpity(fila) == 1))
			{
				fila = ordenar(fila);
				printf("%s %d %d\n", fila->itens[fila->inicio].nome, fila->itens[fila->inicio].idade, fila->itens[fila->inicio].criterio);
				remover(fila);
			}else{
				printf("FILA VAZIA\n");
			}
		}else{
			printf("Erro\n");
		}
	}

	return 0;
}