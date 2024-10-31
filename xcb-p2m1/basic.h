#ifndef BASIC_H
#define BASIC_H

typedef struct {
    int players;      
    int cards;      
    int decks;              
    int rounds;            
    char *filename;  
    int demo_mode;
} Result;

typedef enum {
    Spades,
    Hearts,
    Diamonds,
    Clubs
} Suit;

typedef struct {
    Suit suit;
    int rank;
} Card;

 typedef struct {
     Card **card;
     Card leader;
     int score;
 } Player;

//void print_help();

Result inputing(int argc,char *argv[]);

void intial_shuffle(Card* card_fetch,int total);

void intial_output(int n,int r,int d,int c,int demo);

#endif