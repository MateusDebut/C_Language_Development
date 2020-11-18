#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "numbers.h"

#define STRING_SIZE 32

struct node
{
	elem numberVector[4];
	node_t *previous;
	node_t *next;
	int size;
};

struct list
{
	node_t *initial;
	node_t *final;
};

list_t *createList(){
	list_t *list;
	list = (list_t *) malloc(sizeof(list_t));
	list->initial = NULL;
	list->final = NULL;
	return list;
}


//Para calcular o size podemos usar o sizeof de elem *vector e dividi-lo pelo sizeof do tipo de elem
int putOnList(list_t *l, elem *vector, int size){
	assert(l != NULL);
	node_t *node = (node_t *) malloc(sizeof(node_t));
	//caso onde o elemento será o primeiro da fila
	if (l->initial == NULL)
	{
		for (int i = 0; i < size; i++)
		{
			node->numberVector[i] = vector[i];
		}
		node->previous = NULL;
		node->next = NULL;
		l->initial = node;
		l->final = node;
		node->size = size;
	}
	//Caso em que já existem elementos na fila
	else
	{
		for (int i = 0; i < size; i++)
		{
			node->numberVector[i] = vector[i];
		}
		l->final->next = node;
		node->previous = l->final;
		node->next = NULL;
		l->final = node;
		node->size = size;
	}
	return 0;
}

int removeFromList(list_t *l, elem x){
	return 1;
}

void printList(list_t *l){
	assert(l != NULL);
	node_t *pointer = l->initial;
	while(pointer != NULL){
		for (int i = 0; i < pointer->size; i++)
		{
			printf("%d", pointer->numberVector[i]);
		}
		printf(" ");
		pointer = pointer->next;
	}
	printf("\n");
}

void printListBackwards(list_t *l){
	assert(l != NULL);
	node_t *pointer = l->final;
	while(pointer != NULL){
		for (int i = 0; i < pointer->size; i++)
		{
			printf("%d", pointer->numberVector[i]);
		}
		printf(" ");
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

char *readline(FILE *stream){
	char *string = NULL;
	int index = 0;
	do
	{
		if (index % STRING_SIZE == 0)
		{
			string = (char *) realloc (string, STRING_SIZE * sizeof(char));
		}
		string[index] = getc(stream);

	} while (!feof(stream) && string[index++] != '\n');
	string[index-1] = '\0';
	string = (char *) realloc (string, sizeof(string));
	return string;
}

char **divideLine(char *string){
	char **stringVector = (char **) malloc (3 * sizeof(char *));
	for (int i = 0; i < 3; i++)
	{
		stringVector[i] = (char *) malloc(STRING_SIZE * sizeof(char));
	}

	int controller = 0;	
	for (int i = controller; i < strlen(string); i++)
	{
		if(string[i] != 32 && string[i] != '\n'){
			stringVector[0][i] = string[i];
		}else{
			stringVector[0][i] = '\0';
			controller = i;
			break;
		}
	}

	for (int i = controller+1, j = 0; i < strlen(string); i++, j++)
	{
		if(string[i] != 32 && string[i] != '\n'){
			stringVector[1][j] = string[i];
		}else{
			stringVector[1][j] = '\0';
			controller = i;
			break;
		}
	}

	for (int i = controller+1, j = 0; i < strlen(string); i++, j++)
	{
		if(string[i] != 32 && string[i] != '\n'){
			stringVector[2][j] = string[i];
		}else{
			stringVector[2][j] = '\0';
			break;
		}
	}
	return stringVector;
}

