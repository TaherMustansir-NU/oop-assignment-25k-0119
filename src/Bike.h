#pragma once

#include "Vehicle.h"
#include <string>

using namespace std;

class Bike : public Vehicle {
private:
    string bk_type;
    int cc_val;
    bool abs_flag;
    string f_type;
    int s_height;

public:
    Bike();
    Bike(const string& brand, const string& model, int year, double price,
         double mileage, const string& color, const string& bk_type, int cc_val,
         bool has_abs, const string& frame, int seat_h);
    Bike(const Bike& other);
    ~Bike() override;

    void display() const override;
    string getVehicleType() const override;
    double calculateDepreciation() const override;
    bool matchesKeyword(const string& keyword) override;
    bool matchesPriceRange(double min, double max) override;

    bool operator==(const Bike& other) const;

    friend bool compareBikes(const Bike& a, const Bike& b);

    const string& getBikeType() const { return bk_type; }
    int getEngineCC() const { return cc_val; }
    bool getHasABS() const { return abs_flag; }
    const string& getFrameType() const { return f_type; }
    int getSeatHeight() const { return s_height; }

    void setBikeType(const string& type) { bk_type = type; }
    void setEngineCC(int cc) { cc_val = cc; }
    void setHasABS(bool abs) { abs_flag = abs; }
    void setFrameType(const string& frame) { f_type = frame; }
    void setSeatHeight(int height) { s_height = height; }
};
