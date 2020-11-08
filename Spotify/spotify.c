#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotify.h"

#define STRING_SIZE 256

char *readline(FILE *stream){
	int i = 0;
	char *string = NULL;
	char aux;
	do{
		if (i % STRING_SIZE == 0)
		{
			string = (char*) malloc(STRING_SIZE * (i+1) * sizeof(char));
		}
		aux = getc(stream);
		if (aux == ';')
		{
			string[i] = '\n';
		}
		else{
			string[i] = aux;
		}
		i++;
	}while(!feof(stream) && string[i-1] != '\n');
	string[i-1] = '\0';
	string = (char*) realloc(string, strlen(string));
	return string;
}