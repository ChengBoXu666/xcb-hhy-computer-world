#include "onecard.h"
int main(int argc, char *argv[])
{
    Result result = inputing(argc, argv);
    if (result.demo_mode == -1)
        return 0;
    srand((unsigned int)time(NULL));
    initial_output(result);
    FILE *file = fopen(result.filename, "w");
    if (file == NULL)
    {
        printf("Error: unable to open file\n");
        return 0;
    }
    int *array = (int *)malloc((size_t)(result.players) * sizeof(int));
    if (array == NULL)  
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < result.players; i++) array[i] = 0;
    for (int k = 0; k < result.rounds; k++)
    {
        printf("Round %d\n", k + 1);
        printf("\n");
        // if (result.demo_mode == 0) sleep(2);
        Player *head = NULL, *tail = NULL;
        for (int i = 0; i < result.players; i++)
        {
            Player *new_player = malloc(sizeof(Player));
            if (!new_player)
            {
                fprintf(stderr, "Memory allocation failed for player\n");
                exit(EXIT_FAILURE);
            }
            new_player->card = malloc((long unsigned int)result.cards * sizeof(Card));
            if (!new_player->card)
            {
                fprintf(stderr, "Memory allocation failed for player->card\n");
                exit(EXIT_FAILURE);
            }
            new_player->first = malloc(sizeof(Card));
            if (new_player->first == NULL)
            {
                fprintf(stderr, "Memory allocation failed for player[%d]->first\n", i);
                exit(EXIT_FAILURE);
            }
            new_player->score = 0;
            new_player->number = result.cards;
            new_player->index = i + 1;
            if (!head)
            {
                head = new_player;
                tail = new_player;
            }
            else
            {
                tail->next = new_player;
                new_player->prev = tail;
                tail = new_player;
            }
        }
        if (head)
            head->prev = tail;
        if (tail)
            tail->next = head;
        Player *player=NULL;
        player = head;
        Card *card_fetch = (Card *)malloc((size_t)result.decks * 52 * sizeof(Card));
        if (card_fetch == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        Card *card_discard = (Card *)malloc((size_t)result.decks * 52 * sizeof(Card));
        if (card_discard == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < result.decks * 52; i++)
        {
            card_fetch[i].suit = i % 52 / 13 + 1;
            card_fetch[i].rank = i % 52 % 13 + 2;
        }
        shuffle(card_fetch, result.decks * 52, result.demo_mode);
        Tran trans = {0, 0, 0};
        trans = initial_assignment(card_fetch, card_discard, head, result, trans);
        for (int i = 0; i < result.players; i++)
        {
            if (player->index == trans.mini + 1)
                break;
            player = player->next;
        }
        play(player, card_fetch, card_discard, result, trans);
        for (int i = 0; i < result.players; i++)
        {
            array[i] += head->score;
            head = head->next;
        }
        printf("---- Stats ----\n");
        printf("Round %d results: \n", k + 1);
        for (int i = 0; i < result.players; i++)
        {
            printf("Player %d's score is %d , total score is %d\n", i + 1, head->score, array[i]);
            head = head->next;
        }
        printf("Round %d ends.\n", k + 1);
        printf("\n");
        if (result.demo_mode == 0)
        {
            sleep(7);
            system("clear");
        }
        free(card_fetch);
        free(card_discard);
        for (int i = 0; i < result.players - 1; i++)
        {
            for (int j = 0; j < player->number; j++)
                free(player->card[j]);
            free(player->card);
            Player *temp=NULL;
            temp = player;
            player = player->next;
            free(temp);
        }
        for (int j = 0; j < player->number; j++)
            free(player->card[j]);
        free(player->card);
        free(player);
    }
    if (result.demo_mode == 0)
        system("clear");
    printf("------Final results--------\n");
    for (int i = 0; i < result.players; i++)
        printf("Player %d's score is %d\n", i + 1, array[i]);
    fclose(file);
    free(array);
    return 0;
}
