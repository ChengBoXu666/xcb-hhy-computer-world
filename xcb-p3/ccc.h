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
    double parkingRate;
    std::time_t arrivalTime;
    std::string parkingSpot;

public:
    double duration;
    Vehicle(std::string type, double rate, double parkDuration, std::string spot);
    virtual ~Vehicle();

    virtual double calculateParkingFee();
    virtual void displayTicket(bool isDeparture);
};

class Van : public Vehicle
{
public:
    Van(double parkDuration, std::string spot);
    void displayTicket(bool isDeparture) override;
};

class Bicycle : public Vehicle
{
public:
    Bicycle(double parkDuration, std::string spot);
    void displayTicket(bool isDeparture) override;
};

class Car : public Vehicle
{
public:
    Car(double parkDuration, std::string spot);
    void displayTicket(bool isDeparture) override;
};

class Motorbike : public Vehicle
{
public:
    Motorbike(double parkDuration, std::string spot);
    void displayTicket(bool isDeparture) override;
};

class ParkingLot
{
private:
    std::vector<bool> floor1Spots;
    std::vector<bool> floor2Spots;
    int floor1Capacity;
    int floor2Capacity;

public:
    int totalVehicles;
    ParkingLot(int floor1SpotsCount, int floor2SpotsCount);
    std::string parkVehicle(Vehicle *vehicle);
    void leaveVehicle(std::string parkingSpot);
    bool isFull();
    int getTotalVehicles() const;
    void reset();
};

void simulateVehicleParking(ParkingLot &parkinglot, Vehicle *vehicle);

#endif
