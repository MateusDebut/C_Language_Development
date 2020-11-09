int **generateMatrix(int seed, int matrizSize);
void destroyMatrix(int matrizSize, int ** matrix);
void printMatrix(int matrizSize, int **matrix);
int **modifyPixel(int linePixel, int columnPixel, int **matrix, int t, int matrixSize);
void generateImage(int **matrix, int matrixSize, char *name, int seed);