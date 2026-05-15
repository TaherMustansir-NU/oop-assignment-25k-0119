#pragma once

#include "User.h"
#include <string>

using namespace std;

class Listing;
class Marketplace;
class Vehicle;

class Buyer : public User {
private:
    Listing** favorites;
    int favoriteCount;
    int maxFavorites;
    double budget;
    string preferredBrand;

public:
    Buyer();
    Buyer(const string& uname, const string& pass, const string& em, const string& ph,
          double bud, const string& brand, int maxFav = 10);
    Buyer(const Buyer& other);
    ~Buyer() override;

    void display() const override;
    string getRole() const override;
    void showMenu() override;

    void addFavorite(Listing* itm);
    void removeFavorite(Listing* itm);
    void viewFavorites() const;
    void sendMessage(Marketplace* mkt, const string& receiverName,
                     const string& content);

    friend bool canAfford(const Buyer& b_obj, const Vehicle& vehicle);

    Listing* const* getFavorites() const { return favorites; }
    int getFavoriteCount() const { return favoriteCount; }
    int getMaxFavorites() const { return maxFavorites; }
    double getBudget() const { return budget; }
    const string& getPreferredBrand() const { return preferredBrand; }

    void setBudget(double bud) { budget = bud; }
    void setPreferredBrand(const string& brand) { preferredBrand = brand; }
};

