#include "player.h"

Player* Init_player(int play_id,int FirstNumberOfCard){
    Player* player = (Player*)malloc(sizeof(player));
    player->score = 0;
    player->card_number = FirstNumberOfCard;
    player->card_list = (Card*)malloc(player->card_number*sizeof(Card));
}

void Fetch( int fetch_number, Player* player){
    Card* new_list = (Card*)malloc((player->card_number+fetch_number)*sizeof(Card));


}

void Play( int play_number, Player* player){

}

void Score_update( int add_number, Player* player){

}