#include "item.h"

struct item
{
    char *name;
    char *releaseYear;
    char *producer;
};

Item *itemCreate(char *name, char *releaseYear, char *producer)
{
    Item *item = (Item *)malloc(sizeof(Item));
    item->name = name;
    item->releaseYear = releaseYear;
    item->producer = producer;
    return item;
}

void itemPrint(Item *item)
{
    printf("%s\n", item->name);
}

void itemDelete(Item *item)
{
    if (item == NULL)
        return;
    free(item);
}

char *itemGetProducer(Item *item)
{
    return item->producer;
}

char *itemGetReleaseYear(Item *item)
{
    return item->releaseYear;
}

char *itemGetName(Item *item)
{
    return item->name;
}