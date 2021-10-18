#include "stack.h"
#include "card.h"
#include <stdlib.h>
#include <stdio.h>

struct node
{
    Card *card;
    Node *previous;
};

struct stack
{
    Node *top;
    int numberOfItems;
};

Stack *stackCreate()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->numberOfItems = 0;
    stack->top = NULL;
    return stack;
}

int stackPushCard(Stack *stack, Card *card)
{
    if (stack == NULL)
    {
        printf("Error! Stack doesn't exist...\n");
        return NONEXISTENT_STACK_ERROR;
    }

    if (card == NULL)
    {
        printf("Error! Card atribute is NULL...\n");
        return NULL_CARD_ERROR;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    node->card = card;

    if (stack->top == NULL)
    {
        stack->top = node;
        node->previous = NULL;
        stack->numberOfItems++;
    }
    else
    {
        node->previous = stack->top;
        stack->top = node;
        stack->numberOfItems++;
    }
    return SUCCESS;
}

void stackPrint(Stack *stack)
{
    if (stack != NULL)
    {
        Node *nodeIterator = stack->top;
        while (nodeIterator != NULL)
        {
            cardPrint(nodeIterator->card);
            nodeIterator = nodeIterator->previous;
        }
    }
}

Card *stackPop(Stack *stack){
    if (stack == NULL)
    {
        printf("Error! Stack doesn't exist...\n");
    }

    if(stack->top == NULL)
        return NULL;

    Node *node = stack->top;
    stack->top = stack->top->previous;
    stack->numberOfItems--;
    return node->card;
}

void nodeDelete(Node *node){
    if(node != NULL){
        cardDelete(node->card);

        if(node->previous!= NULL) 
            free(node->previous);
        
        free(node);
        node = NULL;
    }
}

void stackDelete(Stack *stack){
    if(stack != NULL){
        Node *node = stack->top->previous;
        while (stack->top != NULL)
        {
            node = stack->top->previous;
            nodeDelete(stack->top);
            stack->top = node;
        }
    }
}