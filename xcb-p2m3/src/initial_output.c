#include "onecard.h"

void initial_output(Result result,FILE *file) //output the initial setup information
{
    printf("########################\n");fprintf(file,"########################\n");   
    printf("#                      #\n");fprintf(file,"#                      #\n");    
    printf("# Welcome to One Card! #\n");fprintf(file,"# Welcome to One Card! #\n");    
    printf("#                      #\n");fprintf(file,"#                      #\n");    
    printf("########################\n");fprintf(file,"########################\n");   
    if (result.demo_mode == 0) sleep(1);
    printf("---- Initial setup ----\n");fprintf(file,"---- Initial setup ----\n");
    if (result.demo_mode == 0) sleep(1);
    printf("Number of players: %d\n", result.players);fprintf(file,"Number of players: %d\n", result.players);
    if (result.demo_mode == 0) sleep(1);
    printf("Number of rounds: %d\n", result.rounds);fprintf(file,"Number of rounds: %d\n", result.rounds);
    if (result.demo_mode == 0) sleep(1);
    printf("Number of decks: %d\n", result.decks);fprintf(file,"Number of decks: %d\n", result.decks);
    if (result.demo_mode == 0) sleep(1);
    printf("Number of each player's card: %d\n", result.cards);fprintf(file,"Number of each player's card: %d\n", result.cards);
    if (result.demo_mode == 0) sleep(1);
    if (result.demo_mode == 1)
    {
        printf("Demo mode: ON\n");
        fprintf(file,"Demo mode: ON\n");
    }
    else
    {
        printf("Demo mode: OFF\n");
        fprintf(file,"Demo mode: OFF\n");
    }
    printf("\n");fprintf(file,"\n");    
    if (result.demo_mode == 0) sleep(1);
}
