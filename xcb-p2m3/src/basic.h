#ifndef BASIC_H
#define BASIC_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct
{
    int suit;
    int rank;
} Card;

typedef struct
{
    int players;
    int cards;
    int decks;
    int rounds;
    char *filename;
    int demo_mode;
} Result;

typedef struct Player
{
    Card **card;
    Card *first;
    int score;
    int number;
    int index;
    struct Player *next; 
    struct Player *prev;
} Player;

Result inputing(int argc, char *argv[]);

void shuffle(Card *card, int total, int mode);

void initial_output(Result result);

void cards_output(Player *player, int num_card);

void card_output(int suit, int rank);

#endif

