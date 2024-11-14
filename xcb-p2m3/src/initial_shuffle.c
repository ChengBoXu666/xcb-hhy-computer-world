#include "onecard.h"

void initial_shuffle(Card *card_fetch, Result result)
{
    printf("Shuffling cards...\n");
    for (int i = result.decks*52 - 1; i > 0; i--)
    {
        int temp_suit = card_fetch[i].suit;
        int temp_rank = card_fetch[i].rank;
        int t = rand() % i;
        card_fetch[i].suit = card_fetch[t].suit;
        card_fetch[i].rank = card_fetch[t].rank;
        card_fetch[t].suit = temp_suit;
        card_fetch[t].rank = temp_rank;
    }
    for (int i = result.decks*52 - 1; i > 0; i--)
    {
        int temp_suit = card_fetch[i].suit;
        int temp_rank = card_fetch[i].rank;
        int t = rand() % i;
        card_fetch[i].suit = card_fetch[t].suit;
        card_fetch[i].rank = card_fetch[t].rank;
        card_fetch[t].suit = temp_suit;
        card_fetch[t].rank = temp_rank;
    }
    if (result.demo_mode == 1)
    {
        printf("Shuffle result: \n");
        for (int i = 0; i < result.decks*52 - 1; i++)
        {
            card_output(card_fetch[i].suit, card_fetch[i].rank);
        }
    }
    printf("\n");
    printf("\n");
}


