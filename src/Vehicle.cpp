#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle()
    : brand("Unknown"), model("Unknown"), year(0), price(0.0), mileage(0.0), color("Unknown") {
}

Vehicle::Vehicle(const string& brand, const string& model, int year, double price,
                 double mileage, const string& color)
    : brand(brand), model(model), year(year), price(price), mileage(mileage), color(color) {
}

Vehicle::Vehicle(const Vehicle& other)
    : brand(other.brand), model(other.model), year(other.year), price(other.price),
      mileage(other.mileage), color(other.color) {
}

Vehicle::~Vehicle() {
}

bool Vehicle::compareTo(const Vehicle& other) const {
    return price < other.price;
}

bool Vehicle::operator==(const Vehicle& other) const {
    return brand == other.brand && model == other.model && year == other.year;
}

bool Vehicle::operator<(const Vehicle& other) const {
    return price < other.price;
}

ostream& operator<<(ostream& os, const Vehicle& v) {
    os << v.brand << " " << v.model << " (" << v.year << ") - Rs. " << v.price;
    return os;
}
