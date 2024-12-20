#include <iostream>
#include <vector>
#include "parkinglot_outline.h"
#include "parkinglot_initial.h"

a_parking_lot::a_parking_lot(){
    num=parkinglot_outline();
    sl.resize(num);
    for(int i=0;i<num;++i){
        sl[i]=_slots_(i+1,num);
    }
}

a_parking_lot::~a_parking_lot(){
    sl.clear();
}

void a_parking_lot::draw(){
    for(int j=0;j<num;++j){
        sl[j].draw_slots();
    }
}
