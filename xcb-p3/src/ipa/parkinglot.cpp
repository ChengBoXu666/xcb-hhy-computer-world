#ifdef __APPLE__
/* macos */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
/* windows & linux */
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <vector>
#include "parkinglot.h"

// basic vehicle
int Vehicle::cost_calc() const
{
    if ((departure_time - arrival_time) % (3600 / time_multiplier) == 0)
        return cost[static_cast<size_t>(type)] * (static_cast<int>(departure_time - arrival_time) % 3600);
    else
        return cost[static_cast<size_t>(type)] * (static_cast<int>(departure_time - arrival_time) % 3600 + 1);
}
Vehicle::Vehicle(VehicleType t) : type(t)
{
    vehicle_slot.slot_number = -1;
    vehicle_slot.is_occupied = false;
}
Vehicle::~Vehicle() = default;
void Vehicle::arrive() { time(&arrival_time); }
void Vehicle::depart() { time(&departure_time); }
void Vehicle::in_ticket() const
{
    std::cout << "IN TICKET" << "\n";
    std::cout << "Arrival Time: " << static_cast<int>(arrival_time) << "\n";
    std::cout << "Vehicle Type: " << vehicle_type[static_cast<size_t>(type)] << "\n";
    std::cout << "Slot" << vehicle_slot.slot_number + 1 << "\n";
}

void Vehicle::out_ticket() const
{
    std::cout << "OUT TICKET" << "\n";
    std::cout << "Departure Time: " << static_cast<int>(departure_time) << "\n";
    std::cout << "Total Time: " << static_cast<int>(departure_time - arrival_time) * time_multiplier << "\n";
    std::cout << "Vehicle Type: " << vehicle_type[static_cast<size_t>(type)] << "\n";
    std::cout << "Cost: $" << cost_calc() << "\n";
}
void Vehicle::park(int slot, int _draw_time,int _st)
{
    vehicle_slot.slot_number = slot;
    draw_time = _draw_time;
    stop_time = _st;
}
int Vehicle::unpark() const
{
    return vehicle_slot.slot_number+1;
}

Vec Vehicle::generate_route(std::vector<Vec> controlPoints, int n){
    static Vec point(0, 0);
    int numPoints = 10*(int)size(controlPoints);
    if (n > numPoints) return point;
    for (int i = 0; i <= n; ++i) {
        float t = (float)i / (float)numPoints;
        point = Vec::bezier(controlPoints, t);
    }
    return point;
}

std::vector<Vec> Vehicle::generate_in_control_points(int slot_number){
    float d = 4.0f / ((float)ParkingLot::slotnum() + 3.0f);
    std::vector<Vec> controlPoints;
    if (slot_number > ParkingLot::slotnum() / 2){
        int lower_slot_number = slot_number - ParkingLot::slotnum() / 2;
        controlPoints = {
            Vec(-1+1.5f*d/2,-1.2f),
            Vec(-1+1.5f*d/2,-0.3f),
            Vec(-1+1.5f*d/2,-0.2f),
            Vec(-1+1.5f*d/2,-0.2f),
            Vec(-1+1.5f*d/2+0.1f,-0.2f),
            Vec(-1+(1.5f*d+(float)(lower_slot_number)*d+d/2.0f)/2.0f,-0.2f),
            Vec(-1+1.5f*d+(float)(lower_slot_number)*d+d/2.0f,-0.2f),
        };
    }
    else{
        int upper_slot_number = ParkingLot::slotnum()/2-slot_number+1;
        controlPoints = {
            Vec(-1+1.5f*d/2,-1.2f),
            Vec(-1+1.5f*d/2,-0.3f),
            Vec(-1+1.5f*d/2,-0.2f),
            Vec(-1+1.5f*d/2,-0.2f),
            Vec(-1+1.5f*d/2+0.1f,-0.2f),
            Vec(0,-0.2f),
            Vec(1-1.5f*d/2-0.1f,-0.2f),
            Vec(1-1.5f*d/2,-0.2f),
            Vec(1-1.5f*d/2,-0.2f),
            Vec(1-1.5f*d/2,-0.1f),
            Vec(1-1.5f*d/2,0.1f),
            Vec(1-1.5f*d/2,0.2f),
            Vec(1-1.5f*d/2,0.2f),
            Vec(1-1.5f*d/2-0.1f,0.2f),
            Vec(1-((float)upper_slot_number*d+d/2.0f)/2.0f,0.2f),
            Vec(1-(float)upper_slot_number*d-d/2.0f,0.2f),
        };
    }
    return controlPoints;
}

std::vector<Vec> Vehicle::generate_back_control_points(int slot_number){
    float d = 4.0f / ((float)ParkingLot::slotnum() + 3.0f);
    std::vector<Vec> controlPoints;
    if (slot_number > ParkingLot::slotnum() / 2){
        int lower_slot_number = slot_number - ParkingLot::slotnum() / 2;
        controlPoints = {
            Vec(-1+1.5f*d+(float)(lower_slot_number)*d+d/2.0f,-0.2f),
            Vec(-1+1.5f*d+(float)(lower_slot_number-1)*d+d/2.0f-0.1f,-0.2f),
            Vec(-1+1.5f*d+(float)(lower_slot_number-1)*d+d/2.0f,-0.3f),
            Vec(-1+1.5f*d+(float)(lower_slot_number-1)*d+d/2.0f,-0.6f),
        };
    }
    else{
        int upper_slot_number = ParkingLot::slotnum()/2-slot_number+1;
        controlPoints = {
            Vec(1-(float)upper_slot_number*d-d/2.0f,0.2f),
            Vec(1-(float)(upper_slot_number-1)*d-d/2.0f+0.1f,0.2f),
            Vec(1-(float)(upper_slot_number-1)*d-d/2.0f,0.3f),
            Vec(1-(float)(upper_slot_number-1)*d-d/2.0f,0.6f),
        };
    }
    return controlPoints;
}

std::vector<Vec> Vehicle::generate_out_control_points(int slot_number){
    float d = 4.0f / ((float)ParkingLot::slotnum() + 3.0f);
    std::vector<Vec> controlPoints;
    if (slot_number > ParkingLot::slotnum() / 2){
        int lower_slot_number = slot_number - ParkingLot::slotnum() / 2;
        controlPoints = {
            Vec(-1+1.5f*d+(float)(lower_slot_number-1)*d+d/2.0f,-0.6f),
            Vec(-1+1.5f*d+(float)(lower_slot_number-1)*d+d/2.0f,-0.3f),
            Vec(-1+1.5f*d+(float)(lower_slot_number-1)*d+d/2.0f,-0.2f),
            Vec(-1+1.5f*d+(float)(lower_slot_number-1)*d+d/2.0f+0.1f,-0.2f),
            Vec(1-1.5f*d/2-0.1f,-0.2f),
            Vec(1-1.5f*d/2,-0.2f),
            Vec(1-1.5f*d/2,-0.2f),
            Vec(1-1.5f*d/2,-0.1f),
            Vec(1-1.5f*d/2,0.1f),
            Vec(1-1.5f*d/2,0.2f),
            Vec(1-1.5f*d/2,0.2f),
            Vec(1-1.5f*d/2-0.1f,0.2f),
            Vec(0,0.2f),
            Vec(-1+1.5f*d/2+0.1f,0.2f),
            Vec(-1+1.5f*d/2,0.2f),
            Vec(-1+1.5f*d/2,0.2f),
            Vec(-1+1.5f*d/2,0.3f),
            Vec(-1+1.5f*d/2,1.2f),
        };
    }
    else{
        int upper_slot_number = ParkingLot::slotnum()/2-slot_number+1;
        controlPoints = {
            Vec(1-(float)(upper_slot_number-1)*d-d/2.0f,0.6f),
            Vec(1-(float)(upper_slot_number-1)*d-d/2.0f,0.3f),
            Vec(1-(float)(upper_slot_number-1)*d-d/2.0f,0.2f),
            Vec(1-(float)(upper_slot_number-1)*d-d/2.0f-0.1f,0.2f),
            Vec(-1+1.5f*d/2+0.1f,0.2f),
            Vec(-1+1.5f*d/2,0.2f),
            Vec(-1+1.5f*d/2,0.2f),
            Vec(-1+1.5f*d/2,0.3f),
            Vec(-1+1.5f*d/2,1.2f),
        };
    }
    return controlPoints;
}

// parking lot
int ParkingLot::total_slots = 0;

ParkingLot::ParkingLot(int n)
{
    total_slots = n;
    slots.resize(static_cast<size_t>(total_slots));
    for (int i = 0; i < total_slots; i++)
    {
        slots[static_cast<size_t>(i)].slot_number = i + 1;
        slots[static_cast<size_t>(i)].is_occupied = false;
        slots[static_cast<size_t>(i)].length = 0.4f;
        slots[static_cast<size_t>(i)].width = 4.0f / ((float)total_slots + 3.0f);
        if (i + 1 <= (int)(total_slots / 2))
        {
            slots[static_cast<size_t>(i)].center = Vec(-0.1f + (float)(i + 2) * slots[static_cast<size_t>(i)].width, 0.6f);
        }
        else
        {
            slots[static_cast<size_t>(i)].center = Vec(-0.1f + (float)(i + 2 - (int)(total_slots / 2)) * slots[static_cast<size_t>(i)].width, -0.6f);
        }
    }
}

int ParkingLot::find_lot() const
{
    for (int i = 0; i < total_slots; i++)
    {
        if (!slots[static_cast<size_t>(i)].is_occupied)
            return i;
    }
    return -1;
}

int ParkingLot::available_slots() const
{
    int count = 0;
    for (int i = 0; i < total_slots; i++)
    {
        if (!slots[static_cast<size_t>(i)].is_occupied)
            count++;
    }
    return count;
}
void ParkingLot::park(Vehicle *v,int _d,int _st)
{
    int lot = find_lot();
    if (lot != -1)
    {
        v->park(lot,_d,_st);
        v->arrive();
        v->in_ticket();
        slots[static_cast<size_t>(lot)].is_occupied = true;
    }
    else
        std::cout << "No slots available" << "\n";
}

void ParkingLot::unpark(Vehicle *v)
{
    int slot = v->unpark();
    v->depart();
    v->out_ticket();
    slots[static_cast<size_t>(slot)].is_occupied = false;
    v->depart();
}
void ParkingLot::draw()
{
#ifndef HEADLESS
    float d = 4.0f / ((float)total_slots + 3.0f); // the width of each slot
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);

    glVertex2f(-1.0f + 1.5f * d, 0.8f);
    glVertex2f(1.0f, 0.8f);
    

    glVertex2f(-1.0f, 0.8f);
    glVertex2f(-1.0f, -0.8f);

    glVertex2f(-1.0f + 1.5f * d, -0.8f); // saving a gap for the entry
    glVertex2f(1.0f, -0.8f);

    glVertex2f(1.0f, -0.8f);
    glVertex2f(1.0f, 0.8f);
    // the boundary of the parking lot

    glVertex2f(-1.0f + 1.5f * d, 0.0f);
    glVertex2f(1.0f - 1.5f * d, 0.0f);
    // the horizontal middle line
    for (int i = 0; i < total_slots; ++i)
    {
        float y1 = 0.0f;
        (void)y1;
        if (i < total_slots / 2)
            y1 = 0.4f; // draw the slots seperating line above
        else
            y1 = -0.8f;

        glVertex2f(-1.0f + (1.5f + (float)(i % (total_slots / 2))) * d, y1 + 0.4f);
        glVertex2f(-1.0f + (1.5f + (float)(i % (total_slots / 2))) * d, y1);
    }
    glEnd();
    #endif
}


int ParkingLot::getnumslot()
{
    int num = 0;
    while (num < 12 || num > 22 || (num & 1) == 1)
    {
        std::cout << "please input how many slots(range:12-22)" << "\n";
        std::cout << "Remember: num should be even numbers!" << "\n";
        std::cin >> num;
    }
    num = num - num % 2;
    return num;
}

int ParkingLot::slotnum()
{
    return total_slots;
}
