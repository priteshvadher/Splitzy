#pragma once
#include "Split.h"

class ExactSplit : public Split {
public:
    ExactSplit(User* user, double amount) : Split(user) { this->amount = amount; }
}; 