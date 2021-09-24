#ifndef CATALOGO_H
#define CATALOGO_H

#include "jogo.h"

typedef struct catalogo Catalogo;

Catalogo *criarCatalogo();
void inserirJogoNoCatalogo(Catalogo *catalogo, Jogo *jogo);
void inserirListaDeJogosNoCatalogo(Catalogo *catalogo, Jogo **jogos);
void desalocarCatalogo(Catalogo *catalogo);
void imprimirCatalogo(Catalogo *catalogo);
void buscaPorAno(Catalogo *catalogo, char *ano);
void buscaPorProdutora(Catalogo *catalogo, char *produtora);

#endif