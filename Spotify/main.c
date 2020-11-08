#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotify.h"

int main(int argc, char const *argv[])
{
	char *nomeArquivo;
	nomeArquivo = readline(stdin);
	dados_t *dados = NULL;
	FILE *fp;
	fp = fopen(nomeArquivo, "r");
	int i = 0;
	header_t header;

	while(!feof(fp)){
		if (i==0)
		{
			header = criaStructHeader(header, fp);
		}else{
			dados = (dados_t*) realloc(dados, (i+1)*sizeof(dados_t));
			dados[i] = criaStructDados(dados[i], fp);
		}
		i++;
		printf("(%i)\n", i);
	}
	fclose(fp);
	return 0;
}