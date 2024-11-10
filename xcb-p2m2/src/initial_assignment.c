#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

Player** initial_assignment(Card *card_fetch, Player **player, Result result)
{
    int t = 0;
    for (int i = 1; i < result.players + 1; i++)
        player[i]->card = malloc((long unsigned int)result.cards * sizeof(Card *));
    for (int i = 0; i < result.cards; i++)
    {
        for (int j = 1; j < result.players + 1; j++)
        {
            player[j]->card[i] = malloc(sizeof(Card));
            player[j]->card[i]->rank = card_fetch[t].rank;
            player[j]->card[i]->suit = card_fetch[t].suit;
            t++;
        }
    }

    int maxi = 0, maxrank = 0, maxsuit = 0;
    for (int i = 1; i < result.players + 1; i++)
    {
        player[i]->first = malloc(sizeof(Card));
        player[i]->first->rank = card_fetch[t].rank;
        player[i]->first->suit = card_fetch[t].suit;
        if ((player[i]->first->rank > maxrank) || ((player[i]->first->rank == maxrank) && (player[i]->first->suit > maxsuit)))
        {
            maxrank = player[i]->first->rank;
            maxsuit = player[i]->first->suit;
            maxi = i;
        }
        t++;
        free(player[i]->first);
    }
    player[0]->current = t;
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
        switch (player[0]->first->suit)
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
        switch (player[0]->first->rank)
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
    }
    printf("The game will start with player %d",maxi);
    return player;
}
