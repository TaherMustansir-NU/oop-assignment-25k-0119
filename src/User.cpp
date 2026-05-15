#include "User.h"

using namespace std;

int User::userCount = 0;

User::User()
    : userId(++userCount), uname("guest"), password("password"),
      email("guest@example.com"), phone("0000000000"), act_flag(true) {
}

User::User(const string& uname, const string& pass, const string& em,
           const string& ph, bool active)
    : userId(++userCount), uname(uname), password(pass), email(em),
      phone(ph), act_flag(active) {
}

User::User(const User& other)
    : userId(other.userId), uname(other.uname), password(other.password),
      email(other.email), phone(other.phone), act_flag(other.act_flag) {
}

User::~User() {
}

User& User::operator=(const User& other) {
    if (this != &other) {
        uname = other.uname;
        password = other.password;
        email = other.email;
        phone = other.phone;
        act_flag = other.act_flag;
    }
    return *this;
}

void User::displayUserInfo() const {
    cout << "User Details\n";
    cout << "User ID: " << userId << "\n";
    cout << "Username: " << uname << "\n";
    cout << "Email: " << email << "\n";
    cout << "Phone: " << phone << "\n";
    cout << "Status: " << (act_flag ? "Active" : "Inactive") << "\n";
}

bool User::authenticate(const string& pass) const {
    return password == pass;
}

void User::updateProfile(const string& newEmail, const string& newPhone) {
    if (!newEmail.empty()) {
        email = newEmail;
    }
    if (!newPhone.empty()) {
        phone = newPhone;
    }
    cout << "Profile updated" << "\n";
}

bool User::operator==(const User& other) const {
    return userId == other.userId;
}

ostream& operator<<(ostream& os, const User& u) {
    os << "[" << u.getRole() << "] " << u.uname << " (" << u.email << ")";
    return os;
}

int User::getUserCount() {
    return userCount;
}
