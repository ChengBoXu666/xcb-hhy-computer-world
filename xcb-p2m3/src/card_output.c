#include "onecard.h"

void card_output(int suit, int rank, FILE *file) // used to output one single card
{
    switch (suit)
    {
    case 1:
        printf("%s", "Spades ");
        fprintf(file, "%s", "Spades ");
        break;
    case 2:
        printf("%s", "Hearts ");
        fprintf(file, "%s", "Hearts ");
        break;
    case 3:
        printf("%s", "Diamonds ");
        fprintf(file, "%s", "Diamonds ");
        break;
    case 4:
        printf("%s", "Clubs ");
        fprintf(file, "%s", "Clubs ");
        break;
    }
    switch (rank)
    {
    case 2:
        printf("%s", "2; ");
        fprintf(file, "%s", "2; ");
        break;
    case 3:
        printf("%s", "3; ");
        fprintf(file, "%s", "3; ");
        break;
    case 4:
        printf("%s", "4; ");
        fprintf(file, "%s", "4; ");
        break;
    case 5:
        printf("%s", "5; ");
        fprintf(file, "%s", "5; ");
        break;
    case 6:
        printf("%s", "6; ");
        fprintf(file, "%s", "6; ");
        break;
    case 7:
        printf("%s", "7; ");
        fprintf(file, "%s", "7; ");
        break;
    case 8:
        printf("%s", "8; ");
        fprintf(file, "%s", "8; ");
        break;
    case 9:
        printf("%s", "9; ");
        fprintf(file, "%s", "9; ");
        break;
    case 10:
        printf("%s", "10; ");
        fprintf(file, "%s", "10; ");
        break;
    case 11:
        printf("%s", "Jack; ");
        fprintf(file, "%s", "Jack; ");
        break;
    case 12:
        printf("%s", "Queen; ");
        fprintf(file, "%s", "Queen; ");
        break;
    case 13:
        printf("%s", "King; ");
        fprintf(file, "%s", "King; ");
        break;
    case 14:
        printf("%s", "Ace; ");
        fprintf(file, "%s", "Ace; ");
        break;
    }
}
