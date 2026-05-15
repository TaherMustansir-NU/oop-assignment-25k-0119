#include "Seller.h"
#include "Bike.h"
#include "Car.h"
#include "Listing.h"
#include "Marketplace.h"

using namespace std;

Seller::Seller()
    : User(), shopName("Unknown Shop"), rating(0.0), totalSales(0),
      address("Unknown Address"), sellerSince("01/01/2024") {
}

Seller::Seller(const string& uname, const string& pass, const string& em, const string& ph,
               const string& shop, double rat, const string& addr, const string& since)
    : User(uname, pass, em, ph), shopName(shop), rating(rat), totalSales(0),
      address(addr), sellerSince(since) {
}

Seller::Seller(const Seller& other)
    : User(other), shopName(other.shopName), rating(other.rating),
      totalSales(other.totalSales), address(other.address),
      sellerSince(other.sellerSince) {
}

Seller::~Seller() {
}

void Seller::display() const {
    displayUserInfo();
    cout << "Role: Seller\n";
    cout << "Shop Name: " << shopName << "\n";
    cout << "Rating: " << rating << "\n";
    cout << "Total Sales: " << totalSales << "\n";
    cout << "Address: " << address << "\n";
    cout << "Seller Since: " << sellerSince << "\n";
}

string Seller::getRole() const {
    return "Seller";
}

void Seller::showMenu() {
    cout << "Seller Menu\n";
    cout << "1. View My Listings\n";
    cout << "2. Add Car Listing\n";
    cout << "3. Add Bike Listing\n";
    cout << "4. Update Listing\n";
    cout << "5. Delete Listing\n";
    cout << "6. View Messages\n";
    cout << "7. View My Profile\n";
    cout << "8. Logout\n";
    cout << "Enter choice: ";
}

void Seller::createListing(Car& car) {
    cout << "Created car listing for " << car.getBrand() << " " << car.getModel() << "\n";
}

void Seller::createListing(Bike& bike) {
    cout << "Created bike listing for " << bike.getBrand() << " " << bike.getModel() << "\n";
}

void Seller::updateListing(Marketplace* marketplace, int listingId,
                           double newPrice, const string& newDescription) {
    if (!marketplace) return;
    Listing* listing = marketplace->findListingById(listingId);
    if (listing && listing->getSeller() == this) {
        listing->updateDetails(string(), newDescription, newPrice);
    } else {
        cout << "Listing not found or you are not the owner\n";
    }
}

void Seller::deleteListing(Marketplace* marketplace, int listingId) {
    if (!marketplace) return;
    Listing* listing = marketplace->findListingById(listingId);
    if (listing && listing->getSeller() == this) {
        marketplace->removeListing(listingId);
    } else {
        cout << "Listing not found or you are not the owner\n";
    }
}

void Seller::viewMyListings(const Marketplace* marketplace) const {
    if (marketplace) {
        marketplace->getListingsBySeller(getUsername());
    }
}
