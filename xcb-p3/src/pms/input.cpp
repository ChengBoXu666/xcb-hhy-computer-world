#include <iostream>
#include <string>
#include "pms.h"

Result inputing(int argc, char *argv[]) // read arguments from command line
{
    int n = 10;
    int floor1 = 8;
    int floor2 = 6;
    int ishelp=0;
    Result result; 
    for (int i = 1; i < argc; i++)
    {
        if ((argv[i][0] == '-' && argv[i][1] == 'h') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'h' && argv[i][3] == 'e' && argv[i][4] == 'l' && argv[i][5] == 'p'))
        {
            std::cout<<("-h|--help              Print this help message\n");
            std::cout<<("-n n|--car-number=n    Specify number of cars, n must be larger than 8 (default: 10)\n");
            std::cout<<("-f1 c|--floor1=c       Specify number of the capcity floor1, c must be larger than 5 (default: 8)\n");
            std::cout<<("-f2 d|--floor2=d       Specify number of the capcity floor1, d must be larger than 5 (default: 6)\n");
            result.n = 0;
            result.floor1 = 0;
            result.floor2 = 0;
            result.ishelp = 1;
            return result;
        }
        if ((argv[i][0] == '-' && argv[i][1] == 'n') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'c' && argv[i][3] == 'a' && argv[i][4] == 'r' && argv[i][5] == '-' && argv[i][6] == 'n' && argv[i][7] == 'u' && argv[i][8] == 'm' && argv[i][9] == 'b' && argv[i][10] == 'e' && argv[i][11] == 'r' && argv[i][12] == '=' ))
        {
            n = atoi(argv[i] + ((argv[i][1] == 'n') ? 3 : 13));
        }
        else if ((argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '1') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'f' && argv[i][3] == 'l' && argv[i][4] == 'o' && argv[i][5] == 'o' && argv[i][6] == 'r' && argv[i][7] == '1'&& argv[i][8] == '=' ))
        {
            floor1 = atoi(argv[i] + ((argv[i][1] == 'c') ? 3 : 9));
        }
        else if ((argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '2') || (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'f' && argv[i][3] == 'l' && argv[i][4] == 'o' && argv[i][5] == 'o' && argv[i][6] == 'r' && argv[i][7] == '1'&& argv[i][8] == '=' ))
        {
            floor2 = atoi(argv[i] + ((argv[i][1] == 'd') ? 3 : 9));
        }
        
    }
    result.n = n; // store the values in the result struct
    result.floor1 = floor1;
    result.floor2 = floor2;
    result.ishelp = ishelp;
    return result;
}
