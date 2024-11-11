#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

void initial_output(int n, int r, int d, int c, int demo)
{
    printf("########################\n");
    printf("#                      #\n");
    printf("# Welcome to One Card! #\n");
    printf("#                      #\n");
    printf("########################\n");
    printf("---- Initial setup ----");
    printf("\n");
    printf("Number of players: %d\n", n);
    printf("Number of rounds: %d\n", r);
    printf("Number of decks: %d\n", d);
    printf("Number of each player's card: %d\n", c);
    printf("\n");
    (void)demo;
}
