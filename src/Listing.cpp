#include "Listing.h"
#include "Bike.h"
#include "Car.h"
#include "Seller.h"
#include "Vehicle.h"

using namespace std;

int Listing::listingCount = 0;

Listing::Listing()
    : listingId(++listingCount), vehicle(nullptr), s_obj(nullptr),
      title("Untitled"), description("No description"), isApproved(false),
      datePosted("01/01/2024") {
}

Listing::Listing(Vehicle* vehicle, Seller* s_obj, const string& title,
                 const string& description, const string& date)
    : listingId(++listingCount), vehicle(vehicle), s_obj(s_obj), title(title),
      description(description), isApproved(false), datePosted(date) {
}

Listing::Listing(const Listing& other)
    : listingId(other.listingId), vehicle(nullptr), s_obj(other.s_obj),
      title(other.title), description(other.description), isApproved(other.isApproved),
      datePosted(other.datePosted) {
    if (other.vehicle) {
        Car* c_obj = (Car*)other.vehicle;
        if (c_obj) {
            vehicle = new Car(*c_obj);
        } else {
            Bike* bk_obj = (Bike*)other.vehicle;
            if (bk_obj) {
                vehicle = new Bike(*bk_obj);
            }
        }
    }
}

Listing::~Listing() {
    delete vehicle;
}

Listing& Listing::operator=(const Listing& other) {
    if (this != &other) {
        delete vehicle;
        vehicle = nullptr;
        title = other.title;
        description = other.description;
        isApproved = other.isApproved;
        datePosted = other.datePosted;
        if (other.vehicle) {
            Car* c_obj = (Car*)other.vehicle;
            if (c_obj) {
                vehicle = new Car(*c_obj);
            } else {
                Bike* bk_obj = (Bike*)other.vehicle;
                if (bk_obj) {
                    vehicle = new Bike(*bk_obj);
                }
            }
        }
    }
    return *this;
}

void Listing::display() {
    cout << "Listing " << listingId << "\n";
    cout << "Title: " << title << "\n";
    cout << "Description: " << description << "\n";
    cout << "Status: " << (isApproved ? "Approved" : "Pending") << "\n";
    cout << "Posted: " << datePosted << "\n";
    if (s_obj) {
        cout << "Seller: " << s_obj->getUsername() << " (" << s_obj->getShopName() << ")\n";
    }
    vehicle->display();
}

void Listing::approve() {
    if (!isApproved) {
        isApproved = true;
        cout << "Listing " << listingId << " approved\n";
    } else {
        cout << "Listing " << listingId << " already approved\n";
    }
}

void Listing::reject() {
    if (isApproved) {
        isApproved = false;
        cout << "Listing " << listingId << " rejected\n";
    } else {
        cout << "Listing " << listingId << " already not approved\n";
    }
}

void Listing::updateDetails(const string& newTitle, const string& newDesc, double newPrice) {
    if (!newTitle.empty()) {
        title = newTitle;
    }
    if (!newDesc.empty()) {
        description = newDesc;
    }
    if (vehicle && newPrice > 0) {
        vehicle->setPrice(newPrice);
    }
    cout << "Listing " << listingId << " updated\n";
}

bool Listing::matchesKeyword(const string& keyword) {
    if (!vehicle) return false;
    return vehicle->matchesKeyword(keyword);
}

bool Listing::matchesPriceRange(double min, double max) {
    if (!vehicle) return false;
    return vehicle->matchesPriceRange(min, max);
}

int Listing::getListingCount() {
    return listingCount;
}

bool listingsBySameSeller(const Listing& a, const Listing& b) {
    return a.s_obj == b.s_obj;
}
