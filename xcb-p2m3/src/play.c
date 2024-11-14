#include "onecard.h"

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
    table.current->rank = card_fetch[table.index1].rank;
    table.current->suit = card_fetch[table.index1].suit;
    card_discard[table.index2] = card_fetch[table.index1];
    table.index1++;
    table.index2++;
    printf("First card: ");
    card_output(table.current->suit, table.current->rank);
    while (1)
    {
        int num = 0;
        printf("Player %d current cards: ", table.player);
        cards_output(player, table.player, player[table.player]->number);
        printf("Player %d plays(Input an integar: 0:no card to play/not play, 1:Card1, 2:Card2, 3:Card3, etc.): ", table.player);
        scanf("%d", &num);
        printf("\n");
        break;
    }
    (void)result;
    free(table.current);
    return player;
}

