//
// Created by mateus on 06/06/22.
//

#ifndef BTREE_ARVOREB_H
#define BTREE_ARVOREB_H
typedef struct pagina Pagina;
typedef struct indice Indice;
typedef struct chavePromovida ChavePromovida;

Pagina *criaPagina();
Pagina *lePaginaDoArquivo(FILE *filepointer, long RRN);
Pagina *recuperaOuCriaRaiz(FILE *arquivo);
Pagina *recuperaRaiz(FILE *arquivo);
void insereElemento(Indice *indice, Pagina *pagina, FILE *arquivo);
long recuperaCabecalhoDaArvore(FILE *filepointer);
Pagina *procuraPosicaoNaPaginaEInsere(Pagina *pagina, ChavePromovida *novaChave);
Pagina *criaNoComChavePromovida(ChavePromovida *chavePromovida,long RRN, FILE *filepointer);
ChavePromovida *split(Pagina *pagina, FILE *filepointer, ChavePromovida *novaChave);
Pagina *transpoeDadosParaNovaPagina(Pagina *origem, Pagina *destino, int inicio, int fim);
Pagina *retrocedeIndices(Pagina *pagina);
void setarNoComoRaiz(Pagina *pagina, long RRN, FILE *filepointer);
void escreveCabecalhoDaArvore(FILE *filepointer, long RRNdaRaiz);
long buscaNaArvore(Pagina *pagina, int chave, FILE *filepointer);
Indice buscaBinaria(Indice *indices, int chaveBuscada, int inicio, int fim);
long localizaRRNProximaPagina(Pagina *pagina, int chave);

#endif //BTREE_ARVOREB_H
