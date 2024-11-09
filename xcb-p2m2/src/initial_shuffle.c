#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

void initial_shuffle(Card *card_fetch, int total)
{
    printf("Shuffling cards...\n");
    for (int i = total - 1; i > 0; i--)
    {
        int temp_suit = card_fetch[i].suit;
        int temp_rank = card_fetch[i].rank;
        int t = rand() % i;
        card_fetch[i].suit = card_fetch[t].suit;
        card_fetch[i].rank = card_fetch[t].rank;
        card_fetch[t].suit = temp_suit;
        card_fetch[t].rank = temp_rank;
    }
}
