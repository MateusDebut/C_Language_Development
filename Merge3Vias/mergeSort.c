#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio, int fim);
int *readVector(FILE *stream, int *i);
int calcularTamanhoVetor(int *vetor);

int main(int argc, char const *argv[])
{
	int *vetor;
	int tamanho = 0;
	vetor = readVector(stdin, &tamanho);
	for (int i = 0; i < tamanho; i++)
	{
		printf("%d ", vetor[i]);
	}

	mergeSort(vetor, 0, tamanho);

	return 0;
}

void mergeSort(int *vetor, int inicio, int fim){
	if ((fim - inicio) <= 1) return;
		int meio = (int)((fim + inicio)/2.0);
		mergeSort(vetor, inicio, meio);
		mergeSort(vetor, meio+1, fim);
		merge(vetor, inicio, meio, fim);
	//return vetor;
}

void merge(int *vetor, int inicio, int meio, int fim){
	int *aux = (int *) malloc((fim-inicio) * sizeof(int) + 1);
	int i = inicio;
	int j = meio+1;
	int k = 0;
	
	while(i <= meio && j <= fim){
		if (vetor[i] <= vetor[j])
		{
			aux[k] = vetor[i];
			i++;
		}else{
			aux[k] = vetor[j];
			j++;
		}
		k++;
	}

	while(i <= c){
		aux[k] = v[i];
		i++; k++;
	}

		while(j <= fim){
		aux[k] = v[j];
		i++; k++;
	}

	for (i = inicio, k = 0; i <= fim; i++, k++)
	{
		vetor[i] = aux[k];
	}

	free(aux);
}

int *readVector(FILE *stream, int *i){
	*i = 0;
	int *vector = NULL;
	while(!feof(stream))
	{
		vector = (int *) realloc(vector, (*i+1) * sizeof(int));
		scanf("%d", &vector[*i]);
		*i = *i + 1;
	}
	return vector;
}