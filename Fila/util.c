#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "fila.h"

struct elem{
	char *nome;
	int idade;
	int criterio;
};

char *readline(FILE *stream){
	char *string = NULL;
	char aux;
	int i = 0;
	do
	{
		if (i % wordSize == 0)
		{
			string = (char *) realloc(string, wordSize * (i+1));
		}
		aux = getc(stream);
		if (aux == '\n' && i == 0)
		{
			i--;
		}else if(aux != '\n' && aux != '\0'){
			string[i] = aux;
		}else{
			string[i] = '\0';
		}
		i++;
	} while (string[i-1] != '\n' && !feof(stdin) && string[i-1] != '\0');
	string[i-1] = '\0';
	string = (char *) realloc(string, strlen(string)+1);
	return string;
}


int identificaEntrada(char *string){
	if(strstr(string, "SAI") != NULL)
		return 0;
	if(strstr(string, "ENTRA") != NULL)
		return 1;
	return -1;
}

elem_t separaEmPartes(char *string, elem_t elemento){
	int k = 0, i;
	char idade[4];
	char criterio[2];

	elemento.nome = (char *) calloc(256, sizeof(char));
	for (i = 6; string[i] != 32; i++, k++)
	{
		elemento.nome[k] = string[i];
	}
	i++;
	k = 0;
	for (i = i; string[i] != 32; i++, k++)
	{
		idade[k] = string[i];
	}
	k++;
	i++;
	idade[k] = '\0';
	elemento.idade = atoi(idade);

	criterio[0] = string[i];
	criterio[1] = '\0';
	elemento.criterio = atoi(criterio);

	return elemento;
}