#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>

class Vehicle
{
protected:
    std::string vehicleType;
    double parkingFee;
    std::time_t arrivalTime;
    double duration;
    std::string parkingSpot;
public:
    Vehicle(std::string type, double fee, double parkDuration, std::string spot);
    virtual ~Vehicle();
    double getDuration(Vehicle *vehicle);
    virtual double calculateParkingFee();
    virtual void display(bool isDeparture);
};

class Van : public Vehicle
{
public:
    Van(std::string spot);
    void display(bool isDeparture) override;
};

class Bicycle : public Vehicle
{
public:
    Bicycle(std::string spot);
    void display(bool isDeparture) override;
};

class Car : public Vehicle
{
public:
    Car(std::string spot);
    void display(bool isDeparture) override;
};

class Motorbike : public Vehicle
{
public:
    Motorbike(std::string spot);
    void display(bool isDeparture) override;
};

class ParkingLot
{
private:
    std::vector<bool> floor1Spots;
    std::vector<bool> floor2Spots;
    int floor1Capacity;
    int floor2Capacity;
    int total;
public:
    ParkingLot(int floor1SpotsCount, int floor2SpotsCount);
    std::string parkVehicle(Vehicle *vehicle);
    void freeVehicle(std::string parkingSpot);
    bool isFull();
};

void Parking(ParkingLot &parkinglot, Vehicle *vehicle);

#endif
