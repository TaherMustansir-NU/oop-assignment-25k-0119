#pragma once

#include <string>

using namespace std;

class App;
class User;
class Admin;
class Seller;
class Buyer;

class Menu {
private:
    App* app;
    User* currentUser;
    bool isRunning;
    string menuTitle;

    void clearInputBuffer();
    void pause();

    void handleLogin();
    void handleRegister();
    void handleRegisterAdmin();
    void handleRegisterSeller();
    void handleRegisterBuyer();

    void showAdminMenu();
    void showSellerMenu();
    void showBuyerMenu();

    void handleCreateCarListing(Seller* s_obj);
    void handleCreateBikeListing(Seller* s_obj);

public:
    Menu(App* ptr);
    ~Menu();

    void showWelcome();
    void handleAuth();
    void run();
};

