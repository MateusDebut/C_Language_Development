#define TamFila 100

//typedef *char elem;
typedef struct elem elem_t;
typedef struct fila fila_t;

fila_t *criar();
int isEmpity(fila_t *f);
int isFull(fila_t *f);
int inserir(fila_t *f, char *nome, int idade, int criterio);
int remover(fila_t *f);
void destruir(fila_t *f);
fila_t *ordenar(fila_t *f);