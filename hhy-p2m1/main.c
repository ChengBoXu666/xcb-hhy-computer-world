#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//data structures definitions
typedef struct {
    int suit;
    int rank;
}Card;
typedef struct{
    Card *p_handcard;
    int num_handcard;
    int score;
}Player;
//define global variable
//define deck in a form of stack
Card *deck;
int index_top_deck;
Card *discard;
int index_top_discard;

Player *player;
int num_player;

void Init_cards(){
    printf("Number of decks: ");
    int x;  //get the import
    scanf("%d",&x);
    deck = (Card*)malloc(x*52*sizeof(Card));
    discard = (Card*)malloc(x*52*sizeof(Card));
    for(int i = 0; i < x*52; i++){
        deck[i].suit = i%52/13 + 1;
        deck[i].rank = i%52%13 + 2;
        discard[i].suit = 0;
        discard[i].rank = 0;
    }
    index_top_deck = x*52-1;
    index_top_discard = -1;
}

void Init_players(){
    printf("Number of players: ");
    int x;  //get the import
    scanf("%d",&x);
    player = (Player*)malloc(x*sizeof(Player));
    for(int i = 0; i < x; i++){
        player[i].score = 0;
        player[i].num_handcard = 0;
    }
    num_player = x;
}

void Shuffle(Card *p_deck, int index_top){
    printf("Shuffling cards...\n");
    for(int i = index_top; i > 0; i--){
        int j = rand()%i;
        int tsuit = p_deck[i].suit;
        int trank = p_deck[i].rank;
        p_deck[i].suit = p_deck[j].suit;
        p_deck[i].rank = p_deck[j].rank;
        p_deck[j].suit = tsuit;
        p_deck[j].rank = trank;
    }
}
void Init_Deal(){
    printf("Dealing cards...\n");
    for(int i = 0; i < num_player; i++){
        player[i].num_handcard = 5;
        player[i].p_handcard = (Card*)malloc(5*sizeof(Card));
        for(int j = 0; j < 5; j++){
            player[i].p_handcard[j].suit = deck[index_top_deck-j].suit;
            player[i].p_handcard[j].rank = deck[index_top_deck-j].rank;
        }
        index_top_deck -= 5;
    }
}

void Print(int suit, int rank){
    printf("[");
    switch(suit){
        case 1:
            printf("♠ ");
            break;
        case 2:
            printf("♥ ");
            break;
        case 3:
            printf("♦ ");
            break;
        case 4:
            printf("♣ ");
            break;
        default:
            printf("? ");
            break;
    }
    switch(rank){
        case 11:
            printf("Jack");
            break;
        case 12:
            printf("Queen");
            break;
        case 13:
            printf("King");
            break;
        case 14:
            printf("Ace");
            break;
        default:
            printf("%d",rank);
            break;
    }
    printf("]");
}

void Determine_play_order(){
    printf("Determining play order...\n");
    Card *temp = (Card*)malloc(52*sizeof(Card));
    for(int i = 0; i < 52; i++){
        temp[i].suit = i/13 + 1;
        temp[i].rank = i%13 + 2;
    }
    int index_top = 51;
    for(int i = index_top; i > 0; i--){
        int j = rand()%i;
        int tsuit = temp[i].suit;
        int trank = temp[i].rank;
        temp[i].suit = temp[j].suit;
        temp[i].rank = temp[j].rank;
        temp[j].suit = tsuit;
        temp[j].rank = trank;
    }
    int min_rank = 0;
    int min_suit = 0;
    int min_index = 0;
    for(int i = 0; i < num_player; i++){
        printf("Player %d: ",i+1);
        Print(temp[index_top-i].suit,temp[index_top-i].rank);
        printf("\n");
        if(i == 0){
            min_rank = temp[index_top-i].rank;
            min_suit = temp[index_top-i].suit;
            min_index = i;
        }
        else{
            if(temp[index_top-i].rank < min_rank){
                min_rank = temp[index_top-i].rank;
                min_suit = temp[index_top-i].suit;
                min_index = i;
            }
            else if(temp[index_top-i].rank == min_rank && temp[index_top-i].suit < min_suit){
                min_suit = temp[index_top-i].suit;
                min_rank = temp[index_top-i].rank;
                min_index = i;
            }
        }
    }
    printf("The game will start with player %d\n",min_index+1);
    free(temp);
}
        

void Init(int *p_r){
    printf("########################\n");
    printf("#                      #\n");
    printf("# Welcome to One Card! #\n");
    printf("#                      #\n");
    printf("########################\n");
    printf("---- Initial setup ----\n");
    printf("Number of rounds: ");
    scanf("%d",p_r);
    Init_cards();
    Init_players();
    Shuffle(deck,index_top_deck);
    Init_Deal();
    Determine_play_order();
}

void Free(){
    free(player);
    free(deck);
    free(discard);
}
int main(void){
    srand(time(0));
    //roundnumber
    int r;  

    Init(&r);

    Free();
    return 0;
}