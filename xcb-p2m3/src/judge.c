#include "onecard.h"

int judge(int n) // to shorten the function "play"
{
    if (n != 2 && n != 3 && n != 7 && n != 11 && n != 12)
        return 1;
    else
        return 0;
}

