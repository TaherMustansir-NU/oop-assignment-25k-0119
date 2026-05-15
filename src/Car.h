#pragma once

#include "Vehicle.h"
#include "Engine.h"
#include "Insurance.h"
#include <string>

using namespace std;

class Car : public Vehicle {
private:
    Engine eng;
    Insurance ins;
    string b_style;

public:
    Car();
    Car(const string& brand, const string& model, int year, double price,
        double mileage, const string& color, const Engine& eng,
        const Insurance& ins, const string& body);
    Car(const Car& other);
    ~Car() override;

    void display() const override;
    string getVehicleType() const override;
    double calculateDepreciation() const override;
    bool matchesKeyword(const string& keyword) override;
    bool matchesPriceRange(double min, double max) override;

    Car operator+(const Car& other) const;

    const Engine& getEngine() const { return eng; }
    const Insurance& getInsurance() const { return ins; }
    const string& getBodyStyle() const { return b_style; }

    void setEngine(const Engine& eng) { this->eng = eng; }
    void setInsurance(const Insurance& ins) { this->ins = ins; }
    void setBodyStyle(const string& style) { b_style = style; }
};

