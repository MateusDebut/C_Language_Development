#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main(int argc, char const *argv[])
{
	arvore_t *arvore = criaArvore();
	inserir_esq(arvore, 1, -1);
	inserir_esq(arvore, 2, 1);
	inserir_dir(arvore, 3, 1);
	inserir_esq(arvore, 4, 3);
	inserir_dir(arvore, 5, 3);
	inserir_esq(arvore, 6, 4);

	imprimir(arvore->raiz);
	printf("\n");

	return 0;
}