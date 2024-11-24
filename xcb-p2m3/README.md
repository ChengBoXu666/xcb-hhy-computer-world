# Project 2: Onecard

## Introduction

Onecard is a card game that use poker cards to simulate the game of UNO. The cards with different suits and ranks are divided into basic cards and functional cards. Rank 2, 3, 7, J, Q in all suits are regards as functional cards, while the rest are basic cards.

You can determine the player number, the number of decks, the number of cards, the number of players' initial cards and rounds. You can also fit demo mode to see how the game works. And all the data will be saved in a log file if you want to review it later.

## How to start

1. Ensure that you are in a **Linux environment** (e.g. Ubuntu).
2. Open the terminal and navigate to the directory named            "ChengboXu524370910111-p2"
3. Input "**make**" to compile the program.
4. Input "**./onecard -h**" or "**./onecard --help**" to view the help message.
5. Input the varibles' number you want to set.(You can view the default values in help message)
   - e.g   "**./onecard -n 2 -d 1**" to set the number of players to 2 and the number of decks to 1.
6. If you want to view the **demo mode**, add "**-a**" or "**--auto**".
7. If you want to choose **the log file name**, use "**--log \<filename\>**" and fill your desired filename in the **\<filename\>** part.
8. Press Enter to start the game.

## How to play
- The game starts with the player who has the first turn.
- Each player can **input a number** presenting their **option**.
  - **0**: No card to play / Not to play any card.
  - **1**: Play Card 1.
  - **2**: Play Card 2.
  - **3**: Play Card 3.
  - etc.

 ## Basic Rules(From p2 document)
### Overview
One Card is a rather simple game played by n persons over a pre-decided number of rounds r. A total of d decks of Poker cards, excluding Jokers, are shufffed and c cards are offered to each player. Before the game starts each player is offered an extra card to determine the playing order. This game is then discarded. The game will be played counter-clockwise, starting with the player who received the extra card with lowest rank. Once the playing order has been decided all those initial n cards are directly put in the discard pile. Finally, the game starts with the first card of the stock pile being posed face-up, to initiate the rank and suit.

As the game starts each player, following the deffned order, plays exactly one card either following the rank or the suit deffned by the previous card. Any played card directly goes into the discard pile, and anyone who is unable to play should draw a card from the top of the stock pile. If the stock pile is exhausted, the discard pile is shufffed and used as stock pile.

As soon as a player has no cards left, the rounds stops. All other players receive a penalty equal to the number of cards left in their hands. The player who won the round initiates the following one, all the other rules remain unchanged. At the end of the r rounds the ffnal score of the players is determined by summing up their respective penalties. The person with highest score wins. In case of equality more than one player can be declared winner.

### Cards
Cards split into four main categories:

#### Attack:
- Cards with rank 2: the next player draws two cards from the stock pile;

- Cards with rank 3: the next player draws three cards from the stock pile;

#### Defense:
- Cards with rank 7: cancel an attack, i.e. do not draw any card if a 2 or a 3 was played before;
#### Action:
- Queen cards: reverse the playing order from counter-clockwise to clockwise or clockwise to counterclockwise;

- Jack cards: skip the next player;

#### Regular:
Any other card has no special effect and is only used to match the previous card's rank or suit;

#### Notes on cards and attacks:
- The effect of the attack cards is cumulative.
- A Queen or a Jack, of same suit as the previous card, can be played to redirect an attack on the previous player, or the player after the next one, respectively;
- When attacked, a player not playing a special card (2, 3, 7, Q, J) must draw cards from the stock pile, before ending its turn;

## Extra complement rules

- **Only** when a card fits the previous card's **rank or suit**, it can be played no matter it is a basic or a functional card.

- If you play a **invalid card**, you are not allow to have another chance and will be regard as giving up the turn (just the same as input **0**);

- If you play a **functional card**, you are not allow to have another chance and will be regard as giving up the turn (just the same as input **0**);                                                                       

## Layers

### Layer1
- basic.h
- inputing.c
- card_output,c
- cards_output,c
- initial_output.c
- shuffle.c
  
### Layer2
- logical.h
- initial_assignment.c
- sort.c
  
- ### layer3
- initial_table.c
- play.c
- judge.c

## Bugs
- Memory will leak in player->card[], and I still don't find out the way to fix it.                                      