#include <stdio.h>
#include <stdlib.h>

// MATEUS DOS SANTOS RIBEIRO Nº USP: 11796997

unsigned char* funcao(unsigned short* v1, unsigned short* v2, int n);
unsigned char* novaFuncao(unsigned short* v1, unsigned short* v2, int n, int i, unsigned char *found);
unsigned char* funcaoOtimizada(unsigned short* v1, unsigned short* v2, int n, int i, unsigned char *found);

int main(int argc, char const *argv[])
{

	int n;
	scanf("%d", &n);

	unsigned short* v1 = (unsigned short*) malloc(n * sizeof(unsigned short));
	unsigned short* v2 = (unsigned short*) malloc(n * sizeof(unsigned short));

	srand(1);

	v1[0] = rand()%2;
	for (int i = 1; i < n; i++) {
		v1[i] = v1[i-1]+(rand()%3)+1;
	}

	v2[0] = rand()%2;

	for (int i = 1; i < n; i++) {
		v2[i] = v2[i-1]+(rand()%3)+1;
	}
	unsigned char *found = calloc(n, sizeof(unsigned char));
	found = funcaoOtimizada(v1, v2, n, 0, found);

	for (int i = 0; i < n; i++)
	{
		if (found[i] == 1)
		{
			printf("%04hu ", v1[i]);
		}
	}
	printf("\n");


	free(v1);
	free(v2);
	
	return 0;
}

unsigned char* funcao(unsigned short* v1, unsigned short* v2, int n) {
	unsigned char* found = calloc(n, sizeof(unsigned char));
	for (int i = 0; i < n; i++) {
		unsigned short value = v1[i];
		for (int j = 0; j < n; j++) {
			if (value == v2[j]) found[i] = 1;
		}
	}
	return found;
}

unsigned char* novaFuncao(unsigned short* v1, unsigned short* v2, int n, int i, unsigned char *found){
	if (i==n) return found; // c
	unsigned short value = v1[i]; // a
	for (int j = 0; j < n; j++)
	{
		if (value == v2[j]) found[i] = 1; // c + 2a
	}
	return novaFuncao(v1, v2, n, i+1, found); 
}

unsigned char* funcaoOtimizada(unsigned short* v1, unsigned short* v2, int n, int i, unsigned char *found){
	if (i==n) return found; // c
	unsigned short chave = v1[i]; // a
	int inicio = 0, fim = n-1, meio;

	while(inicio <= fim){
		meio = (int)((fim + inicio)/2.0);
		if (v2[meio] == chave)//c
		{
			found[i] = 1;//a
			break;
		}else if (v2[meio] > chave)//a + c
		{
			fim = meio-1;
		}else
		{
			inicio = meio+1;
		}
	}
	return funcaoOtimizada(v1, v2, n, i+1, found); 
}

int buscaBinariaRecursiva(int *vetor, int chave, int inicio, int fim){
	if(inicio >= fim) return -1;

	int centro = (int)((fim + inicio)/2.0);
	if (vetor[centro] == chave)
		return centro;
	else if(vetor[centro] < chave)
		return buscaBinariaRecursiva(vetor, chave, centro + 1, fim);
	else
		return buscaBinariaRecursiva(vetor, chave, inicio, centro -1);
}