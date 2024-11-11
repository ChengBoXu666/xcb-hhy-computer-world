#ifndef BASIC_H
#define BASIC_H

typedef struct
{
    int players;
    int cards;
    int decks;
    int rounds;
    char *filename;
    int demo_mode;
} Result;

typedef struct
{
    int suit;
    int rank;
} Card;

typedef struct
{
    int player;
    int direction;
    int attack;
    int index1;
    int index2;
    Card *current;
} Table;

typedef struct
{
    Card **card;
    Card *first;
    int score;
    int current1;
    int current2;
    int number;
} Player;

Result inputing(int argc, char *argv[]);

void initial_shuffle(Card *card_fetch, int total);

void initial_output(int n, int r, int d, int c, int demo);

Player **initial_assignment(Card *card_fetch, Card *card_discard, Player **player, Result result);

Player **play(Player **player, Card *card_fetch, Card *card_discard, Result result);

void card_output(Player **player, int index_player, int num_card);

#endif
