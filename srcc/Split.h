#pragma once
#include "User.h"

class Split {
protected:
    User* user;
    double amount;
public:
    Split(User* user) : user(user), amount(0) {}
    virtual ~Split() = default;
    User* getUser() const { return user; }
    double getAmount() const { return amount; }
    void setAmount(double amt) { amount = amt; }
}; 