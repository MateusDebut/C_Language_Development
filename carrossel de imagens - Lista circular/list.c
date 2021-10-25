#include <string.h>
#include "list.h"

struct node
{
    Item *item;
    Node *next;
    Node *previous;
};

struct list
{
    Node *head;
    Node **items;
    Node *lastNode;
    Node *currentNode;
    int numberOfItems;
};

List *listCreate()
{
    List *list = (List *)malloc(sizeof(List));
    list->numberOfItems = 0;
    list->head = (Node *)malloc(sizeof(Node));
    list->head->previous = NULL;
    list->head->next = NULL;
    list->lastNode = list->head;
    list->currentNode = list->head;
    return list;
}

void listPut(Item *item, List *list)
{
    if (list == NULL || item == NULL)
        return;

    if (list->numberOfItems == 0)
    {
        list->head->next = (Node *)malloc(sizeof(Node));
        list->head->next->item = item;
        list->head->next->previous = NULL;
        list->lastNode = list->head->next;
        list->currentNode = list->head->next;
    }
    else
    {
        list->lastNode->next = (Node *)malloc(sizeof(Node));
        list->lastNode->next->item = item;
        list->lastNode->next->previous = list->lastNode;
        list->lastNode = list->lastNode->next;
    }
    list->lastNode->next = list->head->next;
    list->head->next->previous = list->lastNode;
    list->numberOfItems++;
}
void listRemove(Item *item, List *list)
{
    Node *currentNode = list->head;
    while (currentNode != list->lastNode)
    {
        currentNode = currentNode->next;
        if (currentNode->item == item)
        {
            conectNeighborsNodes(currentNode);
            adjustFirstAndLastNode(currentNode, list);
            itemDelete(currentNode->item);
            free(currentNode);
            list->numberOfItems--;
        }
    }
}

void listPrint(List *list)
{
    Node *currentNode = list->head;
    while (currentNode != list->lastNode)
    {
        currentNode = currentNode->next;
        itemPrint(currentNode->item);
    }
}

void listPrintNextItem(List *list)
{
    itemPrint(list->currentNode->item);
    list->currentNode = list->currentNode->next;
}

void listPrintPreviousItem(List *list)
{
    itemPrint(list->currentNode->item);
    list->currentNode = list->currentNode->previous;
}

void listMoveItemRight(int initialPosition, int finalPosition, List *list)
{
    Node *currentNode = list->head;
    for (int i = 0; i < initialPosition; i++)
    {
        currentNode = currentNode->next;
    }
    conectNeighborsNodes(currentNode);
    adjustFirstAndLastNode(currentNode, list);

    Node *finalPositionNode = currentNode;
    for (int i = 0; i < finalPosition; i++)
    {
        finalPositionNode = finalPositionNode->next;
    }
    currentNode->next = finalPositionNode->next;
    finalPositionNode->next->previous = currentNode;
    finalPositionNode->next = currentNode;
    currentNode->previous = finalPositionNode;
    if (finalPositionNode == list->lastNode)
    {
        list->lastNode = currentNode;
    }
}

void listMoveItemLeft(int initialPosition, int finalPosition, List *list)
{
    Node *currentNode = list->head;
    for (int i = 0; i < initialPosition; i++)
    {
        currentNode = currentNode->next;
    }
    conectNeighborsNodes(currentNode);
    adjustFirstAndLastNode(currentNode, list);
    Node *finalPositionNode = currentNode;
    for (int i = 0; i < finalPosition; i++)
    {
        finalPositionNode = finalPositionNode->previous;
    }
    currentNode->previous = finalPositionNode->previous;
    finalPositionNode->previous->next = currentNode;
    finalPositionNode->previous = currentNode;
    currentNode->next = finalPositionNode;
    if (finalPositionNode == list->head->next)
    {
        list->head->next = currentNode;
    }
}

void findByProducer(List *list, char *producerName)
{
    Node *currentNode = list->head;
    while (currentNode != list->lastNode)
    {
        currentNode = currentNode->next;
        if (strcmp(itemGetProducer(currentNode->item), producerName) == 0)
        {
            itemPrint(currentNode->item);
        }
    }
}

void findByReleaseYear(List *list, char *releaseYear)
{
    Node *currentNode = list->head;
    while (currentNode != list->lastNode)
    {
        currentNode = currentNode->next;
        if (itemGetReleaseYear(currentNode->item) == atoi(releaseYear))
        {
            itemPrint(currentNode->item);
        }
    }
}

void printItemByPosition(int position, List *list)
{
    Node *currentNode = list->head;

    for (int i = 0; i < position && i < list->numberOfItems; i++)
    {
        currentNode = currentNode->next;
    }
    itemPrint(currentNode->item);
}

void conectNeighborsNodes(Node *currentNode)
{
    currentNode->next->previous = currentNode->previous;
    currentNode->previous->next = currentNode->next;
}

void adjustFirstAndLastNode(Node *currentNode, List *list)
{
    if (currentNode == list->lastNode)
    {
        list->lastNode = list->lastNode->previous;
    }
    if (currentNode == list->head->next)
    {
        list->head->next = currentNode->next;
    }
}

void listDelete(List *list)
{
}
