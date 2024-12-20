#ifndef _PARKINGLOT_PLACES_H
#define _PARKINGLOT_PLACES_H

#include "vec.h"
#include "parkinglot.h"
class _slots_
{
public:
    _slots_(int n, int total_) : length(0.4f), num(n), total(total_)
    {
        width = 4.0f / ((float)n + 3);
        if ((float)num <= (float)total / 2)
        {
            center = Vec(-0.1f + (float)(((float)n + 1) * width), 0.6f);
        }
        else
        {
            center = Vec(-0.1f + (float)(((float)n + 1 - (float)total / 2.0f) * width), -0.6f);
        }
    };
        void draw_slots();

    private:
        int num;
        int total;
        Vec center;
        float length; // const member
        float width;
    };
#endif