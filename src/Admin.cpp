#include "Admin.h"
#include "Listing.h"
#include "Marketplace.h"

using namespace std;

Admin::Admin()
    : User(), adminLevel(1), department("General"), accessCode("ADMIN123"),
      lastLogin("Never"), approvedCount(0) {}

Admin::Admin(const string &uname, const string &pass, const string &em,
             const string &ph, int level, const string &dept,
             const string &code)
    : User(uname, pass, em, ph), adminLevel(level), department(dept),
      accessCode(code), lastLogin("Never"), approvedCount(0) {}

Admin::Admin(const Admin &other)
    : User(other), adminLevel(other.adminLevel), department(other.department),
      accessCode(other.accessCode), lastLogin(other.lastLogin),
      approvedCount(other.approvedCount) {}

Admin::~Admin() {}

void Admin::display() const {
  displayUserInfo();
  cout << "Role: Admin\n";
  cout << "Admin Level: " << adminLevel << "\n";
  cout << "Department: " << department << "\n";
  cout << "Approved Listings: " << approvedCount << "\n";
  cout << "Last Login: " << lastLogin << "\n";
}

string Admin::getRole() const { return "Admin"; }

void Admin::showMenu() {
  cout << "Admin Menu\n";
  cout << "1. View All Listings\n";
  cout << "2. View Pending Listings\n";
  cout << "3. Approve Listing\n";
  cout << "4. Remove Listing\n";
  cout << "5. View All Users\n";
  cout << "6. View Statistics\n";
  cout << "7. Logout\n";
  cout << "Enter choice: ";
}

void Admin::approveListing(int listingId) {
  incrementApprovedCount();
  cout << "Listing " << listingId << " approved\n";
}

void Admin::approveListing(int listingId, const string &adminNote) {
  incrementApprovedCount();
  cout << "Listing " << listingId << " approved\n";
  if (!adminNote.empty()) {
    cout << "Note: " << adminNote << "\n";
  }
}

void Admin::removeListing(Marketplace *marketplace, int listingId) {
  if (marketplace) {
    marketplace->removeListing(listingId);
  }
}

void Admin::viewAllListings(const Marketplace *marketplace) {
  if (!marketplace)
    return;
  Listing **listings = marketplace->getListings();
  int count = marketplace->getListingCount();
  cout << "All Listings\n";
  for (int i = 0; i < count; i++) {
    if (listings[i]) {
      listings[i]->display();
    }
  }
  cout << "Total Listings: " << count << "\n";
}

void Admin::viewAllUsers(User *const *users, int userCount) const {
  cout << "All Users\n";
  for (int i = 0; i < userCount; i++) {
    if (users[i]) {
      users[i]->display();
    }
  }
}
