#include "Buyer.h"
#include "Listing.h"
#include "Marketplace.h"
#include "Message.h"
#include "Vehicle.h"

using namespace std;

Buyer::Buyer()
    : User(), favorites(nullptr), favoriteCount(0), maxFavorites(10),
      budget(0.0), preferredBrand("Any") {
    favorites = new Listing*[maxFavorites];
    for (int i = 0; i < maxFavorites; i++) {
        favorites[i] = nullptr;
    }
}

Buyer::Buyer(const string& uname, const string& pass, const string& em, const string& ph,
             double bud, const string& brand, int maxFav)
    : User(uname, pass, em, ph), favorites(nullptr), favoriteCount(0),
      maxFavorites(maxFav), budget(bud), preferredBrand(brand) {
    favorites = new Listing*[maxFavorites];
    for (int i = 0; i < maxFavorites; i++) {
        favorites[i] = nullptr;
    }
}

Buyer::Buyer(const Buyer& other)
    : User(other), favorites(nullptr), favoriteCount(other.favoriteCount),
      maxFavorites(other.maxFavorites), budget(other.budget),
      preferredBrand(other.preferredBrand) {
    favorites = new Listing*[maxFavorites];
    for (int i = 0; i < favoriteCount; i++) {
        favorites[i] = other.favorites[i];
    }
    for (int i = favoriteCount; i < maxFavorites; i++) {
        favorites[i] = nullptr;
    }
}

Buyer::~Buyer() {
    delete[] favorites;
}

void Buyer::display() const {
    displayUserInfo();
    cout << "Role: Buyer\n";
    cout << "Budget: " << budget << "\n";
    cout << "Preferred Brand: " << preferredBrand << "\n";
    cout << "Favorites: " << favoriteCount << "/" << maxFavorites << "\n";
}

string Buyer::getRole() const {
    return "Buyer";
}

void Buyer::showMenu() {
    cout << "Buyer Menu\n";
    cout << "1. View All Listings\n";
    cout << "2. Search by Brand\n";
    cout << "3. Search by Price Range\n";
    cout << "4. Filter by Year\n";
    cout << "5. Add to Favorites\n";
    cout << "6. View Favorites\n";
    cout << "7. Remove from Favorites\n";
    cout << "8. Send Message to Seller\n";
    cout << "9. View My Profile\n";
    cout << "10. Logout\n";
    cout << "Enter choice: ";
}

void Buyer::addFavorite(Listing* listing) {
    if (!listing) {
        cout << "Invalid listing\n";
        return;
    }
    if (favoriteCount >= maxFavorites) {
        cout << "Favorites list is full\n";
        return;
    }
    for (int i = 0; i < favoriteCount; i++) {
        if (favorites[i] == listing) {
            cout << "Listing already in favorites\n";
            return;
        }
    }
    favorites[favoriteCount++] = listing;
    cout << "Listing added to favorites\n";
}

void Buyer::removeFavorite(Listing* listing) {
    if (!listing) return;
    for (int i = 0; i < favoriteCount; i++) {
        if (favorites[i] == listing) {
            for (int j = i; j < favoriteCount - 1; j++) {
                favorites[j] = favorites[j + 1];
            }
            favorites[--favoriteCount] = nullptr;
            cout << "Listing removed from favorites\n";
            return;
        }
    }
    cout << "Listing not found in favorites\n";
}

void Buyer::viewFavorites() const {
    cout << "My Favorites\n";
    if (favoriteCount == 0) {
        cout << "No favorites\n";
        return;
    }
    for (int i = 0; i < favoriteCount; i++) {
        if (favorites[i]) {
            favorites[i]->display();
        }
    }
    cout << "Total favorites: " << favoriteCount << "\n";
}

void Buyer::sendMessage(Marketplace* marketplace, const string& receiverName,
                        const string& content) {
    if (!marketplace || receiverName.empty() || content.empty()) return;
    Message* msg = new Message(getUsername(), receiverName, content, "13:30:00");
    marketplace->addMessage(msg);
}

bool canAfford(const Buyer& buyer, const Vehicle& vehicle) {
    return buyer.budget >= vehicle.getPrice();
}
