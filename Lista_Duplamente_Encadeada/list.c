#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct node
{
	elem info;
	node_t *previous;
	node_t *next;
};

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


int putOnList(list_t *l, elem x){
	assert(l != NULL);
	node_t *pointer = (node_t *)malloc(sizeof(node_t)); 
	pointer->info = x;
	pointer->next = NULL;
	pointer->previous = NULL;

	node_t *aux;
	node_t *prev;

	prev = NULL;
	aux = l->initial;

	while(aux != NULL && x > aux->info){
		prev = aux;
		aux = aux->next;
	}

	//Case where x alredy exist on the list
	if (aux != NULL && x == aux->info){
		free(pointer);
		return 0;
	}

	//In which case x must be inserted in the starting position (smaller element or empty list)
	if (prev == NULL)
	{
		pointer->next = l->initial;
		if (l->initial != NULL)
			l->initial->previous = pointer;
		l->initial = pointer;
	}
	//In which case x will be inserted on the middle or in the final of the list 
	else{
		pointer->next = prev->next;
		prev->next = pointer;
		if (pointer->next != NULL)
			pointer->next->previous = pointer;
		else
			l->final = pointer;
		pointer->previous = prev;
	}
	return 1;
}

int removeFromList(list_t *l, elem x){
	assert(l != NULL);

	node_t *pointer = l->initial;
	node_t *prev = NULL;

	while(pointer != NULL && x > pointer->info){
		prev = pointer;
		pointer = pointer->next;
	}

	if (pointer == NULL)
	{
		return 0;
	}

	//removing the first item from the list
	if (prev == NULL)
	{
		l->initial = l->initial->next;
		if(l->initial != NULL)
			l->initial->previous = NULL;
		else
			l->final = NULL;
		free(pointer);
	}
	//removing element from de middle or final of the list
	else{
		if(pointer->next == NULL){
			l->final = pointer->previous;
			prev->next = NULL;
			free(pointer);
		}
		else{
			prev->next = pointer->next;
			pointer->next->previous = prev;
			free(pointer);
		}
	}
	return 1;
}

void printList(list_t *l){
	assert(l != NULL);
	node_t *pointer = l->initial;
	while(pointer != NULL){
		printf("%d ", pointer->info);
		pointer = pointer->next;
	}
	printf("\n");
}

void printListBackwards(list_t *l){

	assert(l != NULL);
	node_t *pointer = l->final;
	while(pointer != NULL){
		printf("%d ", pointer->info);
		pointer = pointer->previous;
	}
	printf("\n");

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