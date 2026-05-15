#include "Bike.h"

using namespace std;

Bike::Bike()
    : Vehicle(), bk_type("Standard"), cc_val(0), abs_flag(false), f_type("Standard"),
      s_height(0) {
}

Bike::Bike(const string& brand, const string& model, int year, double price,
           double mileage, const string& color, const string& bk_type, int cc_val,
           bool abs_flag, const string& f_type, int s_height)
    : Vehicle(brand, model, year, price, mileage, color), bk_type(bk_type),
      cc_val(cc_val), abs_flag(abs_flag), f_type(f_type), s_height(s_height) {
}

Bike::Bike(const Bike& other)
    : Vehicle(other), bk_type(other.bk_type), cc_val(other.cc_val),
      abs_flag(other.abs_flag), f_type(other.f_type), s_height(other.s_height) {
}

Bike::~Bike() {
}

void Bike::display() const {
    cout << "Bike Details\n";
    cout << "Brand: " << getBrand() << "\n";
    cout << "Model: " << getModel() << "\n";
    cout << "Year: " << getYear() << "\n";
    cout << "Price: " << getPrice() << "\n";
    cout << "Mileage: " << getMileage() << "\n";
    cout << "Color: " << getColor() << "\n";
    cout << "Bike Type: " << bk_type << "\n";
    cout << "Engine CC: " << cc_val << "\n";
    cout << "ABS: " << (abs_flag ? "Yes" : "No") << "\n";
    cout << "Frame Type: " << f_type << "\n";
    cout << "Seat Height: " << s_height << "\n";
}

string Bike::getVehicleType() const {
    return "Bike";
}

double Bike::calculateDepreciation() const {
    int currentYear = 2026;
    int age = currentYear - getYear();
    if (age <= 0) return 0.0;
    double depreciationRate = 0.20;
    return getPrice() * depreciationRate * age;
}

bool Bike::matchesKeyword(const string& keyword) {
    if (keyword.empty()) return true;
    if (getBrand().find(keyword) != string::npos) return true;
    if (getModel().find(keyword) != string::npos) return true;
    if (getColor().find(keyword) != string::npos) return true;
    if (bk_type.find(keyword) != string::npos) return true;
    if (f_type.find(keyword) != string::npos) return true;
    return false;
}

bool Bike::matchesPriceRange(double min, double max) {
    double price = getPrice();
    return price >= min && price <= max;
}

bool Bike::operator==(const Bike& other) const {
    return getBrand() == other.getBrand() && getModel() == other.getModel() &&
           cc_val == other.cc_val;
}

bool compareBikes(const Bike& a, const Bike& b) {
    return a.getPrice() < b.getPrice() && a.cc_val > b.cc_val;
}
