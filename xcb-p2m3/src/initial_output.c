#include "onecard.h"

void initial_output(Result result)
{
    printf("########################\n");
    printf("#                      #\n");
    printf("# Welcome to One Card! #\n");
    printf("#                      #\n");
    printf("########################\n");
    // sleep(1);
    printf("---- Initial setup ----");
    printf("\n");
    // sleep(1);
    printf("Number of players: %d\n", result.players);
    // sleep(1);
    printf("Number of rounds: %d\n", result.rounds);
    // sleep(1);
    printf("Number of decks: %d\n", result.decks);
    // sleep(1);
    printf("Number of each player's card: %d\n", result.cards);
    // sleep(1);
    if (result.demo_mode == 1)
    {
        printf("Demo mode: ON\n");
    }
    else
    {
        printf("Demo mode: OFF\n");
    }
    printf("\n");
    // sleep(1);
}
