#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "util.h"

int main(int argc, char const *argv[])
{
	char *nomeArquivo = readline(stdin);

	FILE *filePointer = fopen(nomeArquivo, "r");

	if(!filePointer){
		fprintf(stderr, "Couldn't open %s: %s\n", nomeArquivo, strerror(errno));
		exit(-1);
	} 


	registro_t *registro = NULL;
	int quantidadeRegistros = 0;

	while(!feof(filePointer)){
		registro = (registro_t *) realloc(registro, (quantidadeRegistros + 1) * sizeof(registro_t)) ;
		registro[quantidadeRegistros] = montaRegistro(nomeArquivo, filePointer);
		quantidadeRegistros++;
	}

	for (int i = 1; i < quantidadeRegistros; i++)
	{
		if (registro[i].idadeUsuario >= 18)
		{
			if (registro[i].nomeUsuario[0] == '\0')
			{
				printf("O usuario de identificacao %s eh de maior.\n", registro[i].idUsuario);
			}else{
				printf("O usuario %s eh de maior.\n", registro[i].nomeUsuario);
			}
		}
	}

	return 0;
}