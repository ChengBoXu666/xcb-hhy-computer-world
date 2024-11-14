#include "onecard.h"

Player **initial_assignment(Card *card_fetch, Card *card_discard, Player **player, Result result)
{
    int t1 = 0, t2 = 0;
    for (int i = 0; i < result.cards; i++)
    {
        for (int j = 1; j < result.players + 1; j++)
        {
            player[j]->card[i] = malloc(sizeof(Card));
            if (player[j]->card[i] == NULL)
            {
                fprintf(stderr, "Memory allocation failed for player[%d]->card[%d]\n", j, i);
                exit(EXIT_FAILURE);
            }
            player[j]->card[i]->rank = card_fetch[t1].rank;
            player[j]->card[i]->suit = card_fetch[t1].suit;
            card_fetch[t1].rank = 0;
            card_fetch[t1].suit = 0;
            t1++;
        }
    }
    int maxi = 0, maxrank = 0, maxsuit = 0;
    for (int i = 1; i < result.players + 1; i++)
    {
        player[i]->first = malloc(sizeof(Card));
        if (player[i]->first == NULL)
        {
            fprintf(stderr, "Memory allocation failed for player[%d]->first\n", i);
            exit(EXIT_FAILURE);
        }
        player[i]->first->rank = card_fetch[t1].rank;
        player[i]->first->suit = card_fetch[t1].suit;
        card_fetch[t1].rank = 0;
        card_fetch[t1].suit = 0;
        card_discard[t2].rank = player[i]->first->rank;
        card_discard[t2].suit = player[i]->first->suit;
        if ((player[i]->first->rank > maxrank) || ((player[i]->first->rank == maxrank) && (player[i]->first->suit > maxsuit)))
        {
            maxrank = player[i]->first->rank;
            maxsuit = player[i]->first->suit;
            maxi = i;
        }
        t1++;
        t2++;
    }
    player[0]->current1 = t1;
    player[0]->current2 = t2;
    player[0]->score = maxi;
    printf("Dealing cards...\n");
    initial_sort(player, result);
    if (result.demo_mode == 1)
    {
        for (int i = 1; i < result.players + 1; i++)
        {
            printf("Player %d: ",i);
            cards_output(player, i, player[i]->number);
        }
    }
    printf("\n");
    printf("Determining the playing order...\n");
    for (int i = 1; i < result.players + 1; i++)
    {
        printf("Player %d: ", i);
        card_output(player[i]->first->suit, player[i]->first->rank);
        printf("\n");
        free(player[i]->first);
    }
    printf("The game will start with player %d\n", maxi);
    printf("\n");
    return player;
}
