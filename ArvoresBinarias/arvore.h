typedef int elem;
typedef struct no no_t;
typedef struct arvore{
	no_t *raiz;
}arvore_t;

arvore_t *criaArvore();
int esta_vazia(arvore_t *a);
void finalizar(no_t *raiz);
void imprimir (no_t *raiz);
int altura(no_t *raiz);
no_t *busca(no_t *raiz, elem x);
no_t *busca_pai(no_t *raiz, elem x);
int inserir_esq(arvore_t *a, elem x, elem pai);
int inserir_dir(arvore_t *a, elem x, elem pai);
int remover(arvore_t *a, elem x);