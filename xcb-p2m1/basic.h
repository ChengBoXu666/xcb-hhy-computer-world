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

Result initial(int argc,char *argv[]);

#endif