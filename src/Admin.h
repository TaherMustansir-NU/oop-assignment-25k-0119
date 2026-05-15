#pragma once

#include "User.h"
#include <string>

using namespace std;

class Listing;
class Marketplace;

class Admin : public User {
private:
    int adminLevel;
    string department;
    string accessCode;
    string lastLogin;
    int approvedCount;

public:
    Admin();
    Admin(const string& uname, const string& pass, const string& em, const string& ph,
          int level, const string& dept, const string& code);
    Admin(const Admin& other);
    ~Admin() override;

    void display() const override;
    string getRole() const override;
    void showMenu() override;

    void approveListing(int listingId);
    void approveListing(int listingId, const string& adminNote);
    void removeListing(Marketplace* mkt, int listingId);
    void viewAllListings(const Marketplace* mkt);
    void viewAllUsers(User* const* users, int userCount) const;

    int getAdminLevel() const { return adminLevel; }
    const string& getDepartment() const { return department; }
    const string& getAccessCode() const { return accessCode; }
    const string& getLastLogin() const { return lastLogin; }
    int getApprovedCount() const { return approvedCount; }

    void setAdminLevel(int level) { adminLevel = level; }
    void setDepartment(const string& dept) { department = dept; }
    void setAccessCode(const string& code) { accessCode = code; }
    void setLastLogin(const string& login) { lastLogin = login; }
    void incrementApprovedCount() { approvedCount++; }
};

