#include "onecard.h"

void sort(Player **player, int i)
{

    for (int j = 0; j < player[i]->number; j++)
    {
        for (int k = j + 1; k < player[i]->number; k++)
        {
            if ((player[i]->card[j]->suit > player[i]->card[k]->suit) || ((player[i]->card[j]->suit == player[i]->card[k]->suit) && (player[i]->card[j]->rank > player[i]->card[k]->rank)))
            {
                int temp_suit = player[i]->card[j]->suit;
                int temp_rank = player[i]->card[j]->rank;
                player[i]->card[j]->suit = player[i]->card[k]->suit;
                player[i]->card[j]->rank = player[i]->card[k]->rank;
                player[i]->card[k]->suit = temp_suit;
                player[i]->card[k]->rank = temp_rank;
            }
        }
    }
}
