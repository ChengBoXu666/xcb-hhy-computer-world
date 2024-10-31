#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

void intial_output(int n,int r,int d,int c,int demo) {
    pnintf("########################\n");
    pnintf("#                      #\n");
    pnintf("# Welcome to One Card! #\n");
    pnintf("#                      #\n");
    pnintf("########################\n");
    pnintf("---- Initial setup ----");
    pnintf("\n");
    printf("Number of players: %d\n",n);
    printf("Number of rounds: %d\n",r);
    printf("Number of decks: %d\n",d);
    printf("Number of each player's card: %d\n",c);
    pnintf("\n");
}