//
// Created by mateus on 06/06/22.
//

#ifndef BTREE_ARVOREB_H
#define BTREE_ARVOREB_H
typedef struct pagina Pagina;

typedef struct indice Indice;

Pagina *criaPagina();
Pagina *lePaginaDoArquivo(FILE *filepointer, long RRN);
Pagina *recuperaOuCriaRaiz(FILE *arquivo);
Pagina *recuperaRaiz(FILE *arquivo);
void insereElemento(Indice *indice, Pagina *pagina, FILE *arquivo);
long recuperaCabecalhoDaArvore(FILE *filepointer);
void escreveCabecalhoDaArvore(FILE *filepointer, long RRNdaRaiz);

#endif //BTREE_ARVOREB_H
