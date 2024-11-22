#include "onecard.h"

void initial_output(Result result)
{
    printf("########################\n");
    printf("#                      #\n");
    printf("# Welcome to One Card! #\n");
    printf("#                      #\n");
    printf("########################\n");
    // if (result.demo_mode == 0) sleep(1);
    printf("---- Initial setup ----");
    printf("\n");
    // if (result.demo_mode == 0) sleep(1);
    printf("Number of players: %d\n", result.players);
    // if (result.demo_mode == 0) sleep(1);
    printf("Number of rounds: %d\n", result.rounds);
    // if (result.demo_mode == 0) sleep(1);
    printf("Number of decks: %d\n", result.decks);
    // if (result.demo_mode == 0) sleep(1);
    printf("Number of each player's card: %d\n", result.cards);
    // if (result.demo_mode == 0) sleep(1);
    if (result.demo_mode == 1)
    {
        printf("Demo mode: ON\n");
    }
    else
    {
        printf("Demo mode: OFF\n");
    }
    printf("\n");
    // if (result.demo_mode == 0) sleep(1);
}
