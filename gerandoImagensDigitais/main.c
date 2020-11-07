//Autor: Mateus dos Santos Ribeiro; Github: https://github.com/MateusBCC020/
#include <stdio.h>
#include <stdlib.h>
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

	int ** matrix = generateMatrix(seed, matrixSize);
	printMatrix(matrixSize, matrix);
	matrix = modifyPixel(linePixel, columnPixel, matrix, seed, matrixSize);
	printf("\n");
	printMatrix(matrixSize, matrix);
	//destroyMatrix(matrixSize, matrix);

	return 0;
}