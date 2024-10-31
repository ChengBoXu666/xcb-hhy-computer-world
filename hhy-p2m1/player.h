#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

typedef struct{
    int score;          
    int card_number;    
    Card* card_list;    
}Player;

void Fetch( int fetch_number, Player* player);

void Play( int play_number, Player* player);

void Score_update( int add_number, Player* player);

#endif