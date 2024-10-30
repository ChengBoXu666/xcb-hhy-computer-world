#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

void print_help() {
    printf("-h|--help              Print this help message\n");
    printf("--log filename         Write the logs in filename (default: onecard.log)\n");
    printf("-n n|--player-number=n Specify number of players, n must be larger than 2 (default: 4)\n");
    printf("-c c|--initial-cards=c Deal c cards per player, c must be at least 2 (default: 5)\n");
    printf("-d d|--decks=d         Use d decks of 52 cards each, d must be at least 2 (default: 2)\n");
    printf("-r r|--rounds=r        Play r rounds, r must be at least 1 (default: 1)\n");
    printf("-a|--auto              Run in demo mode\n");
}
int get(int argc,char *argv[]) {
    int players=4;      
    int cards=5;      
    int decks=2;              
    int rounds=1;            
    char *filename="onecard.log";  
    int demo_mode=0;         
    for (int i=1;i<argc;i++) {
        if (strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i],"--log")==0 && i+1<argc) {
            filename=argv[++i];
        } else if (strncmp(argv[i],"-n",2)==0 || strncmp(argv[i],"--player-number=",16)==0) {
            players=atoi(argv[i]+((strncmp(argv[i],"-n",2)==0 ? 2:16)));    
        } else if (strncmp(argv[i],"-c",2) == 0 || strncmp(argv[i],"--initial-cards=",16)==0) {
            cards=atoi(argv[i]+((strncmp(argv[i],"-c",2)==0 ? 2:16))); 
        } else if (strncmp(argv[i],"-d",2) == 0 || strncmp(argv[i], "--decks=", 8) == 0) {
            decks=toi(argv[i]+((strncmp(argv[i],"-d",2)==0 ? 2:8)));
        } else if (strncmp(argv[i],"-r",2)==0 || strncmp(argv[i],"--rounds=",9) == 0) {
            rounds=atoi(argv[i]+((strncmp(argv[i],"-r",2)==0 ? 2:9)));
        } else if (strcmp(argv[i],"-a")==0 || strcmp(argv[i],"--auto")==0) {
            demo_mode=1;
        }
    }
    return 0;
}
