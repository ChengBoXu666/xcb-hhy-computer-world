#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include "basic.h"

int main(int argc,char *argv[]) {
    Result result=inputing(argc,argv);
    int n=0,r=0,d=0,c=0,total=0,demo=0;
    n=result.players;
    r=result.rounds;
    d=result.decks;
    c=result.cards;
    demo=result.demo_mode;
    total=n*d;
    
    srand((unsigned int)time(NULL));

    initial_output(n,r,d,c,demo);

    //Player *player=malloc((size_t)n*sizeof(Player));

    Card *card_fetch=(Card*)malloc((size_t)d*52*sizeof(Card));
    if (card_fetch == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    //Card *card_discard=(Card*)malloc((size_t)d*52*sizeof(Card));
    for(int i=0; i<d*52; i++){
        card_fetch[i].suit = i%52/13+1;     
        card_fetch[i].rank = i%52%13+2;     
    }  
    initial_shuffle(card_fetch,total);
    return 0;
}
