#pragma once

using namespace std;

class IDisplayable {
public:
    virtual void display() const = 0;
    virtual ~IDisplayable() {}
};
