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
        printf(" ");
        switch(read_card[i].rank){
            case 2:case 3:case 4:case 5:case 6:
            case 7:case 8:case 9:case 10: printf("%d",read_card[i].rank);break;
            case 1: printf("Ace");break;
            case 11: printf("Joker");break;
            case 12: printf("Queen");break;
            case 13: printf("King");break;
        }
        printf("]");
    }
}