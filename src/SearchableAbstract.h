#pragma once

#include <string>

using namespace std;

class ISearchable {
public:
    virtual bool matchesKeyword(const string& keyword) = 0;
    virtual bool matchesPriceRange(double minPrice, double maxPrice) = 0;
    virtual ~ISearchable() {}
};
