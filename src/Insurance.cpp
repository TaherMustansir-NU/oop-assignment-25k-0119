#include "Insurance.h"

using namespace std;

Insurance::Insurance()
    : pol_num(0), prov("Unknown"), cov_type("None"), prem(0.0),
      exp_date("01/01/2025"), act_flag(false) {
}

Insurance::Insurance(int policyNum, const string& prov, const string& coverage,
                     double prem, const string& exp_date, bool active)
    : pol_num(policyNum), prov(prov), cov_type(coverage),
      prem(prem), exp_date(exp_date), act_flag(active) {
}

Insurance::Insurance(const Insurance& other)
    : pol_num(other.pol_num), prov(other.prov),
      cov_type(other.cov_type), prem(other.prem),
      exp_date(other.exp_date), act_flag(other.act_flag) {
}

Insurance::~Insurance() {
}

Insurance& Insurance::operator=(const Insurance& other) {
    if (this != &other) {
        prov = other.prov;
        cov_type = other.cov_type;
        prem = other.prem;
        exp_date = other.exp_date;
        act_flag = other.act_flag;
    }
    return *this;
}

void Insurance::display() const {
    cout << "Policy Number: " << pol_num << "\n";
    cout << "Provider: " << prov << "\n";
    cout << "Coverage Type: " << cov_type << "\n";
    cout << "Premium: " << prem << "\n";
    cout << "Expiry Date: " << exp_date << "\n";
    cout << "Status: " << (act_flag ? "Active" : "Expired") << "\n";
}

bool Insurance::isExpired() const {
    return !act_flag;
}

void Insurance::renew(const string& newExpiry) {
    exp_date = newExpiry;
    act_flag = true;
    cout << "Insurance renewed until " << newExpiry << "\n";
}

double Insurance::calculatePremium() const {
    if (cov_type == "Comprehensive") {
        return prem * 1.5;
    }
    if (cov_type == "Third Party") {
        return prem * 0.8;
    }
    return prem;
}
