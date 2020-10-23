#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
	lista_t *l = cria();
	int i = 0;

	for (i = 0; i < 5; i++)
	{
		insere(l, (i+1)*i);
	}

	imprimir(l);

	remover(l, 20);

	imprimir(l);

	liberar(l);

	return 0;
}