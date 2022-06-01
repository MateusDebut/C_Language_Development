#include "item.h"

struct item
{
	int numero;
};

Item *criarItem(int numero){
	Item *item = (Item *) malloc(sizeof(Item));
	item->numero = numero;
	return item;
}

void destruirItem(Item *item){
	if(item == NULL){
		return;
	}
	free(item);
	item = NULL;
}

int saoItensIguais(Item *item1, Item *item2){
	if (item1->numero == item2->numero)
	{
		return 1;
	}
	return 0;
}

void printItem(Item *item){
	printf("item: %d\n", item->numero);
}