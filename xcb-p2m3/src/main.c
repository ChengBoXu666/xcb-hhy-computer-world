#include "onecard.h"
int main(int argc, char *argv[])
{
    Result result = inputing(argc, argv); // result is used to store the inputed values
    if (result.demo_mode == -1)
        return 0;                             // if demo mode is -1, it means the writer input -h or --help
    srand((unsigned int)time(NULL));          // random seed
    FILE *file = fopen(result.filename, "w"); // open the file to write
    if (file == NULL)
    {
        printf("Error: unable to open file\n");
        return 0;
    }
    initial_output(result, file);
    int *array = (int *)malloc((size_t)(result.players) * sizeof(int));
    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fprintf(file, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < result.players; i++)
        array[i] = 0; // initialize the array to store the scores of each player
    for (int k = 0; k < result.rounds; k++)
    {
        printf("Round %d\n", k + 1);
        fprintf(file, "Round %d\n", k + 1);
        printf("\n");
        fprintf(file, "\n");
        if (result.demo_mode == 0)
            sleep(2);
        Player *head = NULL, *tail = NULL;
        for (int i = 0; i < result.players; i++) // initial circular double linked list of players
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
        Player *player = NULL;
        player = head;
        Card *card_fetch = (Card *)malloc((size_t)result.decks * 52 * sizeof(Card)); // create an array to store all the cards on table
        if (card_fetch == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            fprintf(file, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        Card *card_discard = (Card *)malloc((size_t)result.decks * 52 * sizeof(Card)); // create an array to store all the discarded cards
        if (card_discard == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            fprintf(file, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < result.decks * 52; i++)
        {
            card_fetch[i].suit = i % 52 / 13 + 1;
            card_fetch[i].rank = i % 52 % 13 + 2;
        } // initial the cards' suit and rank
        shuffle(card_fetch, result.decks * 52, result.demo_mode, file);
        Tran trans = {0, 0, 0};
        trans = initial_assignment(card_fetch, card_discard, head, result, trans, file);
        for (int i = 0; i < result.players; i++)
        {
            if (player->index == trans.mini + 1)
                break;
            player = player->next;
        }
        play(player, card_fetch, card_discard, result, trans, file);
        for (int i = 0; i < result.players; i++)
        {
            array[i] += head->score;
            head = head->next;
        }
        printf("---- Stats ----\n");
        fprintf(file, "---- Stats ----\n"); // out put the single round results
        printf("Round %d results: \n", k + 1);
        fprintf(file, "Round %d results: \n", k + 1);
        for (int i = 0; i < result.players; i++)
        {
            printf("Player %d's score is %d , total score is %d\n", i + 1, head->score, array[i]);
            fprintf(file, "Player %d's score is %d , total score is %d\n", i + 1, head->score, array[i]);
            head = head->next;
        }
        printf("Round %d ends.\n", k + 1);
        fprintf(file, "Round %d ends.\n", k + 1);
        printf("\n");
        fprintf(file, "\n");
        if (result.demo_mode == 0)
        {
            sleep(7);
            system("clear");
        }
        free(card_fetch);
        free(card_discard);
        for (int i = 0; i < result.players - 1; i++) // free player's memory
        {
            for (int j = 0; j < player->number; j++)
                free(player->card[j]);
            free(player->card);
            Player *temp = NULL;
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
    fprintf(file, "------Final results--------\n");
    int max = -100000, maxi = -1;
    for (int i = 0; i < result.players; i++)
    {
        printf("Player %d's score is %d\n", i + 1, array[i]);
        fprintf(file, "Player %d's score is %d\n", i + 1, array[i]);
        if (array[i] > max)
        {
            max = array[i];
            maxi = i + 1;
        }
    }
    printf("\nPlayer %d wins the game!\n", maxi);
    fprintf(file, "\nPlayer %d wins the game!\n", maxi);
    fclose(file);
    free(array);
    return 0;
}
