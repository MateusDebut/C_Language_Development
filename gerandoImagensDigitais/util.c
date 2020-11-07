#include <stdio.h>
#include <stdlib.h>

int **generateMatrix(int seed, int matrixSize){
	srand((unsigned)seed);
	int **matrix = (int **) malloc(matrixSize * sizeof(int*));
	for (int i = 0; i < matrixSize; i++)
	{
		matrix[i] = (int *) malloc(matrixSize * sizeof(int));
	}

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			matrix[i][j] = rand() % 256;
		}
	}
	return matrix;
}

void destroyMatrix(int matrixSize, int ** matrix){
	for (int i = 0; i < matrixSize; ++i)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void printMatrix(int matrixSize, int **matrix){
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int **modifyPixel(int linePixel, int columnPixel, int **matrix, int t, int matrixSize){
	printf("Aqui 1\n");
	printf("linha: %d, coluna: %d, tamanho: %d\n", linePixel, columnPixel, matrixSize);
	//Primeiro caso base (as bordas da matriz foram atingidas)
	if((linePixel <= 0 && columnPixel >= 0)
		|| (linePixel <= 0 && columnPixel >= matrixSize) || (linePixel >= matrixSize && columnPixel <= 0)
		|| (linePixel >= matrixSize && columnPixel >= matrixSize)){
		return matrix;
	}
		

	printf("Aqui 2\n");
	int p = matrix[linePixel][columnPixel];
	int v;
	int m;
	if (linePixel-1 < 0) return matrix;
	if (columnPixel-1 < 0) return matrix;

	v = matrix[linePixel-1][columnPixel];
	if (p!=v){
		m = abs(p-v);
		printf("Aqui 4\n");
		if (m <= t){
			matrix[linePixel-1][columnPixel] = p;
			printf("linha: %d, coluna: %d, tamanho: %d\n", linePixel, columnPixel, matrixSize);
			modifyPixel(linePixel-1, columnPixel, matrix, t, matrixSize);
		}
	}


	v = matrix[linePixel][columnPixel+1];

	if (p!=v){
		m = abs(p-v);
		printf("Aqui 5\n");
		if (m <= t){
			matrix[linePixel][columnPixel+1] = p;
			printf("linha: %d, coluna: %d, tamanho: %d\n", linePixel, columnPixel, matrixSize);
			modifyPixel(linePixel, columnPixel+1, matrix, t, matrixSize);
		}
	}

	v = matrix[linePixel+1][columnPixel];
	if (p!=v){
		m = abs(p-v);
		printf("Aqui 6\n");
		if (m <= t){
			matrix[linePixel+1][columnPixel] = p;
			printf("linha: %d, coluna: %d, tamanho: %d\n", linePixel, columnPixel, matrixSize);
			modifyPixel(linePixel+1, columnPixel, matrix, t, matrixSize);
		}
	}
	v = matrix[linePixel][columnPixel-1];
	if (p!=v){
		m = abs(p-v);
		printf("Aqui 7\n");
		if (m <= t){
			matrix[linePixel][columnPixel-1] = p;
			printf("linha: %d, coluna: %d, tamanho: %d\n", linePixel, columnPixel, matrixSize);
			modifyPixel( linePixel, columnPixel-1, matrix, t, matrixSize);
		}
	}
	printf("Aqui 8\n");
	return matrix;
}