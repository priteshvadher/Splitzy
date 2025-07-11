# SplitBuddy C++ Version

This is a C++ port of the SplitBuddy expense sharing application.

## Files
- Main.cpp: Entry point and main menu logic
- ExpenseManager.h: Core logic for managing users, expenses, and balances
- User.h: User class
- Split.h: Abstract base class for splits
- EqualSplit.h, ExactSplit.h, PercentageSplit.h: Split types
- Expense.h: Expense class

## Build Instructions

You need a C++17 compatible compiler (e.g., g++, clang++).

### Compile (using g++)

```
g++ -std=c++17 -o splitbuddy Main.cpp
```

### Run

```
./splitbuddy
```

## Notes
- All data is in-memory and lost on exit.
- The logic and menu are modeled after the original Java version. 