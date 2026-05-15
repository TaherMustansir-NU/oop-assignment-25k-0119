#pragma once

#include "Marketplace.h"
#include <string>

using namespace std;

class User;

class App {
private:
    Marketplace marketplace;
    User** users;
    int userCount;
    int userCapacity;
    const string appName;
    bool isInitialized;

    void resizeUsers();

public:
    App();
    App(const string& name, int initUserCap = 20);
    ~App();

    void initialize();
    void registerUser(User* user);
    User* findUserByUsername(const string& uname) const;
    User* loginUser(const string& uname, const string& password) const;
    void run();
    void cleanup();

    Marketplace& getMarketplace() { return marketplace; }
    const Marketplace& getMarketplace() const { return marketplace; }
    User* const* getUsers() const { return users; }
    int getUserCount() const { return userCount; }
    const string& getAppName() const { return appName; }
    bool getIsInitialized() const { return isInitialized; }
};

