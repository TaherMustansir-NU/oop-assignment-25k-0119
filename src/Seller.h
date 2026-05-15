#pragma once

#include "User.h"
#include <string>

using namespace std;

class Listing;
class Marketplace;
class Car;
class Bike;

class Seller : public User {
private:
    string shopName;
    double rating;
    int totalSales;
    string address;
    string sellerSince;

public:
    Seller();
    Seller(const string& uname, const string& pass, const string& em, const string& ph,
           const string& shop, double rat, const string& addr, const string& since);
    Seller(const Seller& other);
    ~Seller() override;

    void display() const override;
    string getRole() const override;
    void showMenu() override;

    void createListing(Car& c_obj);
    void createListing(Bike& bk_obj);
    void updateListing(Marketplace* mkt, int listingId,
                       double newPrice, const string& newDescription);
    void deleteListing(Marketplace* mkt, int listingId);
    void viewMyListings(const Marketplace* mkt) const;

    const string& getShopName() const { return shopName; }
    double getRating() const { return rating; }
    int getTotalSales() const { return totalSales; }
    const string& getAddress() const { return address; }
    const string& getSellerSince() const { return sellerSince; }

    void setShopName(const string& shop) { shopName = shop; }
    void setRating(double rat) { rating = rat; }
    void setTotalSales(int sales) { totalSales = sales; }
    void incrementSales() { totalSales++; }
    void setAddress(const string& addr) { address = addr; }
    void setSellerSince(const string& since) { sellerSince = since; }
};

