#pragma once

#include <iostream>
#include <string>

using namespace std;

class Insurance {
private:
    const int pol_num;
    string prov;
    string cov_type;
    double prem;
    string exp_date;
    bool act_flag;

public:
    Insurance();
    Insurance(int policyNum, const string& prov, const string& coverage,
              double prem, const string& exp_date, bool active);
    Insurance(const Insurance& other);
    ~Insurance();

    Insurance& operator=(const Insurance& other);

    void display() const;
    bool isExpired() const;
    void renew(const string& newExpiry);
    double calculatePremium() const;

    int getPolicyNumber() const { return pol_num; }
    const string& getProvider() const { return prov; }
    const string& getCoverageType() const { return cov_type; }
    double getPremium() const { return prem; }
    const string& getExpiryDate() const { return exp_date; }
    bool getIsActive() const { return act_flag; }

    void setProvider(const string& prov) { this->prov = prov; }
    void setCoverageType(const string& coverage) { cov_type = coverage; }
    void setPremium(double prem) { this->prem = prem; }
    void setExpiryDate(const string& expiry) { exp_date = expiry; }
    void setIsActive(bool active) { act_flag = active; }
};

