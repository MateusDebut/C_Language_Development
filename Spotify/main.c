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
	int numero_linhas = 0;
	header_t header;
	header = criaStructHeader(header, fp);

	while(!feof(fp)){
		dados = (dados_t*) realloc(dados, (numero_linhas+1)*sizeof(dados_t));
		dados[numero_linhas] = criaStructDados(dados[numero_linhas], fp);
		numero_linhas++;
	}

	numero_linhas--;
	qsort(dados, numero_linhas, sizeof(dados_t), compararNome);
	posicao_t posicao;
	posicao = contaArtista(dados, numero_linhas, posicao);

	fclose(fp);
	return 0;
}