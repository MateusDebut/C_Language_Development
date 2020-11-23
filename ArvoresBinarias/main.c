#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "arvore.h"

int main(int argc, char const *argv[])
{
	int numero_nos;
	scanf("%d", &numero_nos);

	arvore_t *arvore = criaArvore();
	int id, esq, dir;
	for (int i = 0; i < numero_nos; i++)
	{
		scanf("%d %d %d", &id, &esq, &dir);
		if (busca(arvore->raiz, id) == NULL)
		{
			inserir_esq(arvore, id, (i-1));
			inserir_esq(arvore, esq, id);
			inserir_dir(arvore, dir, id);
		}else{
			inserir_esq(arvore, esq, id);
			inserir_dir(arvore, dir, id);
		}
	}
	
	imprimir(arvore->raiz, 0);


	return 0;
}