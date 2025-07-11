#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "Split.h"

class Expense {
    double amount;
    User* paidBy;
    std::vector<Split*> splits;
    std::string expenseType;
public:
    Expense(double amount, User* paidBy, const std::vector<Split*>& splits, const std::string& expenseType)
        : amount(amount), paidBy(paidBy), splits(splits), expenseType(expenseType) {}
    double getAmount() const { return amount; }
    User* getPaidBy() const { return paidBy; }
    const std::vector<Split*>& getSplits() const { return splits; }
    const std::string& getExpenseType() const { return expenseType; }
}; 