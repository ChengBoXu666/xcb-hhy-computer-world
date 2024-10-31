#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int suit;   
    int rank;   
}Card;

extern Card* deckforfetch;
extern Card* deckfordiscard;
extern int numberofcards_in_deckforfetch;
extern int numberofcards_in_deckfordiscard;

void Init_deck(int NumberOfDecks);
void Shuffle(int numberofcards);

#endif 