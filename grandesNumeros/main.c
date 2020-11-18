#include <stdio.h>
#include <stdlib.h>
#include "numbers.h"

int main(int argc, char const *argv[])
{
	
	list_t *lista;
	lista  = createList();
	elem *vector1 = (elem *) calloc(4, sizeof(elem));
	elem *vector2 = (elem *) calloc(4, sizeof(elem));
	int tamanho = 0;
	for (int i = 0; i < 3; i++)
	{
		vector1[i] = i*2;
		vector2[i] = i*3;
	}
	putOnList(lista, vector1, 4);
	putOnList(lista, vector2, 4);
	printListBackwards(lista);
	printList(lista);


	return 0;
}