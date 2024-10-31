#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int roundnumber;
extern int playernumber;

void init_beforestart();
void init_round();
void settle_round();

#endif