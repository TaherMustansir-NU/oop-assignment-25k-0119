#pragma once

#include "DisplayableAbstract.h"
#include <iostream>
#include <string>

using namespace std;

class User : public IDisplayable {
private:
    const int userId;
    string uname;
    string password;
    string email;
    string phone;
    bool act_flag;

    static int userCount;

protected:
    void displayUserInfo() const;
    void setUsername(const string& username) { uname = username; }

public:
    User();
    User(const string& uname, const string& pass, const string& em,
         const string& ph, bool active = true);
    User(const User& other);
    virtual ~User();

    User& operator=(const User& other);

    virtual void display() const = 0;
    virtual string getRole() const = 0;
    virtual void showMenu() = 0;

    bool authenticate(const string& pass) const;
    void updateProfile(const string& newEmail, const string& newPhone);

    bool operator==(const User& other) const;
    friend ostream& operator<<(ostream& os, const User& u);

    static int getUserCount();

    int getUserId() const { return userId; }
    const string& getUsername() const { return uname; }
    const string& getPassword() const { return password; }
    const string& getEmail() const { return email; }
    const string& getPhone() const { return phone; }
    bool getIsActive() const { return act_flag; }

    void setPassword(const string& pass) { password = pass; }
    void setEmail(const string& em) { email = em; }
    void setPhone(const string& ph) { phone = ph; }
    void setIsActive(bool active) { act_flag = active; }
};

