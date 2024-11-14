#include "onecard.h"

int main(int argc, char *argv[])
{
    Result result = inputing(argc, argv);
    if (result.demo_mode == -1) return 0;
    srand((unsigned int)time(NULL));
    initial_output(result);
    FILE *file=fopen(result.filename,"w");
    if(file==NULL)
    {            
        printf("Error: unable to open file\n"); 
        return 0;
    }
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
    initial_shuffle(card_fetch, result);

    player = initial_assignment(card_fetch, card_discard, player, result);

    player = play(player, card_fetch, card_discard, result);

    free(card_fetch);
    free(card_discard);
    for (int i = 0; i < result.players + 1; i++)
    {
        free(player[i]);
    }
    free(player);
    free(result.filename);
    fclose(file);
    return 0;
}


