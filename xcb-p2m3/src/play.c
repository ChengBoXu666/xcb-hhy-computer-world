#include "onecard.h"
void play(Player *player, Card *card_fetch, Card *card_discard, Result result, Tran trans,FILE *file) // the main logical function of the game
{
    printf("---- Game start ----\n");fprintf(file,"---- Game start ----\n");
    if (result.demo_mode == 0) sleep(2);
    Table table;
    table = initial_table(card_fetch, card_discard, trans, result,file);
    int currentjudge = 0;
    int flag = 1, num = 0;
    while (1)
    {
        printf("Player %d's turn\n", player->index);fprintf(file,"Player %d's turn\n", player->index);
        printf("\n");fprintf(file,"\n");
        if (result.demo_mode == 0)
            sleep(1);
        printf("Player %d current cards: ", player->index);fprintf(file,"Player %d current cards: ", player->index);
        cards_output(player, player->number,file);
        printf("\n");fprintf(file,"\n");
        if (result.demo_mode == 0)  // an extra judgement for the demo mode
        {
            sleep(1);
            printf("Please input your choice(Input an integar: 0:no card to play/not play, 1:Card1, 2:Card2, 3:Card3, etc.): ");fprintf(file,"Please input your choice(Input an integar: 0:no card to play/not play, 1:Card1, 2:Card2, 3:Card3, etc.): ");
            scanf("%d", &num);fprintf(file,"%d", num);
            printf("\n");fprintf(file,"\n");
        }
        else
        {
            for (int i = 1; i < player->number + 1; i++)
                if (!(((player->card[i - 1]->rank != table.current->rank) && (player->card[i - 1]->suit != table.current->suit)) || ((table.attack != 0) && (player->card[i - 1]->rank != 2 && player->card[i - 1]->rank != 3 && player->card[i - 1]->rank != 7 && player->card[i - 1]->rank != 11 && player->card[i - 1]->rank != 12 && currentjudge == 1))))
                {
                    num = i;
                    break;
                }
            if (num == 0)
            {
                printf("Player %d has no valid card to play\n\n", player->index);
                fprintf(file,"Player %d has no valid card to play\n\n", player->index);
            }
        }
        if (num == 0) // the player give up to play a card
        {
            if (table.attack == 0)
                table.attack = 1;
        }
        else if ((num > player->number) || (((player->card[num - 1]->rank != table.current->rank) && (player->card[num - 1]->suit != table.current->suit)) || ((table.attack != 0) && (player->card[num - 1]->rank != 2 && player->card[num - 1]->rank != 3 && player->card[num - 1]->rank != 7 && player->card[num - 1]->rank != 11 && player->card[num - 1]->rank != 12 && currentjudge == 1))))
        { // the player choose an invalid card
            printf("Invalid card! You are regarded as giving up this turn!\n\n");fprintf(file,"Invalid card! You are regarded as giving up this turn!\n\n");
            if (table.attack == 0)
                table.attack = 1;
            flag = 0;
        }
        else
        {
            player->number--;  // the number of cards decrease by 1
            table.current->rank = player->card[num - 1]->rank; //change the current card to the card chosen by the player
            table.current->suit = player->card[num - 1]->suit;
            for (int i = num - 1; i < player->number; i++)  // swap
                player->card[i] = player->card[i + 1];

            card_discard[table.index2].rank = player->card[num - 1]->rank; // put the card chosen by the player into the discard pile
            card_discard[table.index2].suit = player->card[num - 1]->suit;
            table.index2++;
            if (table.current->rank == 2 || table.current->rank == 3) //judge the attack number
            {
                currentjudge = 1;
                table.attack += table.current->rank;
            }
            if (table.current->rank == 7)
                table.attack = 0;
            if (table.current->rank == 11)
            {
                currentjudge = 1;
                table.direction = 2 * table.direction;
            }
            if (table.current->rank == 12)
            {
                table.direction = (-1) * table.direction;
                currentjudge = 1;
            }
            printf("Player %d plays card: ", player->index);fprintf(file,"Player %d plays card: ", player->index);
            card_output(table.current->suit, table.current->rank,file);
            printf("\n\n");fprintf(file,"\n\n");
            if (result.demo_mode == 0)
                sleep(1);
        }
        if (flag == 0 || num == 0)
            player->number = table.attack + player->number;
        if ((player->number != 0) && ((flag == 0 || num == 0)))
        {
            player->card = realloc(player->card, sizeof(Card) * (long unsigned int)player->number); // realloc to fit the change
            if (player->card == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                fprintf(file,"Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            for (int i = player->number - table.attack; i < player->number; i++)
            {
                player->card[i] = malloc(sizeof(Card));
                if (player->card[i] == NULL)
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    fprintf(file,"Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        if ((table.attack != 0) && ((flag == 0 || num == 0))) // fetch the cards from the stock pile
        {
            currentjudge = 0;
            printf("Player %d draws %d cards: ", player->index, table.attack);fprintf(file,"Player %d draws %d cards: ", player->index, table.attack);
            for (int i = 0; i < table.attack; i++)
            {
                player->card[player->number - table.attack + i]->rank = card_fetch[table.index1].rank;
                player->card[player->number - table.attack + i]->suit = card_fetch[table.index1].suit;
                table.index1++;
                card_output(player->card[player->number - table.attack + i]->suit, player->card[player->number - table.attack + i]->rank,file);
                if (table.index1 == 52 * result.decks)
                {
                    printf("\n\nStock pile exhausted. Shuffling the discard pile and restore the stock pile\n\n");fprintf(file,"\n\nStock pile exhausted. Shuffling the discard pile and restore the stock pile\n\n");
                    shuffle(card_discard, table.index2, 2 ,file);
                    table.index1 = 0;
                    for (int j = 0; j < table.index2; j++)
                    {
                        card_fetch[j] = card_discard[j];
                        card_discard[j].rank = 0;
                        card_discard[j].suit = 0;
                    }
                    table.index2 = 0;
                }
            }
            table.attack = 0;
            printf("\n\n");fprintf(file,"\n\n");
        }
        if (result.demo_mode == 0)
            sleep(4);
        if (player->number == 0) // judge the round winner
        {
            if (result.demo_mode == 0)
                sleep(2);
            printf("Player %d wins!\n\n", player->index);fprintf(file,"Player %d wins!\n\n", player->index);
            if (result.demo_mode == 0)
            {
                system("clear");
                sleep(4);
            }
            break;
        }
        sort(player);
        if (result.demo_mode == 0)
            system("clear");
        printf("Current card on table: ");fprintf(file,"Current card on table: ");
        card_output(table.current->suit, table.current->rank,file);
        printf("\n\n");fprintf(file,"\n\n");
        if ((table.current->rank == 2 || table.current->rank == 3 || table.current->rank == 11 || table.current->rank == 12) && (table.attack > 1))
        {
            printf("Total attact number is %d\n\n", table.attack);
            fprintf(file,"Total attact number is %d\n\n", table.attack);
        }
        if (table.direction == -2) // juedge the next player
        {
            player = player->prev->prev;
            table.direction = -1;
        }
        else if (table.direction == 2)
        {
            player = player->next->next;
            table.direction = 1;
        }
        else if (table.direction == -1)
            player = player->prev;
        else
            player = player->next;
        if (table.current->rank != 2 && table.current->rank != 3)
            table.attack = 0;
        flag = 1;
        num = 0;
    }
    for (int i = 0; i < result.players; i++) // calculate the round score of each player
    {
        player->score = (-1) * player->number;
        player = player->next;
    }
    free(table.current);
}
