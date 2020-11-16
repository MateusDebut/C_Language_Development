typedef struct dados{
	char *track_name;
	char *track_id;
	char *album_name;
	char *album_id; 
	char *artist_name; 
	char *artist_id; 
	char *release_date; 
	int length; 
	int popularity; 
	float acousticness;
	float danceability; 
	float energy; 
	char *instrumentalness; 
	float liveness; 
	float loudness; 
	float speechiness; 
	float tempo; 
	int time_signature;
}dados_t;

typedef struct header{
	char *track_name;
	char *track_id;
	char *album_name;
	char *album_id; 
	char *artist_name; 
	char *artist_id; 
	char *release_date; 
	char *length; 
	char *popularity; 
	char *acousticness;
	char *danceability; 
	char *energy; 
	char *instrumentalness; 
	char *liveness; 
	char *loudness; 
	char *speechiness; 
	char *tempo; 
	char *time_signature;
}header_t;

typedef struct artista
{
	char *nome_artista; 
	char *artista_id;
	int quantidade_musicas;
	float popularidade;
	char *link_spotify;
}artista_t;

typedef struct posicao
{
	int numero_artistas;
	int *posicoes;
}posicao_t;

char *readline(FILE *stream);
dados_t criaStructDados(dados_t dados, FILE *fp);
header_t criaStructHeader(header_t header, FILE *fp);
void imprimeDados(dados_t dados);
void mergesort(dados_t *dados, int ini, int fim);
int compararNome (const void *a, const void *b);
int compararPopularidade(const void *x, const void *y);
posicao_t contaArtista(dados_t *dados, int numeroDados, posicao_t posicao);
float calculaPopularidade(dados_t *dados, int inicio, int fim);
artista_t criaStructArtista(dados_t *dados, int numero_linhas, posicao_t posicao, int indice);
