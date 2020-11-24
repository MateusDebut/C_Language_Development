typedef struct skiplist skiplist_t;
typedef struct no no_t;

skiplist_t *criar(int nivelMax, float fracao);
no_t *novoNo(int chave, int nivel);
void destruir(skiplist_t *skiplist);
int buscar(skiplist_t *skiplist, int chave);
int inserir(skiplist_t *skiplist, int chave);
int sorteiaNivel(skiplist_t *skiplist);
int remover(skiplist_t *skiplist, int chave);