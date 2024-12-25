#ifndef PARKINGLOT_H
#define PARKINGLOT_H
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <array>
#include "vec.h"

using slot = struct _slot {
    int slot_number;
    bool is_occupied;
    float length;
    float width;
    Vec center;
};

static const int time_multiplier = 60;
static const std::array<int, 4> cost = {2, 1, 3, 1};
static const std::array<std::string, 4> vehicle_type = {"Car", "UFO", "Teleporter", "Spacecraft"};

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
        int draw_time=0;
        int stop_time=0;
    public:
        explicit Vehicle(VehicleType t);
        virtual ~Vehicle();
        void arrive();
        void depart();
        std::vector<Vec> generate_in_control_points(int slot_number);
        std::vector<Vec> generate_back_control_points(int slot_number);
        std::vector<Vec> generate_out_control_points(int slot_number);
        Vec generate_route(std::vector<Vec> controlPoints, int n);
        void in_ticket() const;
        void out_ticket() const;
        void park(int slot,int _d,int _st);
        int unpark() const;
        VehicleType gettype() const { return type; }
        int get_draw_time() const { return draw_time; }
        int get_stop_time() const { return stop_time; }
        slot get_slot() const { return vehicle_slot; }
};

class ParkingLot {
    private:
        std::vector<slot> slots;
        static int total_slots;
    public:
        explicit ParkingLot(int n=getnumslot());
        int find_lot() const;
        int available_slots() const;
        void park(Vehicle* v,int _d,int _st);
        void unpark(Vehicle* v);
        void draw();
        static int getnumslot();//prompt the user to input how many slots they want.
        static int slotnum();
};

class pole{
    private:
        Vec start;
        Vec end;
        float d;
    public:
        pole(Vec _s,float _d);
        void pole_move(float* pole_switch);
        void pole_draw() const;
};

#endif
