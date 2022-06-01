#ifndef LISTA_H
#define LISTA_H

#include "item.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node Node;
typedef struct lista Lista;

Lista *criarLista();
int getNumeroItens(Lista *lista);
static int ehListaNula(Lista *lista);
static int ehItemNulo(Item *item);
void incluirItemNaLista(Item *item, Lista *lista);
void imprimirLista(Lista *lista);
void removerItemDalista(Item *item, Lista *lista);

#endif //LISTA_H