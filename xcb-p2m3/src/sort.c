#include "onecard.h"

void sort(Player *player)// sort the cards in the order given in p2 document
{

    for (int j = 0; j < player->number; j++)
    {
        for (int k = j + 1; k < player->number; k++)
        {
            if ((player->card[j]->suit > player->card[k]->suit) || ((player->card[j]->suit == player->card[k]->suit) && (player->card[j]->rank > player->card[k]->rank)))
            {
                int temp_suit = player->card[j]->suit;
                int temp_rank = player->card[j]->rank;
                player->card[j]->suit = player->card[k]->suit;
                player->card[j]->rank = player->card[k]->rank;
                player->card[k]->suit = temp_suit;
                player->card[k]->rank = temp_rank;
            }
        }
    }
}
