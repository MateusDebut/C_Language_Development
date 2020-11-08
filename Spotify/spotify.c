#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spotify.h"

#define STRING_SIZE 256

char *readline(FILE *stream){
	int i = 0;
	char *string = NULL;
	char aux;
	int controle = 0;
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
	string[i-1] = '\0';
	string = (char*) realloc(string, strlen(string));
	printf("%s\n", string);
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
	//fscanf(fp, "%i", &dados.time_signature);

	return dados;
}