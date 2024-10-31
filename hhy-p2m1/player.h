#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

typedef struct{
    int score;          //��ҷ���
    int card_number;    //��ҿ�����
    Card* card_list;    //��ҿ�����(��̬)
}Player;

void Fetch( int fetch_number, Player* player);

void Play( int play_number, Player* player);

void Score_update( int add_number, Player* player);

#endif