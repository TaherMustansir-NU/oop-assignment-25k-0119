#pragma once

#include <string>

using namespace std;

class Listing;
class Message;
class Seller;

class Marketplace {
private:
    Listing** listings;
    int listingCount;
    int listingCapacity;
    Message** messages;
    int messageCount;
    int messageCapacity;
    const string name;

    void resizeListings();
    void resizeMessages();

public:
    Marketplace();
    Marketplace(const string& marketName, int initListingCap = 10, int initMessageCap = 20);
    Marketplace(const Marketplace& other);
    ~Marketplace();

    void addListing(Listing* itm);
    bool removeListing(int listingId);
    void searchByBrand(const string& brand);
    void searchByPriceRange(double minPrice, double maxPrice);
    void filterByYear(int minYear, int maxYear);
    void filterByVehicleType(const string& type);
    void displayAllListings();
    void displayPendingListings();
    void addMessage(Message* message);
    void getMessagesForUser(const string& username) const;
    Listing* findListingById(int listingId) const;
    void getListingsBySeller(const string& sellerUsername) const;

    Listing** getListings() const { return listings; }
    int getListingCount() const { return listingCount; }
    int getListingCapacity() const { return listingCapacity; }
    Message* const* getMessages() const { return messages; }
    int getMessageCount() const { return messageCount; }
    int getMessageCapacity() const { return messageCapacity; }
    const string& getName() const { return name; }
};

