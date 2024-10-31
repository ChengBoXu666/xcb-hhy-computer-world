#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#include "game.h"
#include "card.h"
#include "show.h"

int roundnumber;    
int playernumber;   
int decknumber;
//Spades < Hearts < Diamonds < Clubs

Card* deckforfetch;
int numberofcards_in_deckforfetch;
Card* deckfordiscard;
int numberofcards_in_deckfordiscard;

void init_beforestart(){
    printf("---- Initial setup ----\n");
    printf("Number of rounds:");
    scanf("%d",&roundnumber);
    printf("Number of decks:");
    scanf("%d",&decknumber);
    printf("Number of players:");  
    scanf("%d",&playernumber);
    printf("\n");
    Init_deck(decknumber);
    Shuffle(numberofcards_in_deckforfetch);
    
}

int main( void ) {
    srand(time(NULL));

    init_beforestart();
    for(int i = 0; i < roundnumber; i++){
        
    }
    free(deckforfetch);
    free(deckfordiscard);
    return 0;
}
