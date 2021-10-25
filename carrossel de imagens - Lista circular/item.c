#include "item.h"
#include "util.h"

struct item
{
    char **art;
};

Item *itemCreate(char **art)
{
    Item *item = (Item *)malloc(sizeof(Item));
    item->art = art;
    return item;
}

void itemPrint(Item *item)
{
    int i = 0;
    while (myStrcmp(item->art[i], "-42") != 0)
    {
        printf("%s\n", item->art[i]);
        i++;
    }
    printf("\n\n\n");
}

void itemDelete(Item *item)
{
    if (item == NULL)
        return;
    free(item);
}

char *itemGetProducer(Item *item)
{
    return  NULL;
}

int itemGetReleaseYear(Item *item)
{
    return 0;
}