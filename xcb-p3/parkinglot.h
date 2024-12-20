#ifndef _PARKINGLOTH
#define _PARKINGLOTH
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <array>

using slot = struct _slot {
    int slot_number;
    bool is_occupied;
};

static const int time_multiplier = 60;
static const std::array<int, 4> cost = {2, 1, 3, 1};
static const std::array<std::string, 4> vehicle_type = {"Car", "UFO", "Teleported", "Spacecraft"};

enum class VehicleType {
    Car,
    UFO,
    Teleporter,
    Spacecraft
};

class Vehicle {
    protected:
        VehicleType type;
        slot vehicle_slot;
        time_t arrival_time=0;
        time_t departure_time=0;
        std::string plate;
        int cost_calc() const;
    public:
        explicit Vehicle(VehicleType t);
        virtual ~Vehicle();
        void arrive();
        void depart();
        void in_ticket() const;
        void out_ticket() const;
        void park(int slot);
        int unpark() const;
};

class ParkingLot {
    private:
        std::vector<slot> slots;
        int total_slots;
    public:
        explicit ParkingLot(int n);
        int find_lot() const;
        int available_slots() const;
        void park(Vehicle* v);
        void unpark(Vehicle* v);
        void draw() const;
};

#endif