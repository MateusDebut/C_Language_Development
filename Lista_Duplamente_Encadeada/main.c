#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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
	return 0;
}