#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "numbers.h"

typedef struct node
{
	elem info;
	node_t *previous;
	node_t *next;
}node_t;

struct list
{
	node_t *initial;
	node_t *final;
};

list_t *createList(){
	list_t *pointer;
	pointer = (list_t *) malloc(sizeof(list_t));
	pointer->initial = NULL;
	pointer->final = NULL;
	return pointer;
}

int putInList(list_t *l, elem){

}

int removeFromList(list_t *l, elem x){

}

int printList(list_t *l){
	node_t *pointer = l->initial;
	while(pointer != NULL){
		printf("%d ", pointer->info);
		pointer = pointer->next;
	}
	printf("\n");
}

int printListBackwards(list_t *l){

}

void destroyList(list_t *l){
	if (l != NULL)
	{
		node_t *aux = l->initial;
		while(aux != NULL){
			l->initial = l->initial->next;
			free(aux);
			aux = l->initial;
		}
		free(l);
	}
}