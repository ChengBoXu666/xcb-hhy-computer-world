#include "card.h"

void Init_deck(int NumberOfDecks){
    deckforfetch = (Card*)malloc(NumberOfDecks*52*sizeof(Card));  
    numberofcards_in_deckforfetch = NumberOfDecks*52;
    for(int i = 0; i < NumberOfDecks*52; i++){
        deckforfetch[i].suit = i%52/13 + 1;     
        deckforfetch[i].rank = i%52%13 + 1;     
    }   
    deckfordiscard = (Card*)malloc(NumberOfDecks*52*sizeof(Card));
    numberofcards_in_deckfordiscard = 0;
}

void Shuffle(int numberofcards){
    printf("Shuffling cards...\n");
    for(int i = numberofcards-1; i > 0; i--){
        int temp_suit = deckforfetch[i].suit;
        int temp_rank = deckforfetch[i].rank;
        int x = rand()%i;
        deckforfetch[i].suit = deckforfetch[x].suit;
        deckforfetch[i].rank = deckforfetch[x].rank;
        deckforfetch[x].suit = temp_suit;
        deckforfetch[x].rank = temp_rank;
    }
}

