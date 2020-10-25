#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio1, int meio2, int fim);
int *readVector(FILE *stream, int *i);
int calcularTamanhoVetor(int *vetor);
void imprimeVetor(int *vetor, int tamanho);

int main(int argc, char const *argv[])
{
	int *vetor;
	int tamanho = 0;
	vetor = readVector(stdin, &tamanho);
	imprimeVetor(vetor, tamanho);
	mergeSort(vetor, 0, tamanho);
	imprimeVetor(vetor, tamanho);

	return 0;
}

void mergeSort(int *vetor, int inicio, int fim){
	if (fim - inicio < 2) return;
		int meio1 = inicio + (int)((fim - inicio)/3.0);
		int meio2 = inicio + 2 * ((int)((fim - inicio)/3.0)) + 1;
		mergeSort(vetor, inicio, meio1);
		mergeSort(vetor, meio1, meio2);
		mergeSort(vetor, meio2, fim);
		merge(vetor, inicio, meio1, meio2, fim);
}

void merge(int *vetor, int inicio, int meio1, int meio2, int fim){
	int *aux = (int *) malloc((fim-inicio) * sizeof(int) + 1);
	int i = inicio;
	int j = meio1;
	int k = meio2;
	int l = 0;
	while((i < meio1) && (j < meio2) && (k < fim)){
		if (vetor[i] < vetor[j])
		{
			if (vetor[i] < vetor[k])
			{
				aux[l++] = vetor[i++];
			}else{
				aux[l++] = vetor[k++];
			}
		}else{
			if (vetor[j] < vetor[k])
			{
				aux[l++] = vetor[j++];
			}else{
				aux[l++] = vetor[k++];
			}
		}
	}

	while((i < meio1) && (j < meio2)){
		if (vetor[i] < vetor[j])
		{
			aux[l++] = vetor[i++];
		}else{
			aux[l++] = vetor[j++];
		}
	}

	while((j < meio2) && (k < fim)){
		if (vetor[j] < vetor[k])
		{
			aux[l++] = vetor[j++];
		}else{
			aux[l++] = vetor[k++];
		}
	}

	while((i < meio1) && (k < fim)){
		if (vetor[i] < vetor[k])
		{
			aux[l++] = vetor[i++];
		}else{
			aux[l++] = vetor[k++];
		}
	}

	while(i < meio1){
		aux[l++] = vetor[i++];
	}

	while(j < meio2){
		aux[l++] = vetor[j++];
	}

	while(k < fim){
		aux[l++] = vetor[k++];
	}

	for (i = inicio, k = 0; i < fim; i++, k++)
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
	vector = (int *) realloc(vector, (j-2) * sizeof(int));
	return vector;
}

void imprimeVetor(int *vetor, int tamanho){
	for (int i = 0; i < tamanho; i++)
	{
		printf("%d ", vetor[i]);
	}
	printf("\n");
}