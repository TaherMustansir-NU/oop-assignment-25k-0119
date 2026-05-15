#pragma once

#include "SearchableAbstract.h"
#include <string>

using namespace std;

class Vehicle;
class Seller;

class Listing : public ISearchable {
private:
    int listingId;
    Vehicle* vehicle;
    Seller* s_obj;
    string title;
    string description;
    bool isApproved;
    string datePosted;

    static int listingCount;

public:
    Listing();
    Listing(Vehicle* vehicle, Seller* s_obj, const string& title,
            const string& description, const string& date);
    Listing(const Listing& other);
    ~Listing();

    Listing& operator=(const Listing& other);

    void display();
    void approve();
    void reject();
    void updateDetails(const string& newTitle, const string& newDesc, double newPrice);

    bool matchesKeyword(const string& keyword) override;
    bool matchesPriceRange(double min, double max) override;

    static int getListingCount();

    int getListingId() { return listingId; }
    Vehicle* getVehicle() { return vehicle; }
    Seller* getSeller() { return s_obj; }
    string& getTitle() { return title; }
    string& getDescription() { return description; }
    bool getIsApproved() { return isApproved; }
    string& getDatePosted() { return datePosted; }

    void setTitle(const string& t) { title = t; }
    void setDescription(const string& desc) { description = desc; }
    void setIsApproved(bool approved) { isApproved = approved; }
    void setDatePosted(const string& date) { datePosted = date; }

    friend bool listingsBySameSeller(const Listing& a, const Listing& b);
};

