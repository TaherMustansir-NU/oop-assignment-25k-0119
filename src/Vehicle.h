#pragma once

#include "DisplayableAbstract.h"
#include "SearchableAbstract.h"
#include <iostream>
#include <string>

using namespace std;

class Vehicle : public IDisplayable, public ISearchable {
private:
    string brand;
    string model;
    int year;
    double price;
    double mileage;
    string color;

public:
    Vehicle();
    Vehicle(const string& brand, const string& model, int year, double price,
            double mileage, const string& color);
    Vehicle(const Vehicle& other);
    virtual ~Vehicle();

    virtual void display() const = 0;
    virtual string getVehicleType() const = 0;
    virtual double calculateDepreciation() const = 0;
    virtual bool matchesKeyword(const string& keyword) = 0;
    virtual bool matchesPriceRange(double min, double max) = 0;
    virtual bool compareTo(const Vehicle& other) const;

    bool operator==(const Vehicle& other) const;
    bool operator<(const Vehicle& other) const;

    friend ostream& operator<<(ostream& os, const Vehicle& v);

    const string& getBrand() const { return brand; }
    const string& getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    double getMileage() const { return mileage; }
    const string& getColor() const { return color; }

    void setBrand(const string& b) { brand = b; }
    void setModel(const string& m) { model = m; }
    void setYear(int y) { year = y; }
    void setPrice(double p) { price = p; }
    void setMileage(double m) { mileage = m; }
    void setColor(const string& c) { color = c; }
};
