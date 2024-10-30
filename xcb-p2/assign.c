#include<stdio.h>
#include "basic.h"

void assign(int n,Player player[]) {
    for (int i=0; i<n; i++) {
        int tsuit=rand() % 4;
        int trank=rand() % 13;
        player[i].card.suit=tsuit;
        player[i].card.rank=trank+1;
    }
}