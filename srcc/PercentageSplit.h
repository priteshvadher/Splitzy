#pragma once
#include "Split.h"

class PercentageSplit : public Split {
    double percentage;
public:
    PercentageSplit(User* user, double percentage) : Split(user), percentage(percentage) {}
    double getPercentage() const { return percentage; }
}; 