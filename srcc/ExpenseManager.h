#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "User.h"
#include "Expense.h"
#include "Split.h"
#include "PercentageSplit.h"

class ExpenseManager {
    std::unordered_map<std::string, User*> users;
    std::vector<Expense*> expenses;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> balanceSheet;
public:
    ExpenseManager() = default;
    ~ExpenseManager() {
        for (auto& p : users) delete p.second;
        for (auto& e : expenses) delete e;
    }
    void clearAllData() {
        for (auto& p : users) delete p.second;
        users.clear();
        for (auto& e : expenses) delete e;
        expenses.clear();
        balanceSheet.clear();
        std::cout << "All data cleared." << std::endl;
    }
    void addOrUpdateUser(const std::string& userId, const std::string& name) {
        if (users.find(userId) == users.end()) {
            User* user = new User(userId, name);
            users[userId] = user;
            balanceSheet[userId] = std::unordered_map<std::string, double>();
            for (const auto& other : users) {
                if (other.first != userId) {
                    balanceSheet[userId][other.first] = 0.0;
                    balanceSheet[other.first][userId] = 0.0;
                }
            }
            std::cout << "Added new user: " << userId << " (" << name << ")" << std::endl;
        }
    }
    void addExpense(const std::string& expenseType, double amount, const std::string& paidByUserId, std::vector<Split*> splits) {
        Expense* expense = new Expense(amount, users[paidByUserId], splits, expenseType);
        expenses.push_back(expense);
        if (expenseType == "EQUAL") {
            int totalUsers = splits.size();
            double splitAmount = round((amount / totalUsers) * 100.0) / 100.0;
            for (auto split : splits) split->setAmount(splitAmount);
        } else if (expenseType == "PERCENTAGE") {
            for (auto split : splits) {
                auto ps = dynamic_cast<PercentageSplit*>(split);
                double pctAmt = round((amount * ps->getPercentage() / 100.0) * 100.0) / 100.0;
                ps->setAmount(pctAmt);
            }
        }
        for (auto split : splits) {
            std::string payerId = paidByUserId;
            std::string payeeId = split->getUser()->getUserId();
            if (payerId == payeeId) continue;
            double owed = split->getAmount();
            balanceSheet[payerId][payeeId] += owed;
            balanceSheet[payeeId][payerId] -= owed;
        }
    }
    double getBalance(const std::string& fromUserId, const std::string& toUserId) {
        if (balanceSheet.find(fromUserId) == balanceSheet.end()) return 0.0;
        return balanceSheet[fromUserId][toUserId];
    }
    void settleExpense(const std::string& fromUserId, const std::string& toUserId, double amountToSettle) {
        balanceSheet[fromUserId][toUserId] = 0.0;
        balanceSheet[toUserId][fromUserId] = 0.0;
        std::cout << "You paid Rs " << amountToSettle << " to " << toUserId << "." << std::endl;
        std::cout << "You are all settled with " << toUserId << "." << std::endl;
    }
    void showBalances() {
        bool empty = true;
        for (const auto& entry : balanceSheet) {
            const std::string& userId = entry.first;
            for (const auto& bal : entry.second) {
                double amt = bal.second;
                if (amt != 0) {
                    empty = false;
                    printBalance(userId, bal.first, amt);
                }
            }
        }
        if (empty) std::cout << "No balances." << std::endl;
    }
    void showUserBalance(const std::string& userId) {
        if (balanceSheet.find(userId) == balanceSheet.end()) {
            std::cout << "No data for user: " << userId << std::endl;
            return;
        }
        bool hasNonZero = false;
        for (const auto& entry : balanceSheet[userId]) {
            double amt = entry.second;
            const std::string& otherId = entry.first;
            if (amt < 0) {
                hasNonZero = true;
                std::cout << "You owe Rs " << std::fixed << std::setprecision(2) << fabs(amt) << " to " << otherId << std::endl;
            } else if (amt > 0) {
                hasNonZero = true;
                std::cout << otherId << " owes you Rs " << std::fixed << std::setprecision(2) << amt << std::endl;
            }
        }
        if (!hasNonZero) std::cout << "You have no balances." << std::endl;
    }
    void printBalance(const std::string& user1Id, const std::string& user2Id, double amount) {
        if (amount > 0) {
            std::cout << users[user2Id]->getName() << " owes Rs " << amount << " to " << users[user1Id]->getName() << std::endl;
        }
    }
    const std::unordered_map<std::string, User*>& getUsers() const { return users; }
}; 