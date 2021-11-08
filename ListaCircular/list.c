#include <string.h>
#include "list.h"
#include "util.h"

struct node
{
    Item *item;
    Node *next;
    Node *previous;
};

struct list
{
    Node *head;
    Node *lastNode;
    int numberOfItems;
};

List *listCreate()
{
    List *list = (List *)malloc(sizeof(List));
    list->numberOfItems = 0;
    list->head = (Node *)malloc(sizeof(Node));
    list->head->previous = NULL;
    list->head->next = NULL;
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
    }
    else
    {
        list->lastNode->next = (Node *) malloc(sizeof(Node));
        list->lastNode->next->item = item;
        list->lastNode->next->previous = list->lastNode;
        list->lastNode = list->lastNode->next;
    }
    list->lastNode->next = list->head->next;
    list->head->next->previous = list->lastNode;
    list->numberOfItems++;
}
void listRemove(Node *node, List *list)
{
    conectNeighborsNodes(node);
    adjustFirstAndLastNode(node, list);
    itemDelete(node->item);
    free(node);
    node = NULL;
    list->numberOfItems--;
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
        if (strcmp(itemGetReleaseYear(currentNode->item), releaseYear) == 0)
        {
            itemPrint(currentNode->item);
        }
    }
}

void printItemByPosition(int position, List *list)
{
    Node *currentNode = list->head;

    for (int i = 0; i <= position; i++)
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
    Node *currentNode = list->head->next;
    Node *nextNode = currentNode->next;
    while (currentNode != list->lastNode)
    {
        itemDelete(currentNode->item);
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(list->head);
    itemDelete(list->lastNode->item);
    free(list->lastNode);
    free(list);    
}

void listDeleteRepeatedItens(List *list)
{
    Node *currentNode = list->head;
    while (currentNode != list->lastNode)
    {
        currentNode = currentNode->next;
        Node *sentinel = currentNode;
        while (sentinel != list->lastNode)
        {
            sentinel = sentinel->next;
            char *currentItemName = itemGetName(currentNode->item);
            char *sentinelItemName = itemGetName(sentinel->item);
            if (strcmp(currentItemName, sentinelItemName) == 0)
            {
                Node *temp = sentinel->previous;
                listRemove(sentinel, list);
                sentinel = temp;
            }
        }
    }
}
