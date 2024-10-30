#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include "basic.h"

int main() {
    srand((unsigned int)time(NULL));
    int r,d,n,c;
    printf("Number of players: ");scanf("%d",n); 
    printf("Number of rounds: ");scanf("%d",r);
    printf("Number of decks: ");scanf("%d",d);
    printf("Number of each player's card");scanf("%d",c);
    Player player[n];
    assign(n,player);
    return 0;
}