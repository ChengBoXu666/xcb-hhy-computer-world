#include "onecard.h"

void initial_output(Result result)
{
    printf("########################\n");
    printf("#                      #\n");
    printf("# Welcome to One Card! #\n");
    printf("#                      #\n");
    printf("########################\n");
    printf("---- Initial setup ----");
    printf("\n");
    printf("Number of players: %d\n", result.players);
    printf("Number of rounds: %d\n", result.rounds);
    printf("Number of decks: %d\n", result.decks);
    printf("Number of each player's card: %d\n", result.cards);
    if (result.demo_mode==1)
        {
        printf("Demo mode: ON\n");
    }
    else
        {
        printf("Demo mode: OFF\n");
    }
    printf("\n");
}
