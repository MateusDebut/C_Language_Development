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

char *readline(FILE *stream);
dados_t criaStructDados(dados_t dados, FILE *fp);
header_t criaStructHeader(header_t header, FILE *fp);