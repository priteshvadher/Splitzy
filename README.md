# Splitzy

Welcome to Splitzy! This is a modern C++ application designed to help you split expenses and keep track of who owes what. Inspired by the classic Splitwise concept, this project is a ground-up C++ rewrite, offering a simple command-line interface for managing group expenses.

## What Can Splitzy Do?
- **Add shared expenses** with flexible split options: equal, exact, or percentage
- **Track balances** between any number of users
- **Settle up** debts between friends
- **Reset all data** for a fresh start

## How the Project is Organized
- `Main.cpp` — The main program and menu
- `ExpenseManager.h` — Handles users, expenses, and balances
- `User.h` — User details
- `Split.h` and its variants — Different ways to split an expense
- `Expense.h` — Represents an expense

## Getting Started

### Requirements
- C++17 or newer
- A C++ compiler (g++, clang++, or MSVC)

### Build Steps
1. Open a terminal and navigate to the `srcc` folder:
   ```sh
   cd srcc
   ```
2. Compile the program:
   ```sh
   g++ -std=c++17 -o splitzy Main.cpp
   ```
   Or, if you use clang++:
   ```sh
   clang++ -std=c++17 -o splitzy Main.cpp
   ```
   On Windows with MSVC:
   ```sh
   cl Main.cpp /std:c++17 /Fe:splitzy.exe
   ```

### Run It
- On Linux/macOS:
  ```sh
  ./splitzy
  ```
- On Windows:
  ```sh
  splitzy.exe
  ```

## How to Use
When you start Splitzy, you'll see a menu. Just follow the prompts to add expenses, check balances, or settle up. You can add new users on the fly—just type a new name when prompted.

**Example:**
```
=== Splitzy ===
1. Add expense
2. Show my balance
3. Settle expense with person
4. Show all balances
5. Clear all data
0. Exit
Choose option: 1
Enter payer userId: Alice
...
```

## Tips & Notes
- All data is kept in memory—when you exit, everything resets.
- User IDs are case-sensitive.
- For exact and percentage splits, the program checks your math.
- The app is designed for learning and experimenting—feel free to extend it!

## Want to Contribute?
Ideas for improvement:
- Add file/database saving
- Build a GUI
- Support more split types
- Add reporting or analytics

---

Splitzy is a fun way to learn C++ and manage group expenses. Enjoy splitting! 
