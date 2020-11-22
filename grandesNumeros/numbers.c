#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "numbers.h"

#define STRING_SIZE 32

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
};


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

commands_t divideCommands(char *string){
	commands_t commands;
	commands.commandName = (char *) malloc (STRING_SIZE * sizeof(char));
	commands.num1 = NULL;
	commands.num2 = NULL;
	int i = 0;
	int j = 0;
	char aux[2];
	while(string[i] != 32){
		commands.commandName[j] = string[i];
		i++;
		j++;
	}
	commands.commandName[j] = '\0';
	j = 0;
	i++;
	while(string[i] != 32){
		commands.num1 = (int *) realloc(commands.num1, (j+1) * sizeof(int));
		aux[0] = string[i];
		aux[1] = '\0';
		if (j == 0 && string[i] == '-')
		{
			aux[0] = string[i+1];
			aux[1] = '\0';
			commands.num1[j] = atoi(aux) * -1;
			i++;
		}else{
			commands.num1[j] = atoi(aux);
		}
		i++;
		j++;
	}
	commands.sizeNum1 = j;
	j = 0;
	i++;
	while(string[i] >= 32){
		commands.num2 = (int *) realloc(commands.num2, (j+1) * sizeof(int));
		aux[0] = string[i];
		aux[1] = '\0';
		if (j == 0 && string[i] == '-')
		{
			aux[0] = string[i+1];
			aux[1] = '\0';
			commands.num2[j] = atoi(aux) * -1;
			i++;
		}else{
			commands.num2[j] = atoi(aux);
		}
		i++;
		j++;
	}
	commands.sizeNum2 = j;
	return commands;
}

node_t *sum(list_t *l){
	assert(l != NULL);

	node_t *pointer = l->initial;
	node_t *result = (node_t *) malloc(sizeof(node_t));;
	result->numberVector = NULL;
	
	int smallest;
	while(pointer->next != NULL){
		if (pointer->size > pointer->next->size)
		{
			result->numberVector = (int *) realloc(result->numberVector, pointer->size * sizeof(int));
			result->size = pointer->size;
			smallest = pointer->next->size;
		}
		else{
			result->numberVector = (int *) realloc(result->numberVector, pointer->next->size * sizeof(int));
			result->size = pointer->next->size;
			smallest = pointer->size;
		}
		pointer = pointer->next;
	}

	pointer = l->initial;
	if (pointer->numberVector[0] > 0 && pointer->next->numberVector[0] > 0)
	{
		int carry;
		while(pointer->next != NULL){
			int i, j;
			for (i = pointer->size -1, j = pointer->next->size -1; i >= 0 && j >= 0; i--, j--)
			{
				carry = 0;
				if (pointer->numberVector[i] + pointer->next->numberVector[j] >= 10)
				{
					carry = 1;
				}
				result->numberVector[i] = (int)(pointer->numberVector[i] + pointer->next->numberVector[j])%10;
				if (pointer->size > pointer->next->size)
				{
					pointer->numberVector[i-1] = pointer->numberVector[i-1] + carry;
				}
				else{
					pointer->next->numberVector[j-1] = pointer->next->numberVector[j-1] + carry;
				}
			}
			while(i >= 0){
				result->numberVector[i] = pointer->numberVector[i];
				i--;
			}
			while(j >= 0){
				result->numberVector[j] = pointer->next->numberVector[j];
				j--;
			}
			pointer = pointer->next;
		}
		putOnList(l, result->numberVector, result->size);
	}
	return result;
}

int selectCommand(char *command){
	if (strstr(command, "sum") != NULL)
	{
		return 1;
	}
	if (strstr(command, "big") != NULL)
	{
		return 2;
	}
	if (strstr(command, "sml") != NULL)
	{
		return 3;
	}
	if (strstr(command, "eql") != NULL)
	{
		return 4;
	}
	return 0;
}

int big(list_t *l){
	for (int i = 0; i < l->initial->size; i++)
	{
		if (l->initial->numberVector[i] > l->initial->next->numberVector[i] )
		{
			return 1;
		}
	}
	return 0;
}

int sml(list_t *l){
	for (int i = 0; i < l->initial->size; i++)
	{
		if (l->initial->numberVector[i] < l->initial->next->numberVector[i])
		{
			return 1;
		}
	}
	return 0;
}

int eql(list_t *l){
	if (l->initial->size != l->initial->next->size)
	{
		return 0;
	}

	for (int i = 0; i < l->initial->size; i++)
	{
		if (l->initial->numberVector[i] != l->initial->next->numberVector[i])
		{
			return 0;
		}
	}
	return 1;
}