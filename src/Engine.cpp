#include "Engine.h"

using namespace std;

Engine::Engine()
    : type("Unknown"), horsepower(0), displacement(0.0), fuelType("Petrol"),
      cylinders(0), transmissionType("Manual") {
}

Engine::Engine(const string& type, int horsepower, double displacement,
               const string& fuelType, int cylinders, const string& transmissionType)
    : type(type), horsepower(horsepower), displacement(displacement),
      fuelType(fuelType), cylinders(cylinders), transmissionType(transmissionType) {
}

Engine::Engine(const Engine& other)
    : type(other.type), horsepower(other.horsepower), displacement(other.displacement),
      fuelType(other.fuelType), cylinders(other.cylinders),
      transmissionType(other.transmissionType) {
}

Engine::~Engine() {
}

Engine& Engine::operator=(const Engine& other) {
    if (this != &other) {
        type = other.type;
        horsepower = other.horsepower;
        displacement = other.displacement;
        fuelType = other.fuelType;
        cylinders = other.cylinders;
        transmissionType = other.transmissionType;
    }
    return *this;
}

void Engine::display() const {
    cout << "Engine Type: " << type << "\n";
    cout << "Horsepower: " << horsepower << "\n";
    cout << "Displacement: " << displacement << "\n";
    cout << "Fuel Type: " << fuelType << "\n";
    cout << "Cylinders: " << cylinders << "\n";
    cout << "Transmission: " << transmissionType << "\n";
}

bool Engine::isHighPerformance() const {
    return horsepower >= 300;
}

int Engine::getFuelEfficiencyRating() const {
    if (horsepower <= 0) return 1;
    double ratio = displacement / horsepower;
    if (ratio < 0.015) return 5;
    if (ratio < 0.020) return 4;
    if (ratio < 0.025) return 3;
    if (ratio < 0.030) return 2;
    return 1;
}

int Engine::compareWith(const Engine& other) const {
    int thisScore = horsepower + (cylinders * 50);
    int otherScore = other.horsepower + (other.cylinders * 50);
    if (thisScore > otherScore) return 1;
    if (thisScore < otherScore) return -1;
    return 0;
}

bool Engine::operator==(const Engine& other) const {
    return type == other.type && displacement == other.displacement &&
           cylinders == other.cylinders;
}

Engine Engine::operator+(const Engine& other) const {
    Engine result(*this);
    if (other.horsepower > result.horsepower) {
        result.type = other.type;
        result.fuelType = other.fuelType;
        result.transmissionType = other.transmissionType;
    }
    result.horsepower = other.horsepower > result.horsepower ? other.horsepower : result.horsepower;
    result.displacement = other.displacement > result.displacement ? other.displacement : result.displacement;
    result.cylinders = other.cylinders > result.cylinders ? other.cylinders : result.cylinders;
    return result;
}

ostream& operator<<(ostream& os, const Engine& e) {
    os << e.type << ", " << e.horsepower << " HP, " << e.displacement << "L, "
       << e.fuelType << ", " << e.cylinders << " cyl, " << e.transmissionType;
    return os;
}
