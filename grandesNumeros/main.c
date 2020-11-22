#include <stdio.h>
#include <stdlib.h>
#include "numbers.h"

int main(int argc, char const *argv[])
{
	int numeroComandos = 0;
	scanf("%d ", &numeroComandos);
	list_t **listas = (list_t **) malloc (numeroComandos * sizeof(list_t*));
	for (int i = 0; i < numeroComandos; i++)
	{
		listas[i]  = createList();
	}
	char **entradas = (char **) malloc(numeroComandos * sizeof(char *));
	for (int i = 0; i < numeroComandos; i++)
	{
		entradas[i] = NULL;
		entradas[i] = readline(stdin);
	}

	commands_t *comandos = (commands_t *) malloc (numeroComandos * sizeof(commands_t));
	for (int i = 0; i < numeroComandos; i++)
	{
		comandos[i] = divideCommands(entradas[i]);
	}

	for (int i = 0; i < numeroComandos; i++)
	{
		putOnList(listas[i], comandos[i].num1, comandos[i].sizeNum1);
		putOnList(listas[i], comandos[i].num2, comandos[i].sizeNum2);
	}
	int opcao = 0;
	for (int i = 0; i < numeroComandos; i++)
	{
		opcao = selectCommand(comandos[i].commandName);
		if (opcao == 1)
		{
			node_t *result = sum(listas[i]);
			printf("Resultado %i: ", i+1);
			for (int j = 0; j < result->size; j++)
			{
				printf("%d", result->numberVector[j]);
			}
			printf("\n");
		}
		if (opcao == 2)
		{
			printf("Resultado %i: %d\n", i+1, big(listas[i]));
		}
		if (opcao == 3)
		{
			printf("Resultado %i: %d\n", i+1, sml(listas[i]));
		}
		if (opcao == 4)
		{
			printf("Resultado %i: %d\n", i+1, eql(listas[i]));
		}
	}
	return 0;
}