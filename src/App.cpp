#include "App.h"
#include "Admin.h"
#include "Bike.h"
#include "Buyer.h"
#include "Car.h"
#include "Engine.h"
#include "Insurance.h"
#include "Listing.h"
#include "Menu.h"
#include "Seller.h"
#include "User.h"
#include <iostream>

using namespace std;

App::App()
    : marketplace(), users(nullptr), userCount(0), userCapacity(20),
      appName("Car Marketplace System"), isInitialized(false) {
    users = new User*[userCapacity];
    for (int i = 0; i < userCapacity; i++) {
        users[i] = nullptr;
    }
}

App::App(const string& name, int initUserCap)
    : marketplace(), users(nullptr), userCount(0), userCapacity(initUserCap),
      appName(name), isInitialized(false) {
    users = new User*[userCapacity];
    for (int i = 0; i < userCapacity; i++) {
        users[i] = nullptr;
    }
}

App::~App() {
    cleanup();
}

void App::resizeUsers() {
    int newCapacity = userCapacity * 2;
    User** newUsers = new User*[newCapacity];
    for (int i = 0; i < userCount; i++) {
        newUsers[i] = users[i];
    }
    for (int i = userCount; i < newCapacity; i++) {
        newUsers[i] = nullptr;
    }
    delete[] users;
    users = newUsers;
    userCapacity = newCapacity;
    cout << "User capacity expanded to " << newCapacity << "\n";
}

void App::initialize() {
    if (isInitialized) {
        cout << "App already initialized\n";
        return;
    }

    cout << "Initializing " << appName << "\n";

    Admin* admin = new Admin("admin", "admin123", "admin@pakwheels.com",
                             "0300-1234567", 5, "Management", "ADMIN123");
    registerUser(admin);

    Seller* seller1 = new Seller("seller1", "pass123", "seller1@email.com",
                                 "0301-1111111", "AutoHub", 4.5,
                                 "Main Boulevard, Lahore", "01/01/2020");
    Seller* seller2 = new Seller("seller2", "pass456", "seller2@email.com",
                                 "0302-2222222", "Elite Motors", 4.8,
                                 "Clifton, Karachi", "15/06/2021");
    registerUser(seller1);
    registerUser(seller2);

    Buyer* buyer1 = new Buyer("buyer1", "pass789", "buyer1@email.com",
                              "0303-3333333", 5000000.0, "Toyota", 15);
    Buyer* buyer2 = new Buyer("buyer2", "pass000", "buyer2@email.com",
                              "0304-4444444", 8000000.0, "Honda", 10);
    registerUser(buyer1);
    registerUser(buyer2);

    Engine engine1("V6", 250, 3.5, "Petrol", 6, "Automatic");
    Insurance insurance1(12345, "State Life", "Comprehensive", 5000.0,
                         "31/12/2026", true);
    Car* car1 = new Car("Toyota", "Corolla", 2022, 4500000.0, 15000, "White",
                        engine1, insurance1, "Sedan");
    Listing* listing1 = new Listing(car1, seller1,
                                    "2022 Toyota Corolla",
                                    "Low mileage, single owner",
                                    "01/02/2026");
    marketplace.addListing(listing1);

    Engine engine2("Inline-4", 180, 2.0, "Petrol", 4, "Manual");
    Insurance insurance2(54321, "Jubilee Insurance", "Third Party", 3000.0,
                         "30/06/2027", true);
    Car* car2 = new Car("Honda", "Civic", 2021, 5200000.0, 22000, "Black",
                        engine2, insurance2, "Sedan");
    Listing* listing2 = new Listing(car2, seller2,
                                    "2021 Honda Civic",
                                    "Well maintained",
                                    "10/02/2026");
    marketplace.addListing(listing2);

    Bike* bike1 = new Bike("Yamaha", "R15", 2023, 550000.0, 2000, "Blue",
                           "Sport", 155, true, "Deltabox", 815);
    Listing* listing3 = new Listing(bike1, seller1,
                                    "2023 Yamaha R15",
                                    "Sport bike, low mileage",
                                    "12/02/2026");
    marketplace.addListing(listing3);

    isInitialized = true;
    cout << "Initialization complete\n";
    cout << "Default Admin username: admin\n";
    cout << "Total Users: " << userCount << "\n";
    cout << "Total Listings: " << marketplace.getListingCount() << "\n";
}

void App::registerUser(User* user) {
    if (!user) {
        cout << "Cannot register null user\n";
        return;
    }
    for (int i = 0; i < userCount; i++) {
        if (users[i] && users[i]->getUsername() == user->getUsername()) {
            cout << "Username already exists\n";
            delete user;
            return;
        }
    }
    if (userCount >= userCapacity) {
        resizeUsers();
    }
    users[userCount++] = user;
    cout << "User registered. Role: " << user->getRole() << "\n";
}

User* App::findUserByUsername(const string& username) const {
    if (username.empty()) return nullptr;
    for (int i = 0; i < userCount; i++) {
        if (users[i] && users[i]->getUsername() == username) {
            return users[i];
        }
    }
    return nullptr;
}

User* App::loginUser(const string& username, const string& password) const {
    User* user = findUserByUsername(username);
    if (user && user->authenticate(password)) {
        cout << "Login successful" << "\n";
        return user;
    }
    cout << "Invalid username or password\n";
    return nullptr;
}

void App::run() {
    initialize();
    Menu menu(this);
    menu.run();
}

void App::cleanup() {
    for (int i = 0; i < userCount; i++) {
        delete users[i];
    }
    delete[] users;
    users = nullptr;
    userCount = 0;
}
