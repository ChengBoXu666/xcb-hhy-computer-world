#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

void card_output(Player **player, int index_player, int num_card)
{
    for (int i = 0; i < num_card; i++)
    {
        printf("Card%d: ", i+1);
        switch (player[index_player]->card[i]->suit)
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
        switch (player[index_player]->card[i]->rank)
        {
        case 2:
            printf("%s","2; ");
            break;
        case 3:
            printf("%s", "3; ");
            break;
        case 4:
            printf("%s", "4; ");
            break;
        case 5:
            printf("%s", "5; ");
            break;
        case 6:
            printf("%s", "6; ");
            break;
        case 7:
            printf("%s", "7; ");
            break;
        case 8:
            printf("%s", "8; ");
            break;
        case 9:
            printf("%s", "9; ");
            break;
        case 10:
            printf("%s", "10; ");
            break;
        case 11:
            printf("%s", "Jack; ");
            break;
        case 12:
            printf("%s", "Queen; ");
            break;
        case 13:
            printf("%s", "King; ");
            break;
        case 14:
            printf("%s", "Ace; ");
            break;
        }
        
    }
    printf("\n");
}
