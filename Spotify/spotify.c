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
		if ((aux == 32 && i == 0) || (aux == '\n' && i == 0))
		{
			i--;
		}else{
			string[i] = aux;
		}
		i++;
	}while(!feof(stream) && string[i-1] != ';' && string[i-1] != '\n');
	if (i-1 == 0)
	{
		string[i-1] = '\0';
		string[i] = '\0';
		printf("%s\n", string);
		return string;
	}
	string[i-1] = '\0';
	string = (char*) realloc(string, strlen(string));
	return string;
}

header_t criaStructHeader(header_t header, FILE *fp){
	header.track_name = readline(fp);
	header.track_id = readline(fp);
	header.album_name = readline(fp);
	header.album_id = readline(fp);
	header.artist_name = readline(fp);
	header.artist_id = readline(fp);
	header.release_date = readline(fp);
	header.length = readline(fp);
	header.popularity = readline(fp);
	header.acousticness = readline(fp);
	header.danceability = readline(fp);
	header.energy = readline(fp);
	header.instrumentalness = readline(fp);
	header.liveness = readline(fp);
	header.loudness = readline(fp);
	header.speechiness = readline(fp);
	header.tempo = readline(fp);
	header.time_signature = readline(fp);
}

dados_t criaStructDados(dados_t dados, FILE *fp){
	dados.track_name = readline(fp);
	dados.track_id = readline(fp);
	dados.album_name = readline(fp);
	dados.album_id = readline(fp);
	dados.artist_name = readline(fp);
	dados.artist_id = readline(fp);
	dados.release_date = readline(fp);
	dados.length = atoi(readline(fp));
	dados.popularity = atoi(readline(fp));
	dados.acousticness = atof(readline(fp));
	dados.danceability = atof(readline(fp));
	dados.energy = atof(readline(fp));
	dados.instrumentalness = readline(fp);
	dados.liveness = atof(readline(fp));
	dados.loudness = atof(readline(fp));
	dados.speechiness = atof(readline(fp));
	dados.tempo = atof(readline(fp));
	dados.time_signature = atoi(readline(fp));

	return dados;
}

void imprimeDados(dados_t dados){
	printf("%s\n", dados.track_name);
	printf("%s\n", dados.track_id);
	printf("%s\n", dados.album_name);
	printf("%s\n", dados.album_id);
	printf("%s\n", dados.artist_name);
	printf("%s\n", dados.artist_id);
	printf("%s\n", dados.release_date);
	printf("%d\n", dados.length);
	printf("%d\n", dados.popularity);
	printf("%f\n", dados.acousticness);
	printf("%f\n", dados.danceability);
	printf("%f\n", dados.energy);
	printf("%s\n", dados.instrumentalness);
	printf("%f\n", dados.liveness);
	printf("%f\n", dados.loudness);
	printf("%f\n", dados.speechiness);
	printf("%f\n", dados.tempo);
	printf("%d\n", dados.time_signature);
	printf("\n");
}

int compararNome (const void *a, const void *b) {
    return strcmp (((dados_t *)a)->artist_name,((dados_t *)b)->artist_name);
}

posicao_t contaArtista(dados_t *dados, int numeroDados, posicao_t posicao){
	posicao.numero_artistas = 0;
	posicao.posicoes = NULL;
	for (int i = 0; i < numeroDados-1; i++)
	{
		if (strcmp(dados[i].artist_name, dados[i+1].artist_name) != 0)
		{
			posicao.posicoes = (int *) realloc(posicao.posicoes, (posicao.numero_artistas+1) * sizeof(int));
			posicao.posicoes[posicao.numero_artistas] = i+1;
			posicao.numero_artistas++;
		}
	}
	return posicao;
}



