#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdio>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string customerName;
    float balance;

public:
    BankAccount(int accNo = 0, string name = "", float bal = 0.0) {
        accountNumber = accNo;
        customerName = name;
        balance = bal;
    }

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, customerName);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() const {
        cout << left << setw(15) << accountNumber
             << setw(25) << customerName
             << setw(15) << balance << endl;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    void deposit() {
        float amount;

        cout << "Enter Amount to Deposit: ";
        cin >> amount;

        balance += amount;

        cout << "Amount Deposited Successfully!" << endl;
        cout << "Updated Balance: " << balance << endl;
    }

    void withdraw() {
        float amount;

        cout << "Enter Amount to Withdraw: ";
        cin >> amount;

        if (amount > balance) {
            cout << "Insufficient Balance!" << endl;
        }
        else {
            balance -= amount;

            cout << "Withdrawal Successful!" << endl;
            cout << "Remaining Balance: " << balance << endl;
        }
    }

    void checkBalance() const {
        cout << "Current Balance: " << balance << endl;
    }

    void writeToFile(ofstream &outFile) {
        outFile << accountNumber << endl;
        outFile << customerName << endl;
        outFile << balance << endl;
    }

    void readFromFile(ifstream &inFile) {
        inFile >> accountNumber;
        inFile.ignore();

        getline(inFile, customerName);

        inFile >> balance;
        inFile.ignore();
    }
};

void createNewAccount() {
    BankAccount acc;

    ofstream outFile("bank.txt", ios::app);

    if (!outFile) {
        cout << "File Error!" << endl;
        return;
    }

    acc.createAccount();
    acc.writeToFile(outFile);

    outFile.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts() {
    ifstream inFile("bank.txt");

    if (!inFile) {
        cout << "No Records Found!" << endl;
        return;
    }

    BankAccount acc;

    cout << "\n================ ACCOUNT RECORDS ================\n";

    cout << left << setw(15) << "ACCOUNT NO"
         << setw(25) << "CUSTOMER NAME"
         << setw(15) << "BALANCE" << endl;

    cout << "----------------------------------------------------------\n";

    while (inFile.peek() != EOF) {
        acc.readFromFile(inFile);
        acc.displayAccount();
    }

    inFile.close();
}

void depositAmount() {
    int accNo;
    bool found = false;

    cout << "Enter Account Number: ";
    cin >> accNo;

    ifstream inFile("bank.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cout << "File Error!" << endl;
        return;
    }

    BankAccount acc;

    while (inFile.peek() != EOF) {
        acc.readFromFile(inFile);

        if (acc.getAccountNumber() == accNo) {
            acc.deposit();
            found = true;
        }

        acc.writeToFile(tempFile);
    }

    inFile.close();
    tempFile.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (!found) {
        cout << "Account Not Found!" << endl;
    }
}

void withdrawAmount() {
    int accNo;
    bool found = false;

    cout << "Enter Account Number: ";
    cin >> accNo;

    ifstream inFile("bank.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cout << "File Error!" << endl;
        return;
    }

    BankAccount acc;

    while (inFile.peek() != EOF) {
        acc.readFromFile(inFile);

        if (acc.getAccountNumber() == accNo) {
            acc.withdraw();
            found = true;
        }

        acc.writeToFile(tempFile);
    }

    inFile.close();
    tempFile.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (!found) {
        cout << "Account Not Found!" << endl;
    }
}

void balanceInquiry() {
    int accNo;
    bool found = false;

    cout << "Enter Account Number: ";
    cin >> accNo;

    ifstream inFile("bank.txt");

    if (!inFile) {
        cout << "File Error!" << endl;
        return;
    }

    BankAccount acc;

    while (inFile.peek() != EOF) {
        acc.readFromFile(inFile);

        if (acc.getAccountNumber() == accNo) {
            cout << "\nAccount Found!\n";
            acc.checkBalance();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account Not Found!" << endl;
    }

    inFile.close();
}

int main() {
    int choice;

    while (true) {
        cout << "\n=========== BANK MANAGEMENT APPLICATION ===========\n";

        cout << "1. Create New Account" << endl;
        cout << "2. Display All Accounts" << endl;
        cout << "3. Deposit Amount" << endl;
        cout << "4. Withdraw Amount" << endl;
        cout << "5. Balance Inquiry" << endl;
        cout << "6. Exit" << endl << endl;

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createNewAccount();
            break;

        case 2:
            displayAccounts();
            break;

        case 3:
            depositAmount();
            break;

        case 4:
            withdrawAmount();
            break;

        case 5:
            balanceInquiry();
            break;

        case 6:
            cout << "Exiting Application..." << endl;
            return 0;

        default:
            cout << "Invalid Choice! Please Try Again." << endl;
        }
    }

    return 0;
}
