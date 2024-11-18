#ifndef ONECARD_H
#define ONECARD_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
    int t1;
    int t2;
    int mini;
} Tran;
typedef struct
{
    int suit;
    int rank;
} Card;

typedef struct
{
    int direction;
    int attack;
    int index1;
    int index2;
    Card *current;
} Table;

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

Tran initial_assignment(Card *card_fetch, Card *card_discard, Player *player, Result result,Tran trans);

void play(Player *player, Card *card_fetch, Card *card_discard, Result result,Tran trans);

void cards_output(Player *player, int num_card);

void sort(Player *players);

void card_output(int suit, int rank);

int judge(int n);

#endif


