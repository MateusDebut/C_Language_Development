#include <stdio.h>
#include <stdlib.h>
#include "dicionario.h"

int main(int argc, char const *argv[])
{
	skiplist_t *lista = criar(5, 0.5);
	inserir(lista, 1);
	inserir(lista, 2);
	inserir(lista, 3);
	inserir(lista, 4);

	printf("%d\n", inserir(lista, 4));
	printf("%d\n", remover(lista, 2));
	printf("%d\n", buscar(lista, 3));

	destruir(lista);
	return 0;
}