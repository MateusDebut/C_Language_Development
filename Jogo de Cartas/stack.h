#ifndef STACK_H
#define STACK_H

#define NONEXISTENT_STACK_ERROR -1

#define SUCCESS 1

#include "card.h"
typedef struct node Node;
typedef struct stack Stack;

Stack *stackCreate();
int stackPushCard(Stack *stack, Card *card);
void stackPrint(Stack *stack);
Card *stackPop(Stack *stack);
void nodeDelete(Node *node);
void stackDelete(Stack *stack);

#endif //STACK_H