typedef struct dados{
	char *track_name;
	int track_id;
	char *album_name;
	int album_id; 
	char *artist_name; 
	int artist_id; 
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

char *readline(FILE *stream);