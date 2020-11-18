#include <stdio.h>
#include <stdlib.h>
#include "numbers.h"

int main(int argc, char const *argv[])
{
	
	list_t *lista;
	lista  = createList();
	int numeroComandos = 0;

	scanf("%d ", &numeroComandos);
	char **entradas = (char **) malloc(numeroComandos * sizeof(char *));
	for (int i = 0; i < numeroComandos; i++)
	{
		entradas[i] = NULL;
		entradas[i] = readline(stdin);
		printf("%s\n", entradas[i]);
	}
	printf("\n");

	comands_t *comandos = (comands_t *) malloc (numeroComandos * sizeof(comands_t));
	for (int i = 0; i < numeroComandos; i++)
	{
		comandos[i] = divideComands(entradas[i]);
		printf("%s, ", comandos[i].comandName);
		for (int j = 0; j < comandos[i].sizeNum1; j++)
		{
			printf("%d", comandos[i].num1[j]);
		}
		printf(", ");

		for (int j = 0; j < comandos[i].sizeNum2; j++)
		{
			printf("%d", comandos[i].num2[j]);
		}
		
		printf("\n");

	}

	//putOnList(lista, vector1, 4);
	//printListBackwards(lista);
	//printList(lista);


	return 0;
}