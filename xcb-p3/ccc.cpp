//#include "ccc.h"
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
    
    Vehicle(std::string type, double rate, double parkDuration, std::string spot) : vehicleType(type), parkingRate(rate), duration(parkDuration), parkingSpot(spot)
    {
        arrivalTime = std::time(nullptr);
    }
    virtual double calculateParkingFee()
    {
        return duration * parkingRate;
    }
    virtual void displayTicket(bool isDeparture = false)
    {
        if (!isDeparture)
        {
            std::cout << "Vehicle Type: " << vehicleType << std::endl;
            std::cout << "Arrival Time: " << std::ctime(&arrivalTime);
            std::cout << "Parking Spot: " << parkingSpot << std::endl;
            std::cout << std::endl;
        }
        else
        {
            double parkingFee = calculateParkingFee();
            std::cout << "Vehicle Type: " << vehicleType << std::endl;
            std::cout << "Parking Duration: " << duration << " seconds" << std::endl;
            std::cout << "Parking Fee: " << parkingFee << std::endl;
            std::cout << "Parking Spot: " << parkingSpot << std::endl;
            std::cout << std::endl;
        }
    }

    virtual ~Vehicle() {}
};

class Van : public Vehicle
{
public:
    Van(double parkDuration, std::string spot) : Vehicle("Van", 3, parkDuration, spot) {}

    void displayTicket(bool isDeparture = false) override
    {
        if (!isDeparture)
        {
            std::cout << "Van Ticket(in): \n";
            Vehicle::displayTicket(isDeparture);
        }
        else
        {
            std::cout << "Van Ticket(out): \n";
            Vehicle::displayTicket(isDeparture);
        }
    }
};

class Bicycle : public Vehicle
{
public:
    Bicycle(double parkDuration, std::string spot) : Vehicle("Bicycle", 0.5, parkDuration, spot) {}

    void displayTicket(bool isDeparture = false) override
    {
        if (!isDeparture)
        {
            std::cout << "Bicycle Ticket(in): \n";
            Vehicle::displayTicket(isDeparture);
        }
        else
        {
            std::cout << "Bicycle Ticket(out): \n";
            Vehicle::displayTicket(isDeparture);
        }
    }
};

class Car : public Vehicle
{
public:
    Car(double parkDuration, std::string spot) : Vehicle("Car", 2, parkDuration, spot) {}

    void displayTicket(bool isDeparture = false) override
    {
        if (!isDeparture)
        {
            std::cout << "Car Ticket(in): \n";
            Vehicle::displayTicket(isDeparture);
        }
        else
        {
            std::cout << "Car Ticket(out): \n";
            Vehicle::displayTicket(isDeparture);
        }
    }
};

class Motorbike : public Vehicle
{
public:
    Motorbike(double parkDuration, std::string spot) : Vehicle("Motorbike", 1, parkDuration, spot) {}

    void displayTicket(bool isDeparture = false) override
    {
        if (!isDeparture)
        {
            std::cout << "Motorbike Ticket(in): \n";
            Vehicle::displayTicket(isDeparture);
        }
        else
        {
            std::cout << "Motorbike Ticket(out): \n";
            Vehicle::displayTicket(isDeparture);
        }
    }
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
    ParkingLot(int floor1SpotsCount, int floor2SpotsCount)
        : floor1Capacity(floor1SpotsCount), floor2Capacity(floor2SpotsCount), totalVehicles(0)
    {
        floor1Spots.resize(floor1SpotsCount, false);
        floor2Spots.resize(floor2SpotsCount, false);
    }

    std::string parkVehicle(Vehicle *vehicle)
    {    
        for (int i = 0; i < floor1Capacity; i++)
        {
            if (!floor1Spots[i])
            {
                floor1Spots[i] = true;
                totalVehicles++;
                return "Floor1:" + std::to_string(i + 1);
            }
        }
        
        for (int i = 0; i < floor2Capacity; i++)
        {
            if (!floor2Spots[i])
            {
                floor2Spots[i] = true;
                totalVehicles++;
                return "Floor2:" + std::to_string(i + 1);
            }
        }
        return "";
    }

    void leaveVehicle(std::string parkingSpot)
    {
        if (parkingSpot.find("Floor1") != std::string::npos)
        {
            int spot = std::stoi(parkingSpot.substr(7)) - 1;
            floor1Spots[spot] = false;
            totalVehicles--;
        }
        else if (parkingSpot.find("Floor2") != std::string::npos)
        {
            int spot = std::stoi(parkingSpot.substr(7)) - 1;
            floor2Spots[spot] = false;
            totalVehicles--;
        }
    }

    bool isFull()
    {
        std::cout << "Total Vehicles: " << totalVehicles << std::endl;
        if (totalVehicles >= floor1Capacity + floor2Capacity)
            return true;
        return false;
    }

    int getTotalVehicles() const
    {
        return totalVehicles;
    }

    void reset()
    {
        std::fill(floor1Spots.begin(), floor1Spots.end(), false);
        std::fill(floor2Spots.begin(), floor2Spots.end(), false);
        totalVehicles = 0;
    }
};

void simulateVehicleParking(ParkingLot &parkinglot, Vehicle *vehicle)
{
    std::string parkingSpot = parkinglot.parkVehicle(vehicle);
    parkinglot.totalVehicles--;
    vehicle->displayTicket(false); 
    double parkingDuration = vehicle->duration;

    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(parkingDuration))); 
    parkinglot.leaveVehicle(parkingSpot);
    vehicle->displayTicket(true); 
    delete vehicle; 
}

int main()
{
    srand(time(0));
    ParkingLot parkinglot(8, 6);
    auto getRandomDuration = []() -> double
    {
        return rand() % 5 + 5; 
    };

    auto getRandomVehicle = [&]() -> Vehicle *
    {
        int randType = rand() % 4;                         
        double duration = getRandomDuration();            
        std::string spot = parkinglot.parkVehicle(nullptr); 
        switch (randType)
        {
        case 0:
            return new Van(duration, spot);
            break;
        case 1:
            return new Bicycle(duration, spot);
            break;
        case 2:
            return new Car(duration, spot);
            break;
        case 3:
            return new Motorbike(duration, spot);
            break;
        default:
            return nullptr;
        }
    };

    for (int i = 0; i < 10; i++)
    {
        if (!parkinglot.isFull())
        {
            Vehicle *vehicle = getRandomVehicle();
            std::thread parkingThread([&parkinglot, vehicle]()
                                      { simulateVehicleParking(parkinglot, vehicle); });

            parkingThread.detach();
        }
        else
        {
            std::cout << "Parking lot is full! No more vehicles can enter.\n";
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    std::this_thread::sleep_for(std::chrono::seconds(30));

    return 0;
}