#ifndef ONECARD_H
#define ONECARD_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "logical.h"

typedef struct
{
    int direction;
    int attack;
    int index1;
    int index2;
    Card *current;
} Table;

Table initial_table(Card *card_fetch, Card *card_discard, Tran trans,Result result,FILE *file);

void play(Player *player, Card *card_fetch, Card *card_discard, Result result,Tran trans,FILE *file);

int judge(int n);

#endif


