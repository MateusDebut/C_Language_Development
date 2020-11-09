//Autor: Mateus dos Santos Ribeiro
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/*
	N == matrixSize
	x == linePixel
	y == columnPixel 
	T == seed
*/

int main(int argc, char const *argv[])
{
	int matrixSize, seed;
	int linePixel, columnPixel;
	scanf("%d", &matrixSize);
	scanf("%d", &linePixel);
	scanf("%d", &columnPixel);
	scanf("%d", &seed);

	int **matrix = generateMatrix(seed, matrixSize);
	char *name = (char*) malloc(256 * sizeof(char));
	name = "Original.pgm";
	generateImage(matrix, matrixSize, name, seed);
	printMatrix(matrixSize, matrix);
	matrix = modifyPixel(linePixel, columnPixel, matrix, seed, matrixSize);
	name = "Modificado.pgm";
	generateImage(matrix, matrixSize, name, seed);
	printf("\n");
	printMatrix(matrixSize, matrix);
	//destroyMatrix(matrixSize, matrix);

	return 0;
}