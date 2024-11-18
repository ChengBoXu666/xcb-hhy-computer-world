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
    int *array = (int *)malloc((size_t)(result.players + 1) * sizeof(int));

    for (int k = 0; k < result.rounds; k++)
    {
        printf("Round %d\n", k + 1);
        printf("\n");
        sleep(2);
        Player **player = malloc((size_t)(result.players + 1) * sizeof(Player *));
        if (player == NULL)
        {
            fprintf(stderr, "Memory allocation failed for player\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < result.players + 1; i++)
        {
            player[i] = malloc(sizeof(Player));
            if (player[i] == NULL)
            {
                fprintf(stderr, "Memory allocation failed for player[%d]\n", i);
                exit(EXIT_FAILURE);
            }
        }
        for (int i = 0; i < result.players + 1; i++)
        {
            player[i]->card = malloc((long unsigned int)result.cards * sizeof(Card));
            if (player[i]->card == NULL)
            {
                fprintf(stderr, "Memory allocation failed for player[%d]->card\n", i);
                exit(EXIT_FAILURE);
            }
        }
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
        for (int i = 1; i < result.players + 1; i++)
            player[i]->number = result.cards;
        shuffle(card_fetch, result.decks * 52, result.demo_mode);
        player = initial_assignment(card_fetch, card_discard, player, result);
        player = play(player, card_fetch, card_discard, result);
        for (int i = 0; i < result.players + 1; i++)
            array[i] += player[i]->score;
        printf("---- Stats ----\n");
        printf("Round %d results: \n", k + 1);
        for (int i = 1; i < result.players + 1; i++)
            printf("Player %d's score is %d , total score is %d\n", i, player[i]->score, array[i]);
        printf("Round %d ends.\n", k + 1);
        printf("\n");
        sleep(7);
        if (result.demo_mode == 0)
            system("clear");
        free(card_fetch);
        free(card_discard);
        free(player[0]->card);
        free(player[0]);
        for (int i = 1; i < result.players + 1; i++)
        {
            for (int j = 0; j < player[i]->number; j++)
                free(player[i]->card[j]);
            free(player[i]->card);
            free(player[i]);
        }
        free(player);
    }
    if (result.demo_mode == 0)
        system("clear");
    printf("------Final results--------\n");
    for (int i = 1; i < result.players + 1; i++)
        printf("Player %d's score is %d\n", i, array[i]);
    fclose(file);
    free(array);
    return 0;
}
