#include "show.h"

void Show_card(Card* read_card, int numberofcards){
    for(int i = 0; i < numberofcards; i++){
        printf("[");
        switch(read_card[i].suit){
            case 1: printf("Spades");break;
            case 2: printf("Hearts");break;
            case 3: printf("Diamonds");break;
            default: printf("Clubs");break;
        }
        printf(" %d]",read_card[i].rank);
    }
}