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
		printf("%d\n", vetor[i]);
	}

	return 0;
}

void mergeSort(int *vetor, int inicio, int fim){
	if ((fim - inicio) > 1)
	{
		int meio = (int)((fim + inicio)/2.0);
		mergeSort(vetor, inicio, meio);
		mergeSort(vetor, meio, fim);
		merge(vetor, inicio, meio, fim);
	}
	//return vetor;
}

void merge(int *vetor, int inicio, int meio, int fim){

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