#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>
#include <stdio.h>

typedef struct item Item;

Item *criarItem(int numero);
void printItem(Item *item);
void destruirItem(Item *item);
int saoItensIguais(Item *item1, Item *item2);

#endif //ITEM_H