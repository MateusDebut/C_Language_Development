typedef int elem;
typedef struct lista lista_t;

lista_t *cria();
void liberar(lista_t *l);
void insere(lista_t *l, elem x);
int tamanho(lista_t *l);
void imprimir(lista_t *l);
int esta_na_lista(lista_t *l, elem x);
void remover(lista_t *l, elem x);