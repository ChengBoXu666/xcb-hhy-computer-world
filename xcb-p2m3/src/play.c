#include "onecard.h"
Player **play(Player **player, Card *card_fetch, Card *card_discard, Result result)
{
    printf("---- Game start ----\n");
    // sleep(2);
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
    while (1)
    {
        table.current->rank = card_fetch[table.index1].rank;
        table.current->suit = card_fetch[table.index1].suit;
        card_discard[table.index2] = card_fetch[table.index1];
        table.index1++;
        table.index2++;
        if (judge(table.current->rank) == 1)
            break;
    }
    printf("First card: ");
    card_output(table.current->suit, table.current->rank);
    printf("\n\n");
    int num = 0, flag = 0, judge = 0;
    while (1)
    {
        flag = 1;
        printf("Player %d's turn\n", table.player);
        printf("\n");
        printf("Player %d current cards: ", table.player);
        cards_output(player, table.player, player[table.player]->number);
        printf("\n");
        printf("Please input your choice(Input an integar: 0:no card to play/not play, 1:Card1, 2:Card2, 3:Card3, etc.): ");
        scanf("%d", &num);
        printf("\n");

        if (num == 0)
        {
            if (table.attack == 0)
                table.attack = 1;
        }
        else if ((num > player[table.player]->number) || (((player[table.player]->card[num - 1]->rank != table.current->rank) && (player[table.player]->card[num - 1]->suit != table.current->suit)) || ((table.attack != 0) && (player[table.player]->card[num - 1]->rank != 2 && player[table.player]->card[num - 1]->rank != 3 && player[table.player]->card[num - 1]->rank != 7 && player[table.player]->card[num - 1]->rank != 11 && player[table.player]->card[num - 1]->rank != 12 && judge == 1))))
        {
            printf("Invalid card! You are regarded as giving up this turn!\n\n");
            if (table.attack == 0)
                table.attack = 1;
            flag = 0;
        }
        else
        {
            player[table.player]->number--;
            table.current->rank = player[table.player]->card[num - 1]->rank;
            table.current->suit = player[table.player]->card[num - 1]->suit;
            for (int i = num - 1; i < player[table.player]->number; i++)
                player[table.player]->card[i] = player[table.player]->card[i + 1];

            card_discard[table.index2].rank = player[table.player]->card[num - 1]->rank;
            card_discard[table.index2].suit = player[table.player]->card[num - 1]->suit;
            table.index2++;
            if (table.current->rank == 2 || table.current->rank == 3)
            {
                judge = 1;
                table.attack += table.current->rank;
            }

            if (table.current->rank == 7)
                table.attack = 0;
            if (table.current->rank == 11)
            {
                judge = 1;
                table.direction = 2 * table.direction;
            }
            if (table.current->rank == 12)
            {
                table.direction = (-1) * table.direction;
                judge = 1;
            }
            printf("Player %d plays card: ", table.player);
            card_output(table.current->suit, table.current->rank);
            printf("\n");
        }
        if (flag == 0 || num == 0)
            player[table.player]->number = table.attack + player[table.player]->number;
        if ((player[table.player]->number != 0) && ((flag == 0 || num == 0)))
        {
            player[table.player]->card = realloc(player[table.player]->card, sizeof(Card) * (long unsigned int)player[table.player]->number);
            if (player[table.player] == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            for (int i = player[table.player]->number - table.attack; i < player[table.player]->number; i++)
            {
                player[table.player]->card[i] = malloc(sizeof(Card));
                if (player[table.player]->card[i] == NULL)
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        if ((table.attack != 0) && ((flag == 0 || num == 0)))
        {
            judge = 0;
            printf("Player %d draws %d cards: ", table.player, table.attack);
            for (int i = 0; i < table.attack; i++)
            {
                player[table.player]->card[player[table.player]->number - table.attack + i]->rank = card_fetch[table.index1].rank;
                player[table.player]->card[player[table.player]->number - table.attack + i]->suit = card_fetch[table.index1].suit;
                table.index1++;
                card_output(player[table.player]->card[player[table.player]->number - table.attack + i]->suit, player[table.player]->card[player[table.player]->number - table.attack + i]->rank);
                if (table.index1 == 52 * result.decks)
                {
                    printf("Stock pile exhausted. Shuffling the discard pile and restore the stock pile\n\n");
                    shuffle(card_discard, table.index2 - 1, 0);
                    table.index1 = 0;
                    for (int j = 0; j < table.index2 - 1; j++)
                    {
                        card_fetch[j] = card_discard[j];
                        card_discard[j].rank = 0;
                        card_discard[j].suit = 0;
                    }
                    table.index2 = 0;
                }
            }
            table.attack = 0;
            printf("\n");
        }
        sleep(4);
        if (player[table.player]->number == 0)
        {
            printf("Player %d wins!\n", table.player);
            sleep(4);
            if (result.demo_mode == 0)
                system("clear");
            break;
        }
        sort(player, table.player);
        if (result.demo_mode == 0)
            system("clear");
        printf("Current card on table: ");
        card_output(table.current->suit, table.current->rank);
        printf("\n\n");
        if ((table.current->rank == 2 || table.current->rank == 3 || table.current->rank == 11 || table.current->rank == 12) && (table.attack > 1))
            printf("Total attact number is %d\n\n", table.attack);
        table.player = (table.player + result.players + table.direction - 1) % result.players + 1;
        if (table.direction == -2)
            table.direction = -1;
        if (table.direction == 2)
            table.direction = 1;
        if (table.current->rank != 2 && table.current->rank != 3)
            table.attack = 0;
    }
    for (int i = 1; i < result.players + 1; i++)
        player[i]->score = (-1) * player[i]->number;
    free(table.current);
    return player;
}





