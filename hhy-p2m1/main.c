#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//data structures definitions
typedef struct {
    int suit;
    int rank;
}Card;
typedef struct{
    Card *p_handcard;
    int index_top_handcard;
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

int const count_draw = 5;
int const count_round_draw = 2;

void press_enter_to_continue() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

void Init_cards(){
    printf("Number of decks: ");
    int x;  //get the import
    scanf("%d",&x);
    deck = (Card*)malloc(x*52*sizeof(Card));
    discard = (Card*)malloc((x+1)*52*sizeof(Card));
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
        player[i].index_top_handcard = -1;
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

void Discard(Card *p_deck, int *p_index_top, int num_discard){
    for(int i = 0; i < num_discard; i++){
        discard[index_top_discard].suit = p_deck[*p_index_top].suit;
        discard[index_top_discard].rank = p_deck[*p_index_top].rank;
        *p_index_top -= 1;
        index_top_discard++;
    }
}

void Init_Deal(){
    printf("\n");
    printf("Dealing cards...\n");
    Sleep(2000);
    for(int i = 0; i < num_player; i++){
        player[i].index_top_handcard += count_draw;
        player[i].p_handcard = (Card*)malloc(count_draw*sizeof(Card));
        for(int j = 0; j < count_draw; j++){
            player[i].p_handcard[j].suit = deck[index_top_deck-j].suit;
            player[i].p_handcard[j].rank = deck[index_top_deck-j].rank;
        }
        index_top_deck -= count_draw;
    }
}

void Print(int suit, int rank){
    printf("[");
    switch(suit){
        case 1:
            printf("Spades ");
            break;
        case 2:
            printf("Hearts ");
            break;
        case 3:
            printf("Diamonds ");
            break;
        case 4:
            printf("Clubs ");
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

int Determine_play_order(){
    printf("\n");
    printf("Determining play order...\n");
    Sleep(2000);
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
        Print(temp[index_top].suit,temp[index_top].rank);
        printf("\n");
        if(i == 0){
            min_rank = temp[index_top].rank;
            min_suit = temp[index_top].suit;
            min_index = i;
        }
        else{
            if(temp[index_top].rank < min_rank){
                min_rank = temp[index_top].rank;
                min_suit = temp[index_top].suit;
                min_index = i;
            }
            else if(temp[index_top].rank == min_rank && temp[index_top].suit < min_suit){
                min_suit = temp[index_top].suit;
                min_rank = temp[index_top].rank;
                min_index = i;
            }
        }
        index_top--;
    }
    Discard(temp, &index_top, 52-num_player);
    free(temp);
    return min_index;
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
    press_enter_to_continue();
    system("cls");
}

void Init_Round(int r, int *p_start_index){
    Init_Deal();
    if(r == 1){
        *p_start_index = Determine_play_order();
    } 
    printf("The game will start with player %d\n",*p_start_index+1);
    press_enter_to_continue();
}

void Restructure(Card *p_handcard, int index_top, int positon){
    int tempsuit = p_handcard[positon].suit;
    int temprank = p_handcard[positon].rank;
    for(int i = positon; i < index_top; i++){
        p_handcard[i].suit = p_handcard[i+1].suit;
        p_handcard[i].rank = p_handcard[i+1].rank;
    }
    p_handcard[index_top].suit = tempsuit;
    p_handcard[index_top].rank = temprank;
}

void Fetch(Card *p_handcard, int *p_index_top, int num_fetch){
    printf("Fetching %d cards...\n",num_fetch);
    Sleep(2000);
    for(int i = 0; i < num_fetch; i++){
        p_handcard[*p_index_top].suit = deck[index_top_deck].suit;
        p_handcard[*p_index_top].rank = deck[index_top_deck].rank;
        index_top_deck--;
        (*p_index_top)++;
    }
}

int Check(int beforesuit, int beforerank, Card *p_handcard, int index_top, int j){
    //show the card before
    printf("card before: ");
    Print(beforesuit,beforerank);
    printf("\n");
    //show the current player's cards
    int flag = 0;
    printf("player %d's cards: ",j+1);
    for(int i = 0; i <= index_top; i++){
        printf("%d:",i+1);
        Print(p_handcard[i].suit,p_handcard[i].rank);
        printf(" ");
        if(p_handcard[i].suit == beforesuit || p_handcard[i].rank == beforerank){
            flag = 1;
        }
    }
    printf("\n");
    return flag;
}

int Player_action(int beforesuit, int beforerank, Card *p_handcard, int index_top){
    int choice = 0;
    printf("choose a card to play: ");
    scanf("%d",&choice);
    while(1){
        if(choice < 1 || choice > index_top+1){
            printf("Invalid choice, please choose again: ");
            scanf("%d",&choice);
        }else if(p_handcard[choice-1].suit != beforesuit && p_handcard[choice-1].rank != beforerank){
            printf("Invalid choice, please choose again: ");
            scanf("%d",&choice);
        }else{
            break;
        }
    }
    return choice;
}

void Gameround(int r, int *p_start_index){
    //mark the index of the player now
    int j = *p_start_index;
    int direction = 1;

    //mark the card played before
    //the first card of the deck to initialize the rank and suit
    int beforesuit = deck[index_top_deck].suit;
    int beforerank = deck[index_top_deck].rank;
    Discard(deck,&index_top_deck,1);

    //start the round
    printf("---- Round %d ----\n",r);
    Sleep(1000);
    Init_Round(r, p_start_index);

    system("cls");
    printf("Show the first card: ");
    Print(beforesuit,beforerank);
    printf("\n");
    press_enter_to_continue();

    //the loop for the game round
    //when one player has played all cards, the game ends, break the loop
    while(1){
        system("cls");
        //show the card before
        //show the current player's cards
        int check = Check(beforesuit,beforerank,player[j].p_handcard,player[j].index_top_handcard,j);
        if(check == 0){
            printf("Player %d does not have any cards to play\n",j+1);
            Fetch(player[j].p_handcard,&player[j].index_top_handcard,count_round_draw);
            printf("Player %d's cards: ",j+1);
            for(int i = 0; i <= player[j].index_top_handcard; i++){
                printf("%d:",i+1);
                Print(player[j].p_handcard[i].suit,player[j].p_handcard[i].rank);
                printf(" ");
            }
            printf("\n");
            j = (j+direction)%num_player;
            press_enter_to_continue();
            continue;
        }
        //ask the current player to play a card
        int choice = Player_action(beforesuit,beforerank,player[j].p_handcard,player[j].index_top_handcard);
        //restructure the handcard array 
        Restructure(player[j].p_handcard,player[j].index_top_handcard,choice-1);
        printf("player %d played ",j+1);
        Print(player[j].p_handcard[player[j].index_top_handcard].suit,player[j].p_handcard[player[j].index_top_handcard].rank);
        beforesuit = player[j].p_handcard[player[j].index_top_handcard].suit;
        beforerank = player[j].p_handcard[player[j].index_top_handcard].rank;
        printf("\n");
        Discard(player[j].p_handcard,&player[j].index_top_handcard,1);
        if(player[j].index_top_handcard == -1){
            *p_start_index = j;
            printf("player %d has no more cards, the game ends\n",j+1);
            break;
        }
        press_enter_to_continue();
        j = (j+direction)%num_player;
    }
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
    //the index of the player who will start the game
    int start_index;

    //initialize the game
    Init(&r);
    //start the game
    for(int i = 1; i <= r; i++){
        Gameround(i,&start_index);
    }

    Free();
    return 0;
}