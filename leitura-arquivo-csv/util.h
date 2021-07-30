#define TAMANHO_NOME_ARQUIVO 128
#define MAX_TAMANHO_CAMPO 128

typedef struct registro registro_t;

struct registro
{
	char *idUsuario;
	char *nomeUsuario;
	int idadeUsuario;
};

char *readline(FILE *stream);
registro_t montaRegistro(char *nomeArquivo, FILE  *filePointer);
char *readlineCSV(int tamanhoCampo, FILE *filePointer);