#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio, int fim);
int *readVector(FILE *stream, int *i);
int calcularTamanhoVetor(int *vetor);
void imprimeVetor(int *vetor, int tamanho);

int main(int argc, char const *argv[])
{
	int *vetor;
	int tamanho = 0;
	vetor = readVector(stdin, &tamanho);
	imprimeVetor(vetor, tamanho);
	mergeSort(vetor, 0, tamanho-1);
	imprimeVetor(vetor, tamanho);

	return 0;
}

void mergeSort(int *vetor, int inicio, int fim){
	if (fim <= inicio) return;
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

	while(i <= meio){
		aux[k] = vetor[i];
		i++; k++;
	}

		while(j <= fim){
		aux[k] = vetor[j];
		j++; k++;
	}

	for (i = inicio, k = 0; i <= fim; i++, k++)
	{
		vetor[i] = aux[k];
	}

	free(aux);
}

int *readVector(FILE *stream, int *i){
	*i = 0;
	int j = 0;
	int *vector = NULL;
	
	do{
		vector = (int *) realloc(vector, (j+1) * sizeof(int));
		scanf("%d", &vector[j]);
		j = j + 1;
		*i = *i + 1;
	}while(!feof(stream));
	//printf("Esse é o último elemento do vetor: %d\n", vector[j]);
	vector = (int *) realloc(vector, (j-1) * sizeof(int));
	//printf("Esse é o último elemento do vetor: %d\n", vector[j-1]);
	return vector;
}

void imprimeVetor(int *vetor, int tamanho){
	for (int i = 0; i < tamanho; i++)
	{
		printf("%d ", vetor[i]);
	}
	printf("\n");
}