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

void shuffle(Card *card, int total, int mode,FILE *file);

void initial_output(Result result,FILE *file);

void cards_output(Player *player, int num_card,FILE *file);

void card_output(int suit, int rank,FILE *file);

#endif

