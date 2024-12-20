#ifndef _PARKINGLOT_INITIAL_H
#define _PARKINGLOT_INITIAL_H
#include <vector>
#include "parkinglot_places.h"


class a_parking_lot{
    public:
        a_parking_lot();
        ~a_parking_lot();
        void draw();
    private:
        int num;
        std::vector<_slots_> sl;
};
#endif