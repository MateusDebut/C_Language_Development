#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"

#define TAMANHO_DEFAULT_STRING 256

//Realiza a leitura e o armazenamento dos dados de um arquivo em um ponteiro de char
//enquanto esses forem diferentes de \n ou EOF. Retorna o ponteiro com a string armazenada
char *readline(FILE *stream){
	int indice = 0;
	char *string = NULL;
    char aux;
	do
	{
		if (indice%TAMANHO_DEFAULT_STRING == 0)
		{
			string = (char*) realloc(string, ((indice % TAMANHO_DEFAULT_STRING) + 1) * TAMANHO_DEFAULT_STRING * sizeof(char));
		}
		aux = getc(stream);
		if(aux == -1 || aux == 13) break;
        string[indice] = aux;
        indice++;

    //Esse '\t' quebrou minhas pernas, hein
	} while (string[indice-1] != '\n' && !feof(stream) && string[indice-1] != '\t' && string[indice-1] != EOF);

    if(string[indice-1] == 'F') string[indice] = '\0';
    else string[indice] = '\0';

	printf("string : %s\n", string);

	return string;
}