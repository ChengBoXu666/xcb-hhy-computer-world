#ifndef LOGICAL_H
#define LOGICAL_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "basic.h"

typedef struct
{
    int t1;
    int t2;
    int mini;
} Tran;

Tran initial_assignment(Card *card_fetch, Card *card_discard, Player *player, Result result,Tran trans);

void sort(Player *players);

#endif

