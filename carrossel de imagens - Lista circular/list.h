#ifndef LIST_H_DEFINED
#define LIST_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include "item.h"

typedef struct list List;
typedef struct node Node;

List *listCreate();
void listPut(Item *item, List *list);
void listRemove(Item *item, List *list);
void listPrint(List *list);
void listDelete(List *list);
void adjustFirstAndLastNode(Node *currentNode, List *list);
void conectNeighborsNodes(Node *currentNode);
void listMoveItemRight(int initialPosition, int finalPosition, List *list);
void listMoveItemLeft(int initialPosition, int finalPosition, List *list);
void printItemByPosition(int position, List *list);
void listPrintPreviousItem(List *list);
void listPrintNextItem(List *list);

#endif //LIST_H_DEFINED