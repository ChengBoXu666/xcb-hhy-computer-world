#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

typedef struct{
    int score;          //玩家分数
    int card_number;    //玩家卡牌数
    Card* card_list;    //玩家卡牌组(动态)
}Player;

void Fetch( int fetch_number, Player* player);

void Play( int play_number, Player* player);

void Score_update( int add_number, Player* player);

#endif