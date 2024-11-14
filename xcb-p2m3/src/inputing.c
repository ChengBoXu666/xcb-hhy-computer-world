#include "onecard.h"

Result inputing(int argc, char *argv[])
{
    int players = 4;
    int cards = 5;
    int decks = 2;
    int rounds = 1;
    char *filename = "onecard.log";
    int demo_mode = 0;
    Result result;
    for (int i = 1; i < argc; i++)
    {
        if ((argv[i][0] == '-' && argv[i][1] == 'h') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'h' && argv[i][3] == 'e' && argv[i][4] == 'l' && argv[i][5] == 'p'))
        {
            printf("-h|--help              Print this help message\n");
            printf("--log filename         Write the logs in filename (default: onecard.log)\n");
            printf("-n n|--player-number=n Specify number of players, n must be larger than 2 (default: 4)\n");
            printf("-c c|--initial-cards=c Deal c cards per player, c must be at least 2 (default: 5)\n");
            printf("-d d|--decks=d         Use d decks of 52 cards each, d must be at least 2 (default: 2)\n");
            printf("-r r|--rounds=r        Play r rounds, r must be at least 1 (default: 1)\n");
            printf("-a|--auto              Run in demo mode\n");
            result.demo_mode = -1;
            result.cards = cards; result.decks = decks; result.filename = filename; result.players = players; result.rounds = rounds;
            return result;
        }
        if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'l' && argv[i][3] == 'o' && argv[i][4] == 'g' && argv[i][5] == 0)
        {
            if (i + 1 < argc)
                filename = argv[++i];
        }
        else if ((argv[i][0] == '-' && argv[i][1] == 'n') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'p' && argv[i][3] == 'l' && argv[i][4] == 'a' && argv[i][5] == 'y' && argv[i][6] == 'e' && argv[i][7] == 'r' && argv[i][8] == '-' && argv[i][9] == 'n' && argv[i][10] == 'u' && argv[i][11] == 'm' && argv[i][12] == 'b' && argv[i][13] == 'e' && argv[i][14] == 'r' && argv[i][15] == '='))
        {
            players = atoi(argv[i] + ((argv[i][1] == 'n') ? 3 : 16));
        }
        else if ((argv[i][0] == '-' && argv[i][1] == 'c') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'i' && argv[i][3] == 'n' && argv[i][4] == 'i' && argv[i][5] == 't' && argv[i][6] == 'i' && argv[i][7] == 'a' && argv[i][8] == 'l' && argv[i][9] == '-' && argv[i][10] == 'c' && argv[i][11] == 'a' && argv[i][12] == 'r' && argv[i][13] == 'd' && argv[i][14] == 's' && argv[i][15] == '='))
        {
            cards = atoi(argv[i] + ((argv[i][1] == 'c') ? 3 : 16));
        }
        else if ((argv[i][0] == '-' && argv[i][1] == 'd') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'd' && argv[i][3] == 'e' && argv[i][4] == 'c' && argv[i][5] == 'k' && argv[i][6] == 's' && argv[i][7] == '='))
        {
            decks = atoi(argv[i] + ((argv[i][1] == 'd') ? 3 : 8));
        }
        else if ((argv[i][0] == '-' && argv[i][1] == 'r') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'r' && argv[i][3] == 'o' && argv[i][4] == 'u' && argv[i][5] == 'n' && argv[i][6] == 'd' && argv[i][7] == 's' && argv[i][8] == '='))
        {
            rounds = atoi(argv[i] + ((argv[i][1] == 'r') ? 3 : 9));
        }
        else if ((argv[i][0] == '-' && argv[i][1] == 'a') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'a' && argv[i][3] == 'u' && argv[i][4] == 't' && argv[i][5] == 'o'))
        {
            demo_mode = 1;
        }
    }
    result.cards = cards;
    result.decks = decks;
    result.filename = filename;
    result.players = players;
    result.rounds = rounds;
    result.demo_mode = demo_mode;
    return result;
}

