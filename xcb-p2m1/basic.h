#ifndef BASIC_H
#define BASIC_H


 typedef struct {
     Card card;
     int score;
 } Player;

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

#endif