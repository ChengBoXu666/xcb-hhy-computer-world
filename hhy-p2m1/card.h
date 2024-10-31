#ifndef CARD_H
#define CARD_H

#include <stdlib.h>
#include <time.h>

typedef struct {
    int suit;   //定义花色(rank):黑桃(1)->spade 红桃(2)->heart 方块(3)->dimond 梅花(4)->club
    int rank;   //定义数字:2,3,4,5,6,7,8,9,10,J,Q,L,A
}Card;



#endif 