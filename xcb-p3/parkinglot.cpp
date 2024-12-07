#include "parkinglot.h"

//basic vehicle
int Vehicle::cost_calc() const {
    if  ((departure_time-arrival_time)%(3600/time_multiplier)==0) return cost[(int)type]*((int)(departure_time-arrival_time)%3600);
    else return cost[(int)type]*((int)(departure_time-arrival_time)%3600+1);
}
Vehicle::Vehicle(VehicleType t) : type(t){}
Vehicle::~Vehicle() = default;
void Vehicle::arrive() {time(&arrival_time);}
void Vehicle::depart() {time(&departure_time);}
void Vehicle::in_ticket() const{
    std::cout << "IN TICKET" << "\n";
    std::cout << "Arrival Time: " << (int)arrival_time << "\n";
    std::cout << "Vehicle Type: " << vehicle_type[(int)type] << "\n";
    std::cout << "Slot" << vehicle_slot.slot_number << "\n";
}
void Vehicle::out_ticket() const{
    std::cout << "OUT TICKET" << "\n";
    std::cout << "Departure Time: " << departure_time << "\n";
    std::cout << "Total Time: " << (int)(departure_time-arrival_time) << "\n";  
    std::cout << "Vehicle Type: " << vehicle_type[(int)type] << "\n";
    std::cout << "Cost: $" << cost_calc() << "\n";
}
void Vehicle::park(int slot) {
    vehicle_slot.slot_number = slot;
}
int Vehicle::unpark() const{
    return vehicle_slot.slot_number;
}

//different vehicles
Car::Car() : Vehicle(VehicleType::Car) {}
UFO::UFO() : Vehicle(VehicleType::UFO) {}
Teleported::Teleported() : Vehicle(VehicleType::Teleported) {}
Spacecraft::Spacecraft() : Vehicle(VehicleType::Spacecraft) {}

//parking lot
ParkingLot::ParkingLot(int n) : total_slots(n) {
    slots.resize(n);
    for (int i=0; i<n; i++) {
        slots[i].slot_number = i;
        slots[i].is_occupied = false;
    }
}
int ParkingLot::find_lot() const{
    for (int i=0; i<total_slots; i++) {
        if (!slots[i].is_occupied) return i;
    }
    return -1;
}
int ParkingLot::available_slots() const{
    int count=0;
    for (int i=0; i<total_slots; i++) {
        if (!slots[i].is_occupied) count++;
    }
    return count;
}
void ParkingLot::park(Vehicle* v) {
    if(int lot=find_lot(); lot!=-1){
        v->park(lot);
        v->arrive();
        slots[lot].is_occupied = true;
    }
    else std::cout << "No slots available" << "\n";
}
void ParkingLot::unpark(Vehicle* v) {
    int slot=v->unpark();
    slots[slot].is_occupied = false;
    v->depart();
}