/**
 * Creator: Luke Welton (law0047)
 * Filename: StaffMember.cpp
 *
 * I did not use any outside sources for this file.
 **/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "StaffMember.h"
#include "System.h"
#include "Menu.h"

StaffMember::StaffMember(UserData infoIn) {
    info = infoIn;
}

string StaffMember::getUsername() {
    return info.username;
}

bool StaffMember::isAdmin() {
    return info.isAdmin;
}


string StaffMember::changePassword() {
    string currentPassword = "";
    cout << "What is your current password?\t";

    int tries = 0;
    while (currentPassword != info.password && tries < 10) {
        cin >> currentPassword;
        tries++;

        if (currentPassword != info.password) {
            cout << "Incorrect password entered.\t";
        }
    }

    if (tries >= 10) {
        cout << "You have exceeded the number of allowed attempts." << endl;
        cout << "You will now be logged out." << endl;
        return "";
    }
    else {
        cout << "What would you like your new password to be?\t";
        string newPass = System::pwLoop(info.password);

        info.password = newPass;
        return newPass;
    }
}

UserData StaffMember::addBranchStaff() {
    cout << "Inheritance/Permissions on addBranchStaff() not working properly!" << endl;
    exit(1);
}

string StaffMember::promoteBranchStaff() {
    cout << "Inheritance/Permissions on promoteBranchStaff() not working properly!" << endl;
    exit(1);
}

string StaffMember::deleteBranchStaff() {
    cout << "Inheritance/Permissions on deleteBranchStaff() not working properly!" << endl;
    exit(1);
}

ClientData StaffMember::addClient() {
    ClientData returnData;

    cout << "What is the client's name?\t";
    do {
        getline(cin, returnData.name);

        if (returnData.name == "") {
            cout << "The name cannot be blank" << endl;
        }
    } while (returnData.name == "");

    cout << "What is the client's SSN? (enter as #########)\t";
    do {
        returnData.SSN = System::intLoop(0);

        if (returnData.SSN < 0) {
            cout << "Don't try to trick the system, we know SSNs won't be negative!\t";
        }
    } while (returnData.SSN < 0);

    cout << "What is the client's address?\t";
    getline(cin, returnData.address);
    returnData.address = returnData.address == "" ? "N/A" : returnData.address;

    cout << "Who is the client's employer?\t";
    getline(cin, returnData.employer);
    returnData.employer = returnData.employer == "" ? "N/A" : returnData.employer;

    cout << "How much is the client's income? (round to the nearest dollar)\t";
    returnData.income = System::intLoop(0);

    return returnData;
}

AccountData StaffMember::addAccount() {
    AccountData returnData;

    cout << "What is the SSN of the owner of the account?\t";
    returnData.owner = System::intLoop(0);

    cout << "What type of account is being opened?" << endl;
    cout << "Enter S for Savings or C for Checking\t";
    do {
        cin >> returnData.type;
        returnData.type = static_cast<char>(toupper(returnData.type));

        if (returnData.type != 'S' && returnData.type != 'C') {
            cout << "Please enter either S or C\t";
        }
    } while (returnData.type != 'S' && returnData.type != 'C');

    cout << "What is the starting balance for the account?\t";
    do {
        while (!(cin >> returnData.balance)) {
            cout << "Please enter a decimal number.\t";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (returnData.balance < 0.0) {
            cout << "The starting balance cannot be less than zero.\t";
        }
    } while (returnData.balance < 0.0);

    return returnData;
}

ClientData StaffMember::editClient(Database *db) {
    int clientSSN;
    cout << "What is the SSN of the client you want to change? (enter as #########)\t";
    do {
        clientSSN = System::intLoop(0);

        if (clientSSN < 0) {
            cout << "SSNs cannot be less than zero.\t";
            cin.clear();
        }
    } while (clientSSN < 0);

    if (db->clientExists(clientSSN)) {
        db->displayClient(clientSSN);
        cout << "Would you like to edit this client's data? (Y/N)\t";

        if (System::ynLoop()) {
            ClientData returnData;
            returnData.SSN = clientSSN;

            cin.ignore();
            cout << "Enter the client's name:\t";
            getline(cin, returnData.name);

            cout << "Enter the client's address:\t";
            getline(cin, returnData.address);

            cout << "Enter the client's employer:\t";
            getline(cin, returnData.employer);

            cout << "Enter the client's annual salary:\t";
            returnData.income = System::intLoop(0);

            return returnData;
        }
    }

    ClientData notFound;
    notFound.SSN = -1;
    return notFound;
}

void StaffMember::displayAccounts(Database *db) {
    int ssn;
    cout << "Enter the SSN of the user whose accounts you would like to view: " << endl;
    cout << "Use the format #########\t\t\t";
    ssn = System::intLoop(0);

    if (db->clientExists(ssn)) {
        db->displayAccounts(ssn);
    }
    else {
        cout << "No client was found with the given SSN." << endl;
    }
}

void StaffMember::manageAccount(Database *db) {
    int accountNum;
    cout << "Enter the account number to deposit or withdraw from:\t";
    accountNum = System::intLoop(0);

    if (db->accountExists(accountNum)) {
        Menu dwMenu(4);

        cout << "Would you like to deposit or withdraw?" << endl;
        dwMenu.display();

        switch (dwMenu.getSelection()) {
            case 1: {
                double amount;
                cout << "How much would you like to deposit?\nDo not include a dollar sign.\t";
                while (!(cin >> amount)) {
                    cout << "Please enter a number.\t\t";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                db->deposit(accountNum, amount);
                break;
            }
            case 2: {
                double amount;
                cout << "How much would you like to withdraw?\nDo not include a dollar sign.\t";
                while (!(cin >> amount)) {
                    cout << "Please enter a number.\t\t";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                db->withdraw(accountNum, amount);
                break;
            }
            default: {
                return;
            }
        }
    }
    else {
        cout << "No account was found with the given number." << endl;
    }
}

int StaffMember::deleteAccount() {
    int account;

    cout << "What is the number of the account you would like to delete?\t";
    account = System::intLoop(0);

    return account;
}

StaffMember::~StaffMember() {}