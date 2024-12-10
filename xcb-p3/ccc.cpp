#include "ccc.h"
Vehicle::Vehicle(std::string type, double fee, double parkDuration, std::string spot) : vehicleType(type), parkingFee(fee), duration(parkDuration), parkingSpot(spot)
{
    arrivalTime = std::time(nullptr);
}
double Vehicle::calculateParkingFee()
{
    return duration * parkingFee;
}
double Vehicle::getDuration(Vehicle *vehicle)
{
    return vehicle->duration;
}
void Vehicle::display(bool isDeparture = false)
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
        double parkinCost = calculateParkingFee();
        std::cout << "Vehicle Type: " << vehicleType << std::endl;
        std::cout << "Parking Duration: " << duration << " seconds" << std::endl;
        std::cout << "Parking Fee: " << parkinCost << std::endl;
        std::cout << std::endl;
    }
}

Vehicle::~Vehicle() {}

Van::Van(std::string spot) : Vehicle("Van", 3,(double)(rand()%5+20), spot) {}

void Van::display(bool isDeparture = false)
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

Bicycle::Bicycle(std::string spot) : Vehicle("Bicycle", 0.5, (double)(rand()%5+20), spot) {}

void Bicycle::display(bool isDeparture = false)
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

Car::Car(std::string spot) : Vehicle("Car", 2, (double)(rand()%5+20), spot) {}

void Car::display(bool isDeparture = false)
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

Motorbike::Motorbike(std::string spot) : Vehicle("Motorbike", 1, (double)(rand()%5+20), spot) {}

void Motorbike::display(bool isDeparture = false)
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

ParkingLot::ParkingLot(int floor1SpotsCount, int floor2SpotsCount)
    : floor1Capacity(floor1SpotsCount), floor2Capacity(floor2SpotsCount), total(0)
{
    floor1Spots.resize(floor1SpotsCount, false);
    floor2Spots.resize(floor2SpotsCount, false);
}

std::string ParkingLot::parkVehicle(Vehicle *vehicle)
{
    for (int i = 0; i < floor1Capacity; i++)
    {
        if (!floor1Spots[i])
        {
            floor1Spots[i] = true;
            total++;
            return "Floor1:" + std::to_string(i + 1);
        }
    }

    for (int i = 0; i < floor2Capacity; i++)
    {
        if (!floor2Spots[i])
        {
            floor2Spots[i] = true;
            total++;
            return "Floor2:" + std::to_string(i + 1);
        }
    }
    (void)vehicle;
    return "";
}

void ParkingLot::freeVehicle(std::string parkingSpot)
{
    if (parkingSpot.find("Floor1") != std::string::npos)
    {
        int spot = std::stoi(parkingSpot.substr(7)) - 1;
        floor1Spots[spot] = false;
        total--;
    }
    else if (parkingSpot.find("Floor2") != std::string::npos)
    {
        int spot = std::stoi(parkingSpot.substr(7)) - 1;
        floor2Spots[spot] = false;
        total--;
    }
}

bool ParkingLot::isFull()
{
    if (total >= (floor1Capacity + floor2Capacity)*2)
        return true;
    return false;
}

void Parking(ParkingLot &parkinglot, Vehicle *vehicle)
{
    std::string parkingSpot = parkinglot.parkVehicle(vehicle);
    vehicle->display(false);
    double parkingDuration = vehicle->getDuration(vehicle);

    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(parkingDuration)));
    parkinglot.freeVehicle(parkingSpot);
    vehicle->display(true);
    delete vehicle;
}

int main()
{
     srand((unsigned int)time(NULL));

    ParkingLot parkinglot(8, 6);

    auto getVehicle = [&]() -> Vehicle *
    {
        int randType = rand() % 4;
        std::string spot = parkinglot.parkVehicle(nullptr);
        switch (randType)
        {
        case 0:
            return new Van(spot);
            break;
        case 1:
            return new Bicycle(spot);
            break;
        case 2:
            return new Car(spot);
            break;
        case 3:
            return new Motorbike(spot);
            break;
        default:
            return nullptr;
        }
    };

    for (int i = 0; i < 10; i++)
    {
        if (!parkinglot.isFull())
        {
            Vehicle *vehicle = getVehicle();
            std::thread parkingThread([&parkinglot, vehicle]()
                                      { Parking(parkinglot, vehicle); });

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