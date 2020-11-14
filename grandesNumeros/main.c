#include <stdio.h>
#include <stdlib.h>
#include "numbers.h"

int main(int argc, char const *argv[])
{
	
	list_t *lista;

	lista  = createList();

	putOnList(lista, 10);
	printList(lista);
	putOnList(lista, 12);
	putOnList(lista, 8);
	printListBackwards(lista);
	removeFromList(lista, 8);
	printList(lista);
	char *palavra = readline(stdin);
	char **palavras;
	palavras = divideLine(palavra);
	for (int i = 0; i < 3; i++)
	{
		
	}

	return 0;
}