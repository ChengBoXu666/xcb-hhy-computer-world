#include "card.h"

Card* Init_deck(int NumberOfDecks){
    Card* deck = (Card*)malloc(NumberOfDecks*52*sizeof(Card));  //请求一个大小为牌组数*52*Card结构大小的空间用于存放每张牌的信息
    for(int i = 0; i < NumberOfDecks*52; i++){
        deck[i].suit = i%52/13 + 1;     //分配牌的花色
        deck[i].rank = i%52%13 + 1;     //分配牌的数字
    }
    return deck;    //返回牌组起始地址
}

void Shuffle(Card* deck){
    
}

