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