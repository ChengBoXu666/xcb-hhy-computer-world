#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

Player **initial_assignment(Card *card_fetch, Card *card_discard, Player **player, Result result)
{
    int t1 = 0, t2 = 0;
    for (int i = 0; i < result.cards; i++)
    {
        for (int j = 1; j < result.players + 1; j++)
        {
            player[j]->card[i] = malloc(sizeof(Card));
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
    if (result.demo_mode == 1)
    {
        printf("Shuffle result: \n");
        for (int i = 1; i < result.players + 1; i++)
        {
            for (int j = 0; j < result.cards; j++)
            {
                printf("Player %d: ", i);
                switch (player[i]->card[j]->suit)
                {
                case 1:
                    printf("%s", "Spades ");
                    break;
                case 2:
                    printf("%s", "Hearts ");
                    break;
                case 3:
                    printf("%s", "Diamonds ");
                    break;
                case 4:
                    printf("%s", "Clubs ");
                    break;
                }
                switch (player[i]->card[j]->rank)
                {
                case 2:
                    printf("%s", "2 ");
                    break;
                case 3:
                    printf("%s", "3 ");
                    break;
                case 4:
                    printf("%s", "4 ");
                    break;
                case 5:
                    printf("%s", "5 ");
                    break;
                case 6:
                    printf("%s", "6 ");
                    break;
                case 7:
                    printf("%s", "7 ");
                    break;
                case 8:
                    printf("%s", "8 ");
                    break;
                case 9:
                    printf("%s", "9 ");
                    break;
                case 10:
                    printf("%s", "10 ");
                    break;
                case 11:
                    printf("%s", "Jack ");
                    break;
                case 12:
                    printf("%s", "Queen ");
                    break;
                case 13:
                    printf("%s", "King ");
                    break;
                case 14:
                    printf("%s", "Ace ");
                    break;
                }
            }
            printf("\n");
        }
    }
    printf("Determining the playing order...\n");
    for (int i = 1; i < result.players + 1; i++)
    {

        printf("Player %d: ", i);
        switch (player[i]->first->suit)
        {
        case 1:
            printf("%s", "Spades ");
            break;
        case 2:
            printf("%s", "Hearts ");
            break;
        case 3:
            printf("%s", "Diamonds ");
            break;
        case 4:
            printf("%s", "Clubs ");
            break;
        }
        switch (player[i]->first->rank)
        {
        case 2:
            printf("%s", "2\n");
            break;
        case 3:
            printf("%s", "3\n");
            break;
        case 4:
            printf("%s", "4\n");
            break;
        case 5:
            printf("%s", "5\n");
            break;
        case 6:
            printf("%s", "6\n");
            break;
        case 7:
            printf("%s", "7\n");
            break;
        case 8:
            printf("%s", "8\n");
            break;
        case 9:
            printf("%s", "9\n");
            break;
        case 10:
            printf("%s", "10\n");
            break;
        case 11:
            printf("%s", "Jack\n");
            break;
        case 12:
            printf("%s", "Queen\n");
            break;
        case 13:
            printf("%s", "King\n");
            break;
        case 14:
            printf("%s", "Ace\n");
            break;
        }
        free(player[i]->first);
    }
    printf("The game will start with player %d\n", maxi);
    return player;
}
