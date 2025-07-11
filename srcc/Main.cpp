#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>
#include <cstdlib>
#include "ExpenseManager.h"
#include "EqualSplit.h"
#include "ExactSplit.h"
#include "PercentageSplit.h"

int main() {
    ExpenseManager expenseManager;
    while (true) {
        std::cout << "\n=== Splitwise ===\n";
        std::cout << "1. Add expense\n";
        std::cout << "2. Show my balance\n";
        std::cout << "3. Settle expense with person\n";
        std::cout << "4. Show all balances\n";
        std::cout << "5. Clear all data\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose option: ";
        int option;
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (option == 1) {
            std::string paidBy;
            std::cout << "Enter payer userId: ";
            std::getline(std::cin, paidBy);
            if (expenseManager.getUsers().find(paidBy) == expenseManager.getUsers().end()) {
                expenseManager.addOrUpdateUser(paidBy, paidBy);
            }
            double amount;
            std::cout << "Enter total amount: ";
            std::cin >> amount;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            int count;
            std::cout << "Enter number of users to split among: ";
            std::cin >> count;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::vector<std::string> userIds;
            for (int i = 0; i < count; ++i) {
                std::string userId;
                std::cout << "Enter userId #" << (i + 1) << ": ";
                std::getline(std::cin, userId);
                if (expenseManager.getUsers().find(userId) == expenseManager.getUsers().end()) {
                    expenseManager.addOrUpdateUser(userId, userId);
                }
                userIds.push_back(userId);
            }
            std::vector<Split*> splits;
            if (count == 1) {
                splits.push_back(new ExactSplit(expenseManager.getUsers().at(userIds[0]), amount));
                expenseManager.addExpense("EXACT", amount, paidBy, splits);
            } else {
                std::cout << "Choose split type (enter number):\n";
                std::cout << "1) Equal\n";
                std::cout << "2) Exact\n";
                std::cout << "3) Percentage\n";
                int splitChoice;
                std::cin >> splitChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (splitChoice == 1) {
                    for (const auto& uid : userIds) {
                        splits.push_back(new EqualSplit(expenseManager.getUsers().at(uid)));
                    }
                    expenseManager.addExpense("EQUAL", amount, paidBy, splits);
                } else if (splitChoice == 2) {
                    double totalExact = 0;
                    for (const auto& uid : userIds) {
                        double exactAmt;
                        std::cout << "Enter exact amount for " << uid << ": ";
                        std::cin >> exactAmt;
                        totalExact += exactAmt;
                        splits.push_back(new ExactSplit(expenseManager.getUsers().at(uid), exactAmt));
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (fabs(totalExact - amount) > 0.01) {
                        std::cout << "Error: sums (" << totalExact << ") != total (" << amount << ")." << std::endl;
                    } else {
                        expenseManager.addExpense("EXACT", amount, paidBy, splits);
                    }
                } else if (splitChoice == 3) {
                    double totalPct = 0;
                    for (const auto& uid : userIds) {
                        double pct;
                        std::cout << "Enter percentage for " << uid << ": ";
                        std::cin >> pct;
                        totalPct += pct;
                        splits.push_back(new PercentageSplit(expenseManager.getUsers().at(uid), pct));
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (fabs(totalPct - 100.0) > 0.01) {
                        std::cout << "Error: total percentage (" << totalPct << "%) must be 100%." << std::endl;
                    } else {
                        expenseManager.addExpense("PERCENTAGE", amount, paidBy, splits);
                    }
                } else {
                    std::cout << "Invalid choice." << std::endl;
                }
            }
        } else if (option == 2) {
            std::string userId;
            std::cout << "Enter your userId: ";
            std::getline(std::cin, userId);
            if (expenseManager.getUsers().find(userId) == expenseManager.getUsers().end()) {
                expenseManager.addOrUpdateUser(userId, userId);
            }
            expenseManager.showUserBalance(userId);
        } else if (option == 3) {
            std::string fromUserId, toUserId;
            std::cout << "Enter your userId: ";
            std::getline(std::cin, fromUserId);
            if (expenseManager.getUsers().find(fromUserId) == expenseManager.getUsers().end()) {
                std::cout << "User not found: " << fromUserId << std::endl;
                continue;
            }
            std::cout << "Enter other userId to settle with: ";
            std::getline(std::cin, toUserId);
            if (expenseManager.getUsers().find(toUserId) == expenseManager.getUsers().end()) {
                std::cout << "User not found: " << toUserId << std::endl;
                continue;
            }
            double owed = expenseManager.getBalance(fromUserId, toUserId);
            if (owed >= 0) {
                std::cout << "No outstanding balance from " << fromUserId << " to " << toUserId << "." << std::endl;
            } else {
                expenseManager.settleExpense(fromUserId, toUserId, -owed);
            }
        } else if (option == 4) {
            expenseManager.showBalances();
        } else if (option == 5) {
            expenseManager.clearAllData();
        } else if (option == 0) {
            std::cout << "Exiting. Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
    return 0;
} 