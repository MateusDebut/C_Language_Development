#ifndef CARD_H
#define CARD_H

#define NULL_CARD_ERROR -2

typedef struct card Card;

Card *cardCreate(char *suit, int value);
void cardUpdate(Card card, char *suit, int value);
void cardDelete(Card *card);
void cardPrint(Card *card);
int cardGetValue(Card *card);

#endif //CARD_H