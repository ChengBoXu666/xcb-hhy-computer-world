#include <iostream>
#include "parkinglot.h"

//basic vehicle
int Vehicle::cost_calc() const {
    if  ((departure_time-arrival_time)%(3600/time_multiplier)==0) return cost[static_cast<size_t>(type)]*(static_cast<int>(departure_time-arrival_time)%3600);
    else return cost[static_cast<size_t>(type)]*(static_cast<int>(departure_time-arrival_time)%3600+1);
}
Vehicle::Vehicle(VehicleType t) : type(t){vehicle_slot.slot_number = -1;vehicle_slot.is_occupied = false;}
Vehicle::~Vehicle() = default;
void Vehicle::arrive() {time(&arrival_time);}
void Vehicle::depart() {time(&departure_time);}
void Vehicle::in_ticket() const{
    std::cout << "IN TICKET" << "\n";
    std::cout << "Arrival Time: " << static_cast<int>(arrival_time) << "\n";
    std::cout << "Vehicle Type: " << vehicle_type[static_cast<size_t>(type)] << "\n";
    std::cout << "Slot" << vehicle_slot.slot_number+1 << "\n";
}
void Vehicle::out_ticket() const{
    std::cout << "OUT TICKET" << "\n";
    std::cout << "Departure Time: " << static_cast<int>(departure_time) << "\n";
    std::cout << "Total Time: " << static_cast<int>(departure_time-arrival_time)*time_multiplier << "\n";  
    std::cout << "Vehicle Type: " << vehicle_type[static_cast<size_t>(type)] << "\n";
    std::cout << "Cost: $" << cost_calc() << "\n";
}
void Vehicle::park(int slot) {
    vehicle_slot.slot_number = slot;
}
int Vehicle::unpark() const{
    return vehicle_slot.slot_number;
}


//parking lot
ParkingLot::ParkingLot(int n) : total_slots(n) {
    slots.resize(static_cast<size_t>(n));
    for (int i=0; i<n; i++) {
        slots[static_cast<size_t>(i)].slot_number = i+1;
        slots[static_cast<size_t>(i)].is_occupied = false;
    }
}
int ParkingLot::find_lot() const{
    for (int i=0; i<total_slots; i++) {
        if (!slots[static_cast<size_t>(i)].is_occupied) return i;
    }
    return -1;
}
int ParkingLot::available_slots() const{
    int count=0;
    for (int i=0; i<total_slots; i++) {
        if (!slots[static_cast<size_t>(i)].is_occupied) count++;
    }
    return count;
}
void ParkingLot::park(Vehicle* v) {
    if(int lot=find_lot(); lot!=-1){
        v->park(lot);
        v->arrive();
        v->in_ticket();
        slots[static_cast<size_t>(lot)].is_occupied = true;
    }
    else std::cout << "No slots available" << "\n";
}
void ParkingLot::unpark(Vehicle* v) {
    int slot=v->unpark();
    v->depart();
    v->out_ticket();
    slots[static_cast<size_t>(slot)].is_occupied = false;
    v->depart();
}