/*
	Está é a implementação do algoritmo mergesort de ordenação. Um algoritmo extremamente rápido para ordenar vetores
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_VECTOR 10

void mergesort(int *v, int ini, int fim);

int main(int argc, char const *argv[])
{
	int *vetor = (int *)malloc(SIZE_VECTOR * sizeof(int));
	srand(time(NULL));
	for (int i = 0; i < SIZE_VECTOR; i++)
	{
		vetor[i] = (int) (rand()%10);
	}
	for (int i = 0; i < SIZE_VECTOR; i++)
	{
		printf("%d ", vetor[i]);
	}
	printf("\n\n");
	mergesort(vetor, 0, SIZE_VECTOR-1);
	for (int i = 0; i < SIZE_VECTOR; i++)
	{
		printf("%d ", vetor[i]);
	}
	printf("\n");
	return 0;
}

void mergesort(int *v, int ini, int fim){
	// caso base - vetor unitário
	if(fim <= ini) return;

	int c = (int) ((ini + fim)/2.0);

	// dividir
	mergesort(v, ini, c);
	mergesort(v, c+1, fim);

	int *aux = (int *) malloc(sizeof(int) * (fim + ini) + 1);

	int i = ini;
	int j = c+1;
	int k = 0;

	while(i <= c && j <= fim)
	{
		if(v[i] <= v[j])
		{
			aux[k] = v[i];
			i++;
		}else
		{
			aux[k] = v[j];
			j++;
		}
		k++;
	}

	while(i <= c)
	{
		aux[k] = v[i];
		i++;
		k++;
	}

	while(j <= fim)
	{
		aux[k] = v[j];
		j++;
		k++;
	}

	for (int i = ini, k = 0; i <= fim; i++, k++)
	{
		v[i] = aux[k];
	}

	free(aux);
}