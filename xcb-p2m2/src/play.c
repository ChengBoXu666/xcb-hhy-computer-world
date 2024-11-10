#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

Player **play(Player **player, Card *card_fetch, Card *card_discard, Result result)
{
    printf("---- Game start ----\n");
    Table table;
    table.current = malloc(sizeof(Card));
    if (table.current == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    table.player = player[0]->score;
    table.attack = 0;
    table.direction = 1;
    table.index1 = player[0]->current1;
    table.index2 = player[0]->current2;
    for (int i = 1; i < result.players + 1; i++)
        player[i]->number = result.cards;
    table.current->rank = card_fetch[table.index1].rank;
    table.current->suit = card_fetch[table.index1].suit;
    card_discard[table.index2] = card_fetch[table.index1];
    table.index1++;
    table.index2++;
    printf("First card: ");
    switch (table.current->suit)
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
    switch (table.current->rank)
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
    
    while (1+1==2) 
    {
        int num=0;
        printf("Player %d current cards: ",table.player);
        card_output(player,table.player,player[table.player]->number);
        printf("Player %d plays(Input an integar: 0:no card to play/not play, 1:Card1, 2:Card2, 3:Card3, etc.)",table.player);
        scanf("%d",&num);printf("\n");
    }
    return player;
}

