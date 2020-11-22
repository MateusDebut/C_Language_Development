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
		//Verifica se o tamanho da string deve ser incrementado (apenas quando
		//string == NULL e quando string atingir STRING_SIZE)
		if (i % STRING_SIZE == 0)
		{
			string = (char*) malloc(STRING_SIZE * (i+1) * sizeof(char));
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
	}while(!feof(stream) && string[i-1] != ';' && string[i-1] != '\n');
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
	return header;
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

//Ambas as funções de comparação serão usadas no qSort
int compararNome (const void *a, const void *b) {
    return strcmp (((dados_t *)a)->artist_name,((dados_t *)b)->artist_name);
}

int compararPopularidade(const void *x, const void *y){
    float pri = ((artista_t *)x)->popularidade;
    float seg = ((artista_t *)y)->popularidade;
    if (pri > seg)
    {
    	return 1;
    }
    else if (seg > pri)
    {
    	return -1;
    }
    return 0;
}



posicao_t contaArtista(dados_t *dados, int numeroDados, posicao_t posicao){
	posicao.numero_artistas = 0;
	posicao.posicoes = NULL;
	//Ao chegar nessa função as structs estarão ordenadas em ordem alfabética (pelo artist_name)
	//Esse laço testará as ocorrências de artist_name sequentes e diferentes e quando encontrar
	//Considerará isso um novo artista (por causa da ordem alfabética)
	for (int i = 0; i < numeroDados; i++)
	{
		//Essa condição evita que o programa verifique posições de memória não alocadas
		if (i+1 < numeroDados)
		{
			//verifica se os artist_names são diferentes, se sim, separa um espaço no
			//vetor para quardar o indice do novo artista no vetor de structs e incrementa o contador de artistas
			if (strcmp(dados[i].artist_name, dados[i+1].artist_name) != 0)
			{
				posicao.posicoes = (int *) realloc(posicao.posicoes, (posicao.numero_artistas+1) * sizeof(int));
				posicao.posicoes[posicao.numero_artistas] = i+1;
				posicao.numero_artistas++;
			}
		}else{
			posicao.posicoes = (int *) realloc(posicao.posicoes, (posicao.numero_artistas+1) * sizeof(int));
			posicao.posicoes[posicao.numero_artistas] = i+1;
			posicao.numero_artistas++;
		}
	}
	return posicao;
}

artista_t criaStructArtista(dados_t *dados, int numero_linhas, posicao_t posicao, int indice){
	artista_t artista;
	//Alocamos espaço para o nome e o id, baseado nos índices que coletamos na função anterior
	artista.nome_artista = (char *) malloc(strlen(dados[posicao.posicoes[indice]].artist_name) * sizeof(char));
	artista.artista_id = (char *) malloc (strlen(dados[posicao.posicoes[indice]].artist_id) * sizeof(char));

	strcpy(artista.nome_artista, dados[posicao.posicoes[indice-1]].artist_name);
	strcpy(artista.artista_id, dados[posicao.posicoes[indice-1]].artist_id);

	//Essa condição serve para não ignorarmos o primeiro artista
	if (indice == 0)
	{
		artista.quantidade_musicas = posicao.posicoes[indice];
	}else{
		artista.quantidade_musicas = posicao.posicoes[indice] - posicao.posicoes[indice-1];
	}

	if (indice == 0)
	{
		artista.popularidade = calculaPopularidade(dados, 0, posicao.posicoes[indice]);
	}else{
		artista.popularidade = calculaPopularidade(dados, posicao.posicoes[indice-1], posicao.posicoes[indice]);
	}
	
	return artista;	
}


float calculaPopularidade(dados_t *dados, int inicio, int fim){
	float popularidade = 0;
	float somatorio = 0;
	for (int i = inicio; i < fim; i++)
	{
		somatorio = somatorio + dados[i].popularity;
	}
	popularidade = (float)(somatorio / (fim - inicio));

	return popularidade;
}

