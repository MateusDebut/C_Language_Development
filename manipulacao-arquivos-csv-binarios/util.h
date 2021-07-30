#define TAMANHO_NOME_ARQUIVO 128
#define MAX_TAMANHO_CAMPO 128

typedef struct registro registro_t;

struct registro
{
	int idUsuario;
	char nomeUsuario[50];
	int idadeUsuario;
};

char *readline(FILE *stream);
registro_t montaRegistro(char *nomeArquivo, FILE  *filePointer);