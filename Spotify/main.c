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

	artista_t *artistas = (artista_t *) malloc(posicao.numero_artistas * sizeof(artista_t));
	for (int i = 0; i < posicao.numero_artistas; i++)
	{
		artistas[i] = criaStructArtista(dados, numero_linhas, posicao, i);
	}

	qsort(artistas, posicao.numero_artistas, sizeof(artista_t), compararPopularidade);
	printf("O Dataset contem %d Artistas e %d Musicas\n", posicao.numero_artistas, numero_linhas);
	printf("Os artistas mais populares sao:\n");
	for (int i = posicao.numero_artistas-1, j = 0; i >= 0; i--, j++){
		printf("(%d) Artista: %s, Musicas: %d musicas, Popularidade: %.2lf, Link: https://open.spotify.com/artist/%s\n", j+1,
		artistas[i].nome_artista, artistas[i].quantidade_musicas ,artistas[i].popularidade, artistas[i].artista_id);
	}

	fclose(fp);
	return 0;
}