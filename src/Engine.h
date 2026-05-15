#pragma once

#include <iostream>
#include <string>

using namespace std;

class Engine {
private:
    string type;
    int horsepower;
    double displacement;
    string fuelType;
    int cylinders;
    string transmissionType;

public:
    Engine();
    Engine(const string& type, int horsepower, double displacement,
           const string& fuelType, int cylinders, const string& transmissionType);
    Engine(const Engine& other);
    ~Engine();

    Engine& operator=(const Engine& other);

    void display() const;
    bool isHighPerformance() const;
    int getFuelEfficiencyRating() const;
    int compareWith(const Engine& other) const;

    bool operator==(const Engine& other) const;
    Engine operator+(const Engine& other) const;
    friend ostream& operator<<(ostream& os, const Engine& e);

    const string& getType() const { return type; }
    int getHorsepower() const { return horsepower; }
    double getDisplacement() const { return displacement; }
    const string& getFuelType() const { return fuelType; }
    int getCylinders() const { return cylinders; }
    const string& getTransmissionType() const { return transmissionType; }

    void setType(const string& t) { type = t; }
    void setHorsepower(int hp) { horsepower = hp; }
    void setDisplacement(double disp) { displacement = disp; }
    void setFuelType(const string& fuel) { fuelType = fuel; }
    void setCylinders(int cyl) { cylinders = cyl; }
    void setTransmissionType(const string& trans) { transmissionType = trans; }
};

