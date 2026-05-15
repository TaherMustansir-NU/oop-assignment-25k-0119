#include "Menu.h"
#include "Admin.h"
#include "App.h"
#include "Bike.h"
#include "Buyer.h"
#include "Car.h"
#include "Engine.h"
#include "Insurance.h"
#include "Listing.h"
#include "Seller.h"
#include "User.h"
#include <iostream>
#include <limits>

using namespace std;

Menu::Menu(App* application)
    : app(application), currentUser(nullptr), isRunning(true),
      menuTitle("Car Marketplace System") {
}

Menu::~Menu() {
}

void Menu::clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Menu::pause() {
    cout << "Press Enter to continue" << "\n";
    string line;
    getline(cin, line);
}

void Menu::showWelcome() {
    cout << "Welcome to " << menuTitle << "\n";
}

void Menu::handleAuth() {
    while (isRunning && !currentUser) {
        cout << "Main Menu\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            handleLogin();
        } else if (choice == 2) {
            handleRegister();
        } else if (choice == 3) {
            isRunning = false;
        } else {
            cout << "Invalid option\n";
        }
    }
}

void Menu::handleLogin() {
    string username;
    string password;

    cout << "Login" << "\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    currentUser = app->loginUser(username, password);
    if (currentUser) {
        cout << "Logged in as " << currentUser->getRole() << "\n";
    }
}

void Menu::handleRegister() {
    cout << "Register" << "\n";
    cout << "1. Admin\n";
    cout << "2. Seller\n";
    cout << "3. Buyer\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    clearInputBuffer();

    if (choice == 1) {
        handleRegisterAdmin();
    } else if (choice == 2) {
        handleRegisterSeller();
    } else if (choice == 3) {
        handleRegisterBuyer();
    } else {
        cout << "Invalid option\n";
    }
}

void Menu::handleRegisterAdmin() {
    string username, password, email, phone;
    string department, accessCode;
    int adminLevel;

    cout << "Register Admin" << "\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    cout << "Email: ";
    getline(cin, email);
    cout << "Phone: ";
    getline(cin, phone);
    cout << "Admin Level: ";
    cin >> adminLevel;
    clearInputBuffer();
    cout << "Department: ";
    getline(cin, department);
    cout << "Access Code: ";
    getline(cin, accessCode);

    Admin* admin = new Admin(username, password, email, phone, adminLevel, department, accessCode);
    app->registerUser(admin);
}

void Menu::handleRegisterSeller() {
    string username, password, email, phone;
    string shopName, address;

    cout << "Register Seller" << "\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    cout << "Email: ";
    getline(cin, email);
    cout << "Phone: ";
    getline(cin, phone);
    cout << "Shop Name: ";
    getline(cin, shopName);
    cout << "Address: ";
    getline(cin, address);

    Seller* seller = new Seller(username, password, email, phone,
                                shopName, 0.0, address, "13/02/2026");
    app->registerUser(seller);
}

void Menu::handleRegisterBuyer() {
    string username, password, email, phone;
    string brand;
    double budget;

    cout << "Register Buyer" << "\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    cout << "Email: ";
    getline(cin, email);
    cout << "Phone: ";
    getline(cin, phone);
    cout << "Budget: ";
    cin >> budget;
    clearInputBuffer();
    cout << "Preferred Brand: ";
    getline(cin, brand);

    Buyer* buyer = new Buyer(username, password, email, phone, budget, brand);
    app->registerUser(buyer);
}

void Menu::showAdminMenu() {
    Admin* admin = (Admin*)currentUser;
    if (!admin) return;

    while (isRunning && currentUser) {
        admin->showMenu();
        int choice;
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            admin->viewAllListings(&app->getMarketplace());
            pause();
        } else if (choice == 2) {
            app->getMarketplace().displayPendingListings();
            pause();
        } else if (choice == 3) {
            int listingId;
            cout << "Listing ID to approve: ";
            cin >> listingId;
            clearInputBuffer();
            Listing* listing = app->getMarketplace().findListingById(listingId);
            if (listing) {
                listing->approve();
            }
            string note;
            cout << "Admin note (optional): ";
            getline(cin, note);
            if (note.empty()) {
                admin->approveListing(listingId);
            } else {
                admin->approveListing(listingId, note);
            }
            pause();
        } else if (choice == 4) {
            int listingId;
            cout << "Listing ID to remove: ";
            cin >> listingId;
            clearInputBuffer();
            admin->removeListing(&app->getMarketplace(), listingId);
            pause();
        } else if (choice == 5) {
            admin->viewAllUsers(app->getUsers(), app->getUserCount());
            pause();
        } else if (choice == 6) {
            cout << "Statistics" << "\n";
            cout << "Total Users: " << User::getUserCount() << "\n";
            cout << "Total Listings: " << Listing::getListingCount() << "\n";
            cout << "Approved by you: " << admin->getApprovedCount() << "\n";
            pause();
        } else if (choice == 7) {
            currentUser = nullptr;
            cout << "Logged out" << "\n";
        } else {
            cout << "Invalid option" << "\n";
        }
    }
}

void Menu::showSellerMenu() {
    Seller* seller = (Seller*)currentUser;
    if (!seller) return;

    while (isRunning && currentUser) {
        seller->showMenu();
        int choice;
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            seller->viewMyListings(&app->getMarketplace());
            pause();
        } else if (choice == 2) {
            handleCreateCarListing(seller);
            pause();
        } else if (choice == 3) {
            handleCreateBikeListing(seller);
            pause();
        } else if (choice == 4) {
            int listingId;
            double newPrice;
            string newDesc;
            cout << "Listing ID to update: ";
            cin >> listingId;
            clearInputBuffer();
            cout << "New Price: ";
            cin >> newPrice;
            clearInputBuffer();
            cout << "New Description: ";
            getline(cin, newDesc);
            seller->updateListing(&app->getMarketplace(), listingId, newPrice, newDesc);
            pause();
        } else if (choice == 5) {
            int listingId;
            cout << "Listing ID to delete: ";
            cin >> listingId;
            clearInputBuffer();
            seller->deleteListing(&app->getMarketplace(), listingId);
            pause();
        } else if (choice == 6) {
            app->getMarketplace().getMessagesForUser(seller->getUsername());
            pause();
        } else if (choice == 7) {
            seller->display();
            pause();
        } else if (choice == 8) {
            currentUser = nullptr;
            cout << "Logged out" << "\n";
        } else {
            cout << "Invalid option" << "\n";
        }
    }
}

void Menu::showBuyerMenu() {
    Buyer* buyer = (Buyer*)currentUser;
    if (!buyer) return;

    while (isRunning && currentUser) {
        buyer->showMenu();
        int choice;
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            app->getMarketplace().displayAllListings();
            pause();
        } else if (choice == 2) {
            string brand;
            cout << "Brand: ";
            getline(cin, brand);
            app->getMarketplace().searchByBrand(brand);
            pause();
        } else if (choice == 3) {
            double minPrice;
            double maxPrice;
            cout << "Min Price: ";
            cin >> minPrice;
            cout << "Max Price: ";
            cin >> maxPrice;
            clearInputBuffer();
            app->getMarketplace().searchByPriceRange(minPrice, maxPrice);
            pause();
        } else if (choice == 4) {
            int minYear;
            int maxYear;
            cout << "Min Year: ";
            cin >> minYear;
            cout << "Max Year: ";
            cin >> maxYear;
            clearInputBuffer();
            app->getMarketplace().filterByYear(minYear, maxYear);
            pause();
        } else if (choice == 5) {
            int listingId;
            cout << "Listing ID to add: ";
            cin >> listingId;
            clearInputBuffer();
            Listing* listing = app->getMarketplace().findListingById(listingId);
            buyer->addFavorite(listing);
            pause();
        } else if (choice == 6) {
            buyer->viewFavorites();
            pause();
        } else if (choice == 7) {
            int listingId;
            cout << "Listing ID to remove: ";
            cin >> listingId;
            clearInputBuffer();
            Listing* listing = app->getMarketplace().findListingById(listingId);
            buyer->removeFavorite(listing);
            pause();
        } else if (choice == 8) {
            string receiver;
            string content;
            cout << "Seller Username: ";
            getline(cin, receiver);
            cout << "Message: ";
            getline(cin, content);
            buyer->sendMessage(&app->getMarketplace(), receiver, content);
            pause();
        } else if (choice == 9) {
            buyer->display();
            pause();
        } else if (choice == 10) {
            currentUser = nullptr;
            cout << "Logged out" << "\n";
        } else {
            cout << "Invalid option" << "\n";
        }
    }
}

void Menu::handleCreateCarListing(Seller* seller) {
    string brand, model, color, bodyStyle, title, description;
    int year;
    double price;
    double mileage;

    cout << "Add Car Listing" << "\n";
    cout << "Brand: ";
    getline(cin, brand);
    cout << "Model: ";
    getline(cin, model);
    cout << "Year: ";
    cin >> year;
    cout << "Price: ";
    cin >> price;
    cout << "Mileage: ";
    cin >> mileage;
    clearInputBuffer();
    cout << "Color: ";
    getline(cin, color);
    cout << "Body Style: ";
    getline(cin, bodyStyle);
    cout << "Title: ";
    getline(cin, title);
    cout << "Description: ";
    getline(cin, description);

    Engine engine("Standard", 150, 2.0, "Petrol", 4, "Manual");
    Insurance insurance(10000 + year, "General Insurance", "Third Party",
                        2000.0, "31/12/2027", true);
    Car* car = new Car(brand, model, year, price, mileage, color, engine,
                       insurance, bodyStyle);
    Listing* listing = new Listing(car, seller, title, description, "13/02/2026");
    app->getMarketplace().addListing(listing);
    seller->createListing(*car);
}

void Menu::handleCreateBikeListing(Seller* seller) {
    string brand, model, color, bikeType, frameType, title, description;
    int year;
    double price;
    double mileage;
    int engineCC;
    int seatHeight;
    int absChoice;

    cout << "Add Bike Listing" << "\n";
    cout << "Brand: ";
    getline(cin, brand);
    cout << "Model: ";
    getline(cin, model);
    cout << "Year: ";
    cin >> year;
    cout << "Price: ";
    cin >> price;
    cout << "Mileage: ";
    cin >> mileage;
    clearInputBuffer();
    cout << "Color: ";
    getline(cin, color);
    cout << "Bike Type: ";
    getline(cin, bikeType);
    cout << "Engine CC: ";
    cin >> engineCC;
    cout << "Has ABS (1 yes, 0 no): ";
    cin >> absChoice;
    cout << "Frame Type: ";
    clearInputBuffer();
    getline(cin, frameType);
    cout << "Seat Height: ";
    cin >> seatHeight;
    clearInputBuffer();
    cout << "Title: ";
    getline(cin, title);
    cout << "Description: ";
    getline(cin, description);

    Bike* bike = new Bike(brand, model, year, price, mileage, color,
                          bikeType, engineCC, absChoice == 1, frameType, seatHeight);
    Listing* listing = new Listing(bike, seller, title, description, "13/02/2026");
    app->getMarketplace().addListing(listing);
    seller->createListing(*bike);
}

void Menu::run() {
    showWelcome();
    while (isRunning) {
        if (!currentUser) {
            handleAuth();
        } else {
            string role = currentUser->getRole();
            if (role == "Admin") {
                showAdminMenu();
            } else if (role == "Seller") {
                showSellerMenu();
            } else if (role == "Buyer") {
                showBuyerMenu();
            } else {
                cout << "Unknown role" << "\n";
                currentUser = nullptr;
            }
        }
    }
    cout << "Thank you for using " << app->getAppName() << "\n";
}
