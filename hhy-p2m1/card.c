#include "card.h"

Card* Init_deck(int NumberOfDecks){
    Card* deck = (Card*)malloc(NumberOfDecks*52*sizeof(Card));  //����һ����СΪ������*52*Card�ṹ��С�Ŀռ����ڴ��ÿ���Ƶ���Ϣ
    for(int i = 0; i < NumberOfDecks*52; i++){
        deck[i].suit = i%52/13 + 1;     //�����ƵĻ�ɫ
        deck[i].rank = i%52%13 + 1;     //�����Ƶ�����
    }
    return deck;    //����������ʼ��ַ
}

void Shuffle(Card* deck){
    
}

