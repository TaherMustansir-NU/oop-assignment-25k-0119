#include "Marketplace.h"
#include "Listing.h"
#include "Message.h"
#include "Seller.h"
#include "Vehicle.h"
#include <iostream>

using namespace std;

Marketplace::Marketplace()
    : listings(nullptr), listingCount(0), listingCapacity(10), messages(nullptr),
      messageCount(0), messageCapacity(20), name("PakWheels Marketplace") {
    listings = new Listing*[listingCapacity];
    for (int i = 0; i < listingCapacity; i++) {
        listings[i] = nullptr;
    }
    messages = new Message*[messageCapacity];
    for (int i = 0; i < messageCapacity; i++) {
        messages[i] = nullptr;
    }
}

Marketplace::Marketplace(const string& marketName, int initListingCap, int initMessageCap)
    : listings(nullptr), listingCount(0), listingCapacity(initListingCap), messages(nullptr),
      messageCount(0), messageCapacity(initMessageCap), name(marketName) {
    listings = new Listing*[listingCapacity];
    for (int i = 0; i < listingCapacity; i++) {
        listings[i] = nullptr;
    }
    messages = new Message*[messageCapacity];
    for (int i = 0; i < messageCapacity; i++) {
        messages[i] = nullptr;
    }
}

Marketplace::Marketplace(const Marketplace& other)
    : listings(nullptr), listingCount(other.listingCount),
      listingCapacity(other.listingCapacity), messages(nullptr),
      messageCount(other.messageCount), messageCapacity(other.messageCapacity),
      name(other.name) {
    listings = new Listing*[listingCapacity];
    for (int i = 0; i < listingCount; i++) {
        listings[i] = new Listing(*other.listings[i]);
    }
    for (int i = listingCount; i < listingCapacity; i++) {
        listings[i] = nullptr;
    }
    messages = new Message*[messageCapacity];
    for (int i = 0; i < messageCount; i++) {
        messages[i] = new Message(*other.messages[i]);
    }
    for (int i = messageCount; i < messageCapacity; i++) {
        messages[i] = nullptr;
    }
}

Marketplace::~Marketplace() {
    for (int i = 0; i < listingCount; i++) {
        delete listings[i];
    }
    delete[] listings;
    for (int i = 0; i < messageCount; i++) {
        delete messages[i];
    }
    delete[] messages;
}

void Marketplace::resizeListings() {
    int newCapacity = listingCapacity * 2;
    Listing** newListings = new Listing*[newCapacity];
    for (int i = 0; i < listingCount; i++) {
        newListings[i] = listings[i];
    }
    for (int i = listingCount; i < newCapacity; i++) {
        newListings[i] = nullptr;
    }
    delete[] listings;
    listings = newListings;
    listingCapacity = newCapacity;
    cout << "Listings capacity expanded to " << newCapacity << "\n";
}

void Marketplace::resizeMessages() {
    int newCapacity = messageCapacity * 2;
    Message** newMessages = new Message*[newCapacity];
    for (int i = 0; i < messageCount; i++) {
        newMessages[i] = messages[i];
    }
    for (int i = messageCount; i < newCapacity; i++) {
        newMessages[i] = nullptr;
    }
    delete[] messages;
    messages = newMessages;
    messageCapacity = newCapacity;
    cout << "Messages capacity expanded to " << newCapacity << "\n";
}

void Marketplace::addListing(Listing* listing) {
    if (!listing) {
        cout << "Cannot add null listing\n";
        return;
    }
    if (listingCount >= listingCapacity) {
        resizeListings();
    }
    listings[listingCount++] = listing;
    cout << "Listing added" << "\n";
}

bool Marketplace::removeListing(int listingId) {
    for (int i = 0; i < listingCount; i++) {
        if (listings[i] && listings[i]->getListingId() == listingId) {
            delete listings[i];
            for (int j = i; j < listingCount - 1; j++) {
                listings[j] = listings[j + 1];
            }
            listings[--listingCount] = nullptr;
            cout << "Listing " << listingId << " removed\n";
            return true;
        }
    }
    cout << "Listing " << listingId << " not found\n";
    return false;
}

void Marketplace::searchByBrand(const string& brand) {
    if (brand.empty()) return;
    cout << "Search Results for Brand: " << brand << "\n";
    int found = 0;
    for (int i = 0; i < listingCount; i++) {
        if (listings[i] && listings[i]->getIsApproved()) {
            if (listings[i]->matchesKeyword(brand)) {
                listings[i]->display();
                found++;
            }
        }
    }
    if (found == 0) {
        cout << "No listings found for brand\n";
    } else {
        cout << "Found " << found << " listing(s)\n";
    }
}

void Marketplace::searchByPriceRange(double minPrice, double maxPrice) {
    cout << "Listings in Price Range\n";
    int found = 0;
    for (int i = 0; i < listingCount; i++) {
        if (listings[i] && listings[i]->getIsApproved()) {
            if (listings[i]->matchesPriceRange(minPrice, maxPrice)) {
                listings[i]->display();
                found++;
            }
        }
    }
    if (found == 0) {
        cout << "No listings found in this price range\n";
    } else {
        cout << "Found " << found << " listing(s)\n";
    }
}

void Marketplace::filterByYear(int minYear, int maxYear) {
    cout << "Listings by Year Range\n";
    int found = 0;
    for (int i = 0; i < listingCount; i++) {
        if (listings[i] && listings[i]->getIsApproved()) {
            Vehicle* vehicle = listings[i]->getVehicle();
            if (vehicle) {
                int year = vehicle->getYear();
                if (year >= minYear && year <= maxYear) {
                    listings[i]->display();
                    found++;
                }
            }
        }
    }
    if (found == 0) {
        cout << "No listings found for these years\n";
    } else {
        cout << "Found " << found << " listing(s)\n";
    }
}

void Marketplace::filterByVehicleType(const string& type) {
    cout << "Listings by Vehicle Type: " << type << "\n";
    int found = 0;
    for (int i = 0; i < listingCount; i++) {
        if (listings[i] && listings[i]->getIsApproved()) {
            Vehicle* vehicle = listings[i]->getVehicle();
            if (vehicle && vehicle->getVehicleType() == type) {
                listings[i]->display();
                found++;
            }
        }
    }
    if (found == 0) {
        cout << "No listings found for this type\n";
    } else {
        cout << "Found " << found << " listing(s)\n";
    }
}

void Marketplace::displayAllListings() {
    cout << "Approved Listings\n";
    int approvedCount = 0;
    for (int i = 0; i < listingCount; i++) {
        if (listings[i] && listings[i]->getIsApproved()) {
            listings[i]->display();
            approvedCount++;
        }
    }
    if (approvedCount == 0) {
        cout << "No approved listings\n";
    } else {
        cout << "Total approved listings: " << approvedCount << "\n";
    }
}

void Marketplace::displayPendingListings() {
    cout << "Pending Listings\n";
    int pendingCount = 0;
    for (int i = 0; i < listingCount; i++) {
        if (listings[i] && !listings[i]->getIsApproved()) {
            listings[i]->display();
            pendingCount++;
        }
    }
    if (pendingCount == 0) {
        cout << "No pending listings\n";
    } else {
        cout << "Total pending listings: " << pendingCount << "\n";
    }
}

void Marketplace::addMessage(Message* message) {
    if (!message) {
        cout << "Cannot add null message\n";
        return;
    }
    if (messageCount >= messageCapacity) {
        resizeMessages();
    }
    messages[messageCount++] = message;
    cout << "Message sent" << "\n";
}

void Marketplace::getMessagesForUser(const string& username) const {
    if (username.empty()) return;
    cout << "Messages for " << username << "\n";
    int found = 0;
    for (int i = 0; i < messageCount; i++) {
        if (messages[i] && messages[i]->getReceiverName() == username) {
            messages[i]->display();
            found++;
        }
    }
    if (found == 0) {
        cout << "No messages for " << username << "\n";
    } else {
        cout << "Total messages: " << found << "\n";
    }
}

Listing* Marketplace::findListingById(int listingId) const {
    for (int i = 0; i < listingCount; i++) {
        if (listings[i] && listings[i]->getListingId() == listingId) {
            return listings[i];
        }
    }
    return nullptr;
}

void Marketplace::getListingsBySeller(const string& sellerUsername) const {
    if (sellerUsername.empty()) return;
    cout << "Listings by " << sellerUsername << "\n";
    int found = 0;
    for (int i = 0; i < listingCount; i++) {
        if (listings[i]) {
            const Seller* seller = listings[i]->getSeller();
            if (seller && seller->getUsername() == sellerUsername) {
                listings[i]->display();
                found++;
            }
        }
    }
    if (found == 0) {
        cout << "No listings found for seller\n";
    } else {
        cout << "Total listings: " << found << "\n";
    }
}
