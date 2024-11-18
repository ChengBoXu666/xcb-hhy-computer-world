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

void shuffle(Card *card, int total, int mode);

void initial_output(Result result);

Player **initial_assignment(Card *card_fetch, Card *card_discard, Player **player, Result result);

Player **play(Player **player, Card *card_fetch, Card *card_discard, Result result);

void cards_output(Player **player, int index_player, int num_card);

void sort(Player **players,int i);

void card_output(int suit, int rank);

int judge(int n);

#endif


