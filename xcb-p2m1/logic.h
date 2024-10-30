#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

typedef enum {
    Spades,
    Hearts,
    Diamonds,
    Clubs
} suit_type;

typedef struct {
    suit_type suit;
    int rank;
} card;

#endif