#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

char *readline(FILE *stream){
	int i = 0;
	char *string = NULL;
	char aux;
	do{
		//Verifica se o tamanho da string deve ser incrementado (apenas quando
		//string == NULL e quando string atingir MAX_TAMANHO_CAMPO)
		if (i % MAX_TAMANHO_CAMPO == 0)
		{
			string = (char*) malloc(MAX_TAMANHO_CAMPO * (i+1) * sizeof(char));
		}
		aux = getc(stream);
		//Essa linha é para tratar espaços e pulos de linha como primeiros caracteres
		//Se isso ocorrer o i será decrementado para que possamos salvar um caracter válido na primeira posição
		if ((aux == 32 && i == 0) || (aux == '\n' && i == 0))
		{
			i--;
		}else{
			string[i] = aux;
		}
		i++;
	}while(!feof(stream) && string[i-1] != ',' && string[i-1] != '\n');
	//Verifica se a string está vazia(i-1 == 0). Se estiver, coloca terminadores
	// de string nos dois espaços alocados
	if (i-1 == 0)
	{
		string[i-1] = '\0';
		string[i] = '\0';
		return string;
	}
	string[i-1] = '\0';
	string = (char*) realloc(string, strlen(string));
	return string;
}



registro_t montaRegistro(char *nomeArquivo, FILE  *filePointer){
	registro_t registro;
	registro.idUsuario = readline(filePointer);
	registro.nomeUsuario = readline(filePointer);
	registro.idadeUsuario = atoi(readline(filePointer));

	return registro;
}