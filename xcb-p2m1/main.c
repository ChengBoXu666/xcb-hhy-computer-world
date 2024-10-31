#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include "basic.h"

int main(int argc,char *argv[]) {
    Result result=initial(argc,argv);
    int n,r,d,c;
    n=result.players;
    r=result.rounds;
    d=result.decks;
    c=result.cards;
    srand((unsigned int)time(NULL));
    printf("Number of players: ");
    printf("Number of rounds: ");
    printf("Number of decks: ");
    printf("Number of each player's card");
    Player *player=malloc(sizeof(Player));
    Card *card_fetch[];

    return 0;
}