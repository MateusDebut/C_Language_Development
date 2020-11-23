typedef struct no no_t;
typedef int elem;
typedef struct arvore{
	no_t *raiz;
}arvore_t;

struct no{
	elem info;
	no_t *esq;
	no_t *dir;
	elem pai;
};

arvore_t *criaArvore();
int esta_vazia(arvore_t *a);
void finalizar(no_t *raiz);
void imprimir (no_t *raiz, int indice);
int altura(no_t *raiz);
no_t *busca(no_t *raiz, elem x);
no_t *busca_pai(no_t *raiz, elem x);
int inserir_esq(arvore_t *a, elem x, elem pai);
int inserir_dir(arvore_t *a, elem x, elem pai);
int remover(arvore_t *a, elem x);
int verifica_grau(no_t *raiz);
char *verifica_tipo(no_t *raiz);