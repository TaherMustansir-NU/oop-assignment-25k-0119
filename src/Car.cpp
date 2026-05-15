#include "Car.h"

using namespace std;

Car::Car() : Vehicle(), eng(), ins(), b_style("Unknown") {
}

Car::Car(const string& brand, const string& model, int year, double price,
         double mileage, const string& color, const Engine& eng,
         const Insurance& ins, const string& b_style)
    : Vehicle(brand, model, year, price, mileage, color), eng(eng),
      ins(ins), b_style(b_style) {
}

Car::Car(const Car& other)
    : Vehicle(other), eng(other.eng), ins(other.ins),
      b_style(other.b_style) {
}

Car::~Car() {
}

void Car::display() const {
    cout << "Car Details\n";
    cout << "Brand: " << getBrand() << "\n";
    cout << "Model: " << getModel() << "\n";
    cout << "Year: " << getYear() << "\n";
    cout << "Price: " << getPrice() << "\n";
    cout << "Mileage: " << getMileage() << "\n";
    cout << "Color: " << getColor() << "\n";
    cout << "Body Style: " << b_style << "\n";
    cout << "Engine\n";
    eng.display();
    cout << "Insurance\n";
    ins.display();
}

string Car::getVehicleType() const {
    return "Car";
}

double Car::calculateDepreciation() const {
    int currentYear = 2026;
    int age = currentYear - getYear();
    if (age <= 0) return 0.0;
    double depreciationRate = 0.15;
    return getPrice() * depreciationRate * age;
}

bool Car::matchesKeyword(const string& keyword) {
    if (keyword.empty()) return true;
    if (getBrand().find(keyword) != string::npos) return true;
    if (getModel().find(keyword) != string::npos) return true;
    if (getColor().find(keyword) != string::npos) return true;
    if (b_style.find(keyword) != string::npos) return true;
    return false;
}

bool Car::matchesPriceRange(double min, double max) {
    double price = getPrice();
    return price >= min && price <= max;
}

Car Car::operator+(const Car& other) const {
    Car combined(*this);
    combined.setBrand(getBrand() + "/" + other.getBrand());
    combined.setModel(getModel() + "/" + other.getModel());
    combined.setYear(getYear() > other.getYear() ? getYear() : other.getYear());
    combined.setPrice((getPrice() + other.getPrice()) / 2.0);
    combined.setMileage((getMileage() + other.getMileage()) / 2.0);
    if (getColor() != other.getColor()) {
        combined.setColor("Mixed");
    }
    combined.eng = eng + other.eng;
    combined.b_style = b_style + "/" + other.b_style;
    return combined;
}
