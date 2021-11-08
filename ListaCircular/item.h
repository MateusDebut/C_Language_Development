#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#include <stdio.h>
#include <stdlib.h>

typedef struct item Item;

Item *itemCreate(char *name, char *releaseYear, char *producer);
void itemPrint(Item *item);
void itemDelete(Item *item);
char *itemGetProducer(Item *item);
char *itemGetReleaseYear(Item *item);
char *itemGetName(Item *item);

#endif //ITEM_H_DEFINED