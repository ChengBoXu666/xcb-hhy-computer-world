#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include "basic.h"

int main(int argc,char *argv[]) {
    Result result=inputing(argc,argv);
    int n,r,d,c,total,demo;
    n=result.players;
    r=result.rounds;
    d=result.decks;
    c=result.cards;
    demo=result.demo_mode;
    total=n*d;
    
    srand((unsigned int)time(NULL));

    void initial_output(n,r,d,c,demo);

    Player *player=malloc(n*sizeof(Player));

    Card *card_fetch=(Card*)malloc(d*52*sizeof(Card));
    Card *card_discard=(Card*)malloc(d*52*sizeof(Card));
    for(int i=0; i<d*52; i++){
        card_fetch[i].suit = i%52/13+1;     
        card_fetch[i].rank = i%52%13+1;     
    }  
    void intial_shuffle(card_fetch,total);
    return 0;
}