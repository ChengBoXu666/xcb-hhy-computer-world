#include <iostream>
#include <string>
#include "pms.h"

Vehicle::Vehicle(const std::string type, double fee, double parkDuration, std::string spot)
    : vehicleType(type), parkingFee(fee), duration(parkDuration), parkingSpot(spot), arrivalTime(std::time(nullptr)) {}

Vehicle::~Vehicle() {}

double Vehicle::calculateParkingFee()
{
    return duration * parkingFee;
}

double Vehicle::getDuration() const
{
    return duration;
}

void Vehicle::display(bool isDeparture)
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
        double parkingCost = calculateParkingFee();
        std::cout << "Vehicle Type: " << vehicleType << std::endl;
        std::cout << "Parking Duration: " << duration << " seconds" << std::endl;
        std::cout << "Parking Fee: " << parkingCost << "Yuan" << std::endl;
        std::cout << std::endl;
    }
}

Van::Van(const std::string spot) : Vehicle("Van", 3, static_cast<double>(rand() % 5 + 10), spot) {}

void Van::display(bool isDeparture)
{
    if (!isDeparture)
    {
        std::cout << "Van Ticket(in): \n";
        Vehicle::display(isDeparture);
    }
    else
    {
        std::cout << "Van Ticket(out): \n";
        Vehicle::display(isDeparture);
    }
}

Bicycle::Bicycle(const std::string spot) : Vehicle("Bicycle", 0.5, static_cast<double>(rand() % 5 + 10), spot) {}

void Bicycle::display(bool isDeparture)
{
    if (!isDeparture)
    {
        std::cout << "Bicycle Ticket(in): \n";
        Vehicle::display(isDeparture);
    }
    else
    {
        std::cout << "Bicycle Ticket(out): \n";
        Vehicle::display(isDeparture);
    }
}

Car::Car(const std::string spot) : Vehicle("Car", 2, static_cast<double>(rand() % 5 + 10), spot) {}

void Car::display(bool isDeparture)
{
    if (!isDeparture)
    {
        std::cout << "Car Ticket(in): \n";
        Vehicle::display(isDeparture);
    }
    else
    {
        std::cout << "Car Ticket(out): \n";
        Vehicle::display(isDeparture);
    }
}

Motorbike::Motorbike(const std::string spot) : Vehicle("Motorbike", 1, static_cast<double>(rand() % 5 + 10), spot) {}

void Motorbike::display(bool isDeparture)
{
    if (!isDeparture)
    {
        std::cout << "Motorbike Ticket(in): \n";
        Vehicle::display(isDeparture);
    }
    else
    {
        std::cout << "Motorbike Ticket(out): \n";
        Vehicle::display(isDeparture);
    }
}

Parkinglot::Parkinglot(int floor1SpotsCount, int floor2SpotsCount)
    : floor1Capacity(floor1SpotsCount), floor2Capacity(floor2SpotsCount), total(0)
{
    floor1Spots.resize(static_cast<size_t>(floor1SpotsCount), false);
    floor2Spots.resize(static_cast<size_t>(floor2SpotsCount), false);
}

std::string Parkinglot::parkVehicle(Vehicle *vehicle)
{
    for (int i = 0; i < floor1Capacity; i++)
    {
        if (!floor1Spots[static_cast<size_t>(i)])
        {
            floor1Spots[static_cast<size_t>(i)] = true;
            total++;
            return "Floor1:" + std::to_string(i + 1);
        }
    }

    for (int i = 0; i < floor2Capacity; i++)
    {
        if (!floor2Spots[static_cast<size_t>(i)])
        {
            floor2Spots[static_cast<size_t>(i)] = true;
            total++;
            return "Floor2:" + std::to_string(i + 1);
        }
    }
    (void)vehicle;
    return "";
}

void Parkinglot::freeVehicle(std::string parkingSpot)
{
    if (parkingSpot.find("Floor1") != std::string::npos)
    {
        int spot = std::stoi(parkingSpot.substr(7)) - 1;
        floor1Spots[static_cast<size_t>(spot)] = false;
        total--;
    }
    else if (parkingSpot.find("Floor2") != std::string::npos)
    {
        int spot = std::stoi(parkingSpot.substr(7)) - 1;
        floor2Spots[static_cast<size_t>(spot)] = false;
        total--;
    }
}

bool Parkinglot::isFull()
{
    return total >= (floor1Capacity + floor2Capacity) * 2;
}

void Parking(Parkinglot *parkinglot, Vehicle *vehicle)
{
    std::string parkingSpot = parkinglot->parkVehicle(vehicle);
    vehicle->display(false);
    double parkingDuration = vehicle->getDuration();

    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(parkingDuration)));
    parkinglot->freeVehicle(parkingSpot);
    vehicle->display(true);
    delete vehicle;
}

int main(int argc, char *argv[])
{
    Result result = inputing(argc, argv);
    if (result.ishelp==1) return 0;
    int n=result.n;
    int floor1=result.floor1;
    int floor2=result.floor2;
    srand(static_cast<unsigned int>(time(NULL)));

    Parkinglot parkinglot(floor1, floor2);

    auto getVehicle = [&]() -> Vehicle *
    {
        int randType = rand() % 4;
        std::string spot = parkinglot.parkVehicle(nullptr);
        switch (randType)
        {
        case 0:
            return new Van(spot);
        case 1:
            return new Bicycle(spot);
        case 2:
            return new Car(spot);
        case 3:
            return new Motorbike(spot);
        default:
            return nullptr;
        }
    };

    for (int i = 0; i < n; i++)
    {
        if (!parkinglot.isFull())
        {
            Vehicle *vehicle = getVehicle();
            std::thread parkingThread([&parkinglot, vehicle]()
                                      { Parking(&parkinglot, vehicle); });

            parkingThread.detach();
        }
        else
        {
            std::cout << "Parking lot is full! No more vehicles can enter.\n";
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}