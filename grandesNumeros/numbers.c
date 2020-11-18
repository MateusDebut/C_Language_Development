#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "numbers.h"

#define STRING_SIZE 32

struct node
{
	elem *numberVector;
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
	node->numberVector = NULL;
	node->numberVector = (elem *) realloc(node->numberVector, size * sizeof(elem));
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
		index++;
	} while (!feof(stream) && string[index-1] != '\n');
	string[index-1] = '\0';
	string = (char *) realloc (string, sizeof(string));
	return string;
}

comands_t divideComands(char *string){
	comands_t comands;
	comands.comandName = (char *) malloc (STRING_SIZE * sizeof(char));
	comands.num1 = NULL;
	comands.num2 = NULL;
	int i = 0;
	int j = 0;
	char aux[2];
	while(string[i] != 32){
		comands.comandName[j] = string[i];
		i++;
		j++;
	}
	comands.comandName[j] = '\0';
	j = 0;
	i++;
	while(string[i] != 32){
		comands.num1 = (int *) realloc(comands.num1, (j+1) * sizeof(int));
		aux[0] = string[i];
		aux[1] = '\0';
		if (j == 0 && string[i] == '-')
		{
			aux[0] = string[i+1];
			aux[1] = '\0';
			comands.num1[j] = atoi(aux) * -1;
			i++;
		}else{
			comands.num1[j] = atoi(aux);
		}
		i++;
		j++;
	}
	comands.sizeNum1 = j;
	j = 0;
	i++;
	while(string[i] >= 32){
		comands.num2 = (int *) realloc(comands.num2, (j+1) * sizeof(int));
		aux[0] = string[i];
		aux[1] = '\0';
		if (j == 0 && string[i] == '-')
		{
			aux[0] = string[i+1];
			aux[1] = '\0';
			comands.num2[j] = atoi(aux) * -1;
			i++;
		}else{
			comands.num2[j] = atoi(aux);
		}
		i++;
		j++;
	}
	comands.sizeNum2 = j;
	return comands;
}

