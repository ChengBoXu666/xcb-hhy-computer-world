#ifndef PMS_H
#define PMS_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
typedef struct _result{
    int n;
    int floor1;
    int floor2;
    int ishelp;
} Result;
class Vehicle
{
private:
    std::string vehicleType;
    double parkingFee;
    double duration;
    std::string parkingSpot;
    std::time_t arrivalTime;

public:
    Vehicle(std::string type, double fee, double parkDuration, std::string spot);
    virtual ~Vehicle();

    double getDuration() const; 
    virtual double calculateParkingFee();
    virtual void display(bool isDeparture);


    std::string getVehicleType() const { return vehicleType; }
    double getParkingFee() const { return parkingFee; }
    double getDurationValue() const { return duration; }
    std::string getParkingSpot() const { return parkingSpot; }
    std::time_t getArrivalTime() const { return arrivalTime; }


    void setVehicleType(const std::string &type) { vehicleType = type; }
    void setParkingFee(double fee) { parkingFee = fee; }
    void setDuration(double dur) { duration = dur; }
    void setParkingSpot(const std::string &spot) { parkingSpot = spot; }
    void setArrivalTime(std::time_t time) { arrivalTime = time; }
};

class Van : public Vehicle
{
public:
    explicit Van(std::string spot);
    void display(bool isDeparture) override;
};

class Bicycle : public Vehicle
{
public:
    explicit Bicycle(std::string spot);
    void display(bool isDeparture) override;
};

class Car : public Vehicle
{
public:
    explicit Car(std::string spot);
    void display(bool isDeparture) override;
};

class Motorbike : public Vehicle
{
public:
    explicit Motorbike(std::string spot);
    void display(bool isDeparture) override;
};

class Parkinglot
{
private:
    std::vector<bool> floor1Spots;
    std::vector<bool> floor2Spots;
    int floor1Capacity;
    int floor2Capacity;
    int total;

public:
    Parkinglot(int floor1SpotsCount, int floor2SpotsCount);
    std::string parkVehicle(Vehicle *vehicle);
    void freeVehicle(std::string parkingSpot);
    bool isFull();
};

void Parking(Parkinglot *parkinglot, Vehicle *vehicle);
Result inputing(int argc, char *argv[]);
#endif