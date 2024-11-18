#include "onecard.h"
void play(Player *player, Card *card_fetch, Card *card_discard, Result result,Tran trans)
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
    table.attack = 0;
    table.direction = 1;
    table.index1 = trans.t1;
    table.index2 = trans.t2;
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
        printf("Player %d's turn\n", player->index);
        printf("\n");
        printf("Player %d current cards: ", player->index);
        cards_output(player,player->number);
        printf("\n");
        printf("Please input your choice(Input an integar: 0:no card to play/not play, 1:Card1, 2:Card2, 3:Card3, etc.): ");
        scanf("%d", &num);
        printf("\n");
        if (num == 0)
        {
            if (table.attack == 0)
                table.attack = 1;
        }
        else if ((num > player->number) || (((player->card[num - 1]->rank != table.current->rank) && (player->card[num - 1]->suit != table.current->suit)) || ((table.attack != 0) && (player->card[num - 1]->rank != 2 && player->card[num - 1]->rank != 3 && player->card[num - 1]->rank != 7 && player->card[num - 1]->rank != 11 && player->card[num - 1]->rank != 12 && judge == 1))))
        {
            printf("Invalid card! You are regarded as giving up this turn!\n\n");
            if (table.attack == 0)
                table.attack = 1;
            flag = 0;
        }
        else
        {
            player->number--;
            table.current->rank = player->card[num - 1]->rank;
            table.current->suit = player->card[num - 1]->suit;
            for (int i = num - 1; i < player->number; i++)
                player->card[i] = player->card[i + 1];

            card_discard[table.index2].rank = player->card[num - 1]->rank;
            card_discard[table.index2].suit = player->card[num - 1]->suit;
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
            printf("Player %d plays card: ", player->index);
            card_output(table.current->suit, table.current->rank);
            printf("\n");
        }
        if (flag == 0 || num == 0)
            player->number = table.attack + player->number;
        if ((player->number != 0) && ((flag == 0 || num == 0)))
        {
            player->card = realloc(player->card, sizeof(Card) * (long unsigned int)player->number);
            if (player->card == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            for (int i = player->number - table.attack; i < player->number; i++)
            {
                player->card[i] = malloc(sizeof(Card));
                if (player->card[i] == NULL)
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        if ((table.attack != 0) && ((flag == 0 || num == 0)))
        {
            judge = 0;
            printf("Player %d draws %d cards: ", player->index, table.attack);
            for (int i = 0; i < table.attack; i++)
            {
                player->card[player->number - table.attack + i]->rank = card_fetch[table.index1].rank;
                player->card[player->number - table.attack + i]->suit = card_fetch[table.index1].suit;
                table.index1++;
                card_output(player->card[player->number - table.attack + i]->suit, player->card[player->number - table.attack + i]->rank);
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
        if (player->number == 0)
        {
            printf("Player %d wins!\n", player->index);
            sleep(4);
            if (result.demo_mode == 0)
                system("clear");
            break;
        }
        sort(player);
        if (result.demo_mode == 0)
            system("clear");
        printf("Current card on table: ");
        card_output(table.current->suit, table.current->rank);
        printf("\n\n");
        if ((table.current->rank == 2 || table.current->rank == 3 || table.current->rank == 11 || table.current->rank == 12) && (table.attack > 1))
            printf("Total attact number is %d\n\n", table.attack);
        if (table.direction == -2)
        {
            player=player->prev->prev;
            table.direction = -1;
        }
        else if (table.direction == 2)
        {
            player=player->next->next;
            table.direction = 1;
        }
        else if (table.direction == -1) 
            player=player->prev;
        else 
            player=player->next; 
        if (table.current->rank != 2 && table.current->rank != 3)
            table.attack = 0;
    }
    for (int i = 0; i < result.players; i++)
        player->score = (-1) * player->number;
    free(table.current);
}





