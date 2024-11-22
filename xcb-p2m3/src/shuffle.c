#include "onecard.h"

void shuffle(Card *card, int total, int mode)
{
    printf("Shuffling cards...\n");
    for (int j = 0; j < 7; j++)
    {
        for (int i = total - 1; i > 0; i--)
        {
            int temp_suit = card[i].suit;
            int temp_rank = card[i].rank;
            int t = rand() % i;
            card[i].suit = card[t].suit;
            card[i].rank = card[t].rank;
            card[t].suit = temp_suit;
            card[t].rank = temp_rank;
        }
    }
    if (mode == 1)
    {
        printf("Shuffle result: ");
        for (int i = 0; i < total - 1; i++)
        {
            card_output(card[i].suit, card[i].rank);
        }
        printf("\n");
    }
    printf("\n");
}
