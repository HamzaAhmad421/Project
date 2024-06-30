#include <iostream>
#include <string>
#include <limits> // Include this header for numeric_limits
using namespace std;

class Account {
private:
    double balance;
    string pin;

public:
    Account() : balance(0), pin("") {}

    void initialize(double initial_balance, string account_pin) {
        balance = initial_balance;
        pin = account_pin;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. Current balance: $" << balance << endl;
        } else {
            cout << "Invalid amount. Deposit failed." << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. Current balance: $" << balance << endl;
            return true;
        } else {
            cout << "Insufficient funds or invalid amount. Withdrawal failed." << endl;
            return false;
        }
    }

    void checkBalance() const {
        cout << "Current balance: $" << balance << endl;
    }

    bool transfer(Account& recipient, double amount) {
        if (withdraw(amount)) {
            recipient.deposit(amount);
            cout << "Transfer successful. Current balance after transfer: $" << balance << endl;
            return true;
        } else {
            return false;
        }
    }

    bool validatePin(const string& enteredPin) const {
        return enteredPin == pin;
    }

    void setPin(const string& newPin) {
        pin = newPin;
        cout << "PIN set successfully." << endl;
    }
};

class User {
private:
    string name;
    Account account;

public:
    User() : name("") {}

    void initialize(const string& user_name, double initial_balance, const string& account_pin) {
        name = user_name;
        account.initialize(initial_balance, account_pin);
    }

    Account& getAccount() {
        return account;
    }

    const string& getName() const {
        return name;
    }
};

class Bank {
private:
    static const int MAX_USERS = 10;
    User users[MAX_USERS];
    int userCount;

public:
    Bank() : userCount(0) {}

    void addUser(const string& name, double initial_balance, const string& pin) {
        if (userCount < MAX_USERS) {
            users[userCount].initialize(name, initial_balance, pin);
            cout << "User " << name << " added successfully." << endl;
            userCount++;
        } else {
            cout << "Maximum user limit reached. Cannot add more users." << endl;
        }
    }

    User* getUser(const string& name) {
        for (int i = 0; i < userCount; ++i) {
            if (users[i].getName() == name) {
                return &users[i];
            }
        }
        cout << "User " << name << " not found." << endl;
        return NULL;
    }
};

void displayMenu() {
    cout << "\nBank Management System" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Check Balance" << endl;
    cout << "4. Transfer Money" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Bank bank;
    string name, pin, recipientName;
    double amount;
    int choice;

    // Add some sample users to the bank
    bank.addUser("Basser", 5000.0, "1234");
    bank.addUser("Hamza", 5000.0, "5678");

    cout << "Enter your name: ";
    cin >> name;

    User* user = bank.getUser(name);
    if (!user) return 0;

    // Validate PIN
    cout << "Enter your PIN: ";
    cin >> pin;
    if (!user->getAccount().validatePin(pin)) {
        cout << "Invalid PIN. Access denied." << endl;
        return 0;
    }

    do {
        system("cls");  // Clear the console
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter amount to deposit: $";
                cin >> amount;
                if (cin.fail()) {
                    clearInputBuffer();
                    cout << "Invalid amount. Transaction failed." << endl;
                } else {
                    user->getAccount().deposit(amount);
                }
                break;
            case 2:
                cout << "Enter amount to withdraw: $";
                cin >> amount;
                if (cin.fail()) {
                    clearInputBuffer();
                    cout << "Invalid amount. Transaction failed." << endl;
                } else {
                    user->getAccount().withdraw(amount);
                }
                break;
            case 3:
                user->getAccount().checkBalance();
                break;
            case 4:
                cout << "Enter recipient's name: ";
                cin >> recipientName;
                cout << "Enter amount to transfer: $";
                cin >> amount;
                if (cin.fail()) {
                    clearInputBuffer();
                    cout << "Invalid amount. Transaction failed." << endl;
                } else {
                    User* recipient = bank.getUser(recipientName);
                    if (recipient) {
                        user->getAccount().transfer(recipient->getAccount(), amount);
                    }
                }
                break;
            case 5:
                cout << "Exiting program. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (choice >= 1 && choice <= 4) {
            char response;
            cout << "Do you want to perform another transaction? (y/n): ";
            cin >> response;
            if (response != 'y' && response != 'Y') {
                break;
            }
        }
    } while (choice != 5);

    return 0;
}

