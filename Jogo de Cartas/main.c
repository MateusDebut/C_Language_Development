#include <stdio.h>
#include "util.h"
#include "stack.h"


int main(int argc, char const *argv[])
{
    Card **cards = (Card **) malloc(52 * sizeof(Card *));
    char *name;
    int value;
    int index = 0;

    do{
        name = readline(stdin);
        if(name == NULL)break;
        value = atoiReadline(stdin);
        cards[index] = cardCreate(name, value);
        index++;

    }while (True);

    Stack *stack = stackCreate();
    
    int newIndex = 0;
    while(newIndex < index){
        stackPushCard(stack, cards[newIndex]);
        newIndex++;
    }
        
    gameLogic(stack);
    
    return 0;
}