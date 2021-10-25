#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#include <stdio.h>
#include <stdlib.h>

typedef struct item Item;

Item *itemCreate(char **art);
void itemPrint(Item *item);
void itemDelete(Item *item);
char *itemGetProducer(Item *item);
int itemGetReleaseYear(Item *item);

#endif //ITEM_H_DEFINED