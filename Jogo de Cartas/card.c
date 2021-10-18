#include "card.h"
#include <stdlib.h>
#include <stdio.h>

struct card
{
    char *suit;
    int value;
};

Card *cardCreate(char * suit, int value){
    Card *card = (Card *) malloc(sizeof(Card));
    card->suit = suit;
    card->value = value;
    return card;
}

void cardUpdate(Card card, char * suit, int value){
    card.suit = suit;
    card.value = value;
}

void cardDelete(Card *card){
    if(card != NULL){
        if(card->suit != NULL)
            free(card->suit);

        free(card);
    }
    
}

void cardPrint(Card *card){
    if(card != NULL)
        printf("%d de %s\n", card->value, card->suit);
}

int cardGetValue(Card *card){
    return card->value;
}

Card * setCardValue(Card *card, int value){
    card->value = value;
    return card;
}