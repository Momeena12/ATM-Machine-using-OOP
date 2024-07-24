#include <iostream>        // For input-output operations
#include <string>          // For string class
#include <vector>          // For vector container
#include <stdexcept>       // For exception handling
#include <chrono>          // For time-related functions
#include <fstream>         // For file operations
#include <limits>          // For numeric_limits
#include <ctime>           // For ctime_r
#ifdef _WIN32
#else
#define CLEAR_SCREEN "clear" 
#endif
#define RESET        "\033[0m"       // Adding colours to the text at Run time. 
#define RED          "\033[31m"      
#define GREEN        "\033[32m"      
#define YELLOW       "\033[33m"      
#define BLUE         "\033[34m"     
#define MAGENTA      "\033[35m"      
#define CYAN         "\033[36m"      
#define WHITE        "\033[37m"      
#define GRAY         "\033[90m"      
#define LIGHT_RED    "\033[91m"      
#define LIGHT_GREEN  "\033[92m"      
#define LIGHT_YELLOW "\033[93m"      
#define LIGHT_BLUE   "\033[94m"      
#define LIGHT_MAGENTA "\033[95m"     
#define LIGHT_CYAN   "\033[96m"   

using namespace std;

// BankAccount class definition
class BankAccount {
private:
    double balance;         // Account balance
    string accountNumber;   // Account number

public:
    // Constructor
    BankAccount(double initialBalance, string accNumber) : balance(initialBalance), accountNumber(accNumber) {}

    // Getter for balance
    double getBalance() const {
        return balance;
    }

    // Getter for account number
    const string& getAccountNumber() const {
        return accountNumber;
    }

    // Method to withdraw amount
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << BLUE << "Successful Withdraw. Remaining balance: Rs" << balance << RESET << endl;
        }
        else if (amount <= 0) {
            throw invalid_argument(RED "Invalid Withdraw amount. Amount must be greater than zero." RESET);
        }
        else {
            throw runtime_error(RED "Insufficient balance. You have Rs" + to_string(balance) + " in your account, but tried to withdraw Rs" + to_string(amount) + "." RESET);
        }
    }

    // Method to deposit amount
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << BLUE << "Successful deposit. New balance: Rs" << balance << RESET << endl;
        }
        else {
            throw invalid_argument(RED "Invalid deposit amount. Amount must be greater than zero." RESET);
        }
    }

    // Method to transfer funds to another account
    void transferFunds(BankAccount& receiver, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            receiver.balance += amount;
            cout << BLUE << "Funds transfer successful. Sender's remaining balance: Rs" << balance << RESET << endl;
            cout << BLUE << "Receiver's new balance: Rs" << receiver.balance << RESET << endl;
        }
        else if (amount <= 0) {
            throw invalid_argument(RED "Invalid transfer amount. Amount must be greater than zero." RESET);
        }
        else {
            throw runtime_error(RED "Insufficient funds. You have Rs" + to_string(balance) + " in your account, but tried to transfer Rs" + to_string(amount) + "." RESET);
        }
    }
};

// ATM class definition
class ATM {
private:
    vector<BankAccount> accounts;   // Vector to store bank accounts
    int pin;                        // PIN for ATM access
    chrono::time_point<chrono::system_clock> lastTransactionTime; // Last transaction time

public:
    // Constructor
    ATM(const vector<pair<double, string>>& initialAccounts, const string& pinFile)
        : lastTransactionTime(chrono::system_clock::now()) {
        for (const auto& acc : initialAccounts) {
            accounts.push_back(BankAccount(acc.first, acc.second));
        }
        pin = readPINFromFile(pinFile);
    }

    // Method to read PIN from file
    static int readPINFromFile(const string& pinFile) {
        ifstream file(pinFile);
        int pin;
        if (file >> pin) {
            return pin;
        }
        else {
            cout << YELLOW << "Error reading PIN from file. Using default PIN 1234." << RESET << endl;
            return 1234; // Default PIN if there's an error
        }
    }

    // Method to write PIN to file
    static void writePINToFile(const string& pinFile, int pin) {
        ofstream file(pinFile);
        if (file.is_open()) {
            file << pin;
            file.close();
        }
        else {
            cout << RED << "Error writing PIN to file." << RESET << endl;
        }
    }

    // Method to clear the screen
    void clear() {
        system(CLEAR_SCREEN);
        cout << LIGHT_CYAN << "-------WELCOME TO HABIB BANK LIMITED-------" << RESET << endl;
    }

    // Method to display welcome message
    void welcomeMessage() const {
        cout << LIGHT_CYAN << "-------WELCOME TO HABIB BANK LIMITED-------" << RESET << endl;
    }

    // Method to simulate card insertion
    void insertCard() const {
        cout << LIGHT_GREEN << "Please insert the card in the machine" << RESET << endl;
    }

    // Method to validate PIN
    bool validatePin() {
        int inputPin;
        while (true) {
            cout << LIGHT_GREEN << "Please enter the 4-digit pin: " << RESET;
            if (cin >> inputPin) {
                if (inputPin == pin) {
                    cout << YELLOW << "Please wait for the processing" << RESET << endl;
                    cout << endl;
                    return true;
                }
                else {
                    cout << RED << "Invalid PIN. Please try again." << RESET << endl;
                }
            }
            else {
                cout << RED << "Invalid input. Please enter a numeric PIN." << RESET << endl;
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
            }
        }
        cout << endl;
    }

    // Method to display ATM menu
    void showMenu() const {
        cout << BLUE << "A. Withdraw" << RESET << endl;
        cout << BLUE << "B. Deposit" << RESET << endl;
        cout << BLUE << "C. Balance Inquiry" << RESET << endl;
        cout << BLUE << "D. Transfer Funds" << RESET << endl;
        cout << BLUE << "E. Change PIN" << RESET << endl;
        cout << BLUE << "F. EXIT" << RESET << endl;
    }

    // Method to handle ATM transactions
    void handleTransaction(const string& pinFile) {
        char option;
        
        do {
            showMenu();
            cout << LIGHT_BLUE << "********************************" << RESET << endl;
            cout << LIGHT_GREEN << "please enter your desired choice" << RESET << endl;
            cin >> option;
            cout << LIGHT_BLUE << "********************************" << RESET << endl;
            try {
                switch (option) {
                case 'a':
                case 'A': {
                    double amount;
                    while (true) {
                        cout << LIGHT_GREEN << "Please enter the amount for Withdraw: Rs " << RESET;
                        if (cin >> amount) {
                            try {
                                accounts[0].withdraw(amount);
                                break;
                            }
                            catch (const invalid_argument& ex) {
                                cout << RED << "Error: " << ex.what() << RESET << endl;
                            }
                            catch (const runtime_error& ex) {
                                cout << RED << "Error: " << ex.what() << RESET << endl;
                            }
                        }
                        else {
                            cout << RED << "Invalid input. Please enter a numeric amount." << RESET << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                        }
                    }
                    break;
                }
                case 'b':
                case 'B': {
                    double amount;
                    while (true) {
                        cout << LIGHT_GREEN << "Please enter the amount to be deposited: Rs " << RESET;
                        if (cin >> amount) {
                            try {
                                accounts[0].deposit(amount);
                                break;
                            }
                            catch (const invalid_argument& ex) {
                                cout << RED << "Error: " << ex.what() << RESET << endl;
                            }
                        }
                        else {
                            cout << RED << "Invalid input. Please enter a numeric amount." << RESET << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                        }
                    }
                    break;
                }
                case 'c':
                case 'C':
                    cout << BLUE << "Current Balance for Account 1: Rs" << accounts[0].getBalance() << RESET << endl;
                    break;
                case 'd':
                case 'D': {
                    double amount;
                    string receiverAccountNumber = "123456";
                    while (true) {
                        cout << LIGHT_GREEN << "Enter the amount to transfer: Rs " << RESET;
                        if (cin >> amount) {
                            try {
                                for (BankAccount& acc : accounts) {
                                    if (acc.getAccountNumber() == receiverAccountNumber) {
                                        accounts[0].transferFunds(acc, amount);
                                        break;
                                    }
                                }
                                break;
                            }
                            catch (const invalid_argument& ex) {
                                cout << RED << "Error: " << ex.what() << RESET << endl;
                            }
                            catch (const runtime_error& ex) {
                                cout << RED << "Error: " << ex.what() << RESET << endl;
                            }
                        }
                        else {
                            cout << RED << "Invalid input. Please enter a numeric amount." << RESET << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                        }
                    }
                    break;
                }
                case 'e':
                case 'E': {
                    int newPIN;
                    cout << LIGHT_GREEN << "Enter the new 4-digit pin: ";
                    cin >> newPIN;
                    int verifyPIN;
                    cout << LIGHT_GREEN << "Please enter the new pin again to verify: ";
                    cin >> verifyPIN;
                    if (newPIN == verifyPIN) {
                        pin = newPIN; // Update the pin
                        writePINToFile(pinFile, pin); // Save the new pin to file
                        cout << BLUE << "Congratulations, Your pin has been successfully changed." << RESET << endl;
                    }
                    else {
                        cout << RED << "PIN verification failed. Please try again." << RESET << endl;
                    }
                    break;
                }
                case 'f':
                case 'F':
                    cout << LIGHT_CYAN << "EXITING. Thank you!" << RESET << endl;
                    return; // Exit the function, effectively ending the program
                default:
                    cout << RED << "INVALID. Please select the correct option." << RESET << endl;
                    break;
                }
                logTransaction(option);
                lastTransactionTime = chrono::system_clock::now();

                // Prompt to continue or exit
                char continueOption;
                cout << LIGHT_GREEN << "Do you want to continue (C) or exit (E)? ";
                cin >> continueOption;
                if (continueOption == 'E' || continueOption == 'e') {
                    cout << LIGHT_CYAN << "EXITING. Thank you!" << RESET << endl;
                    return; // Exit the function, effectively ending the program
                }
                clear();
            }
            catch (const exception& ex) {
                cout << RED << "Error: " << ex.what() << RESET << endl;
            }
        } while (option != 'f' && option != 'F');
    }

    // Method to log transactions to a file
    void logTransaction(char option) {
        auto now = chrono::system_clock::to_time_t(lastTransactionTime);
        char timeBuffer[26];
        ctime_r(&now, timeBuffer); // Using ctime_r instead of ctime_s for macOS compatibility
        ofstream logFile("transaction.log", ios::app);
        if (logFile.is_open()) {
            logFile << "Transaction: " << option << " - Time: " << timeBuffer;
            logFile.close();
        }
        else {
            cout << RED << "Error opening log file." << RESET << endl;
        }
    }
};

int main() {
    string pinFile = "pin.txt"; // File to store PIN
    vector<pair<double, string> > initialAccounts = { {10000.78, "654321"}, {5000.0, "123456"} }; // Initial accounts
    ATM atm(initialAccounts, pinFile);

    // Show welcome message
    atm.welcomeMessage();

    // Simulate card insertion
    atm.insertCard();

    // Validate PIN
    while (!atm.validatePin()) {
        atm.insertCard();
    }
    // Handle transactions
    atm.handleTransaction(pinFile);

    return 0;
}
