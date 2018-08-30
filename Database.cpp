/**
 * Creator: Luke Welton (law0047)
 * Filename: Database.cpp
 *
 * I did not use any outside sources for this file.
 **/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include "Database.h"
#include "System.h"

Database::Database() {
    ifstream inStream;

    loadStaff(inStream);
    loadClients(inStream);
    loadAccounts(inStream);
}

void Database::loadStaff(ifstream &inStream, string fileName) {
    inStream.open((char*)fileName.c_str());

    int tries = 0;
    while (!inStream && tries < 10) {
        tries++;
        inStream.close();
        createDefaultAdmin(fileName);
        inStream.open((char*)fileName.c_str());
    }
    if (tries >= 10) {
        cout << "Something went wrong while trying to access the database." << endl;
        exit(1);
    }

    while (inStream) {
        UserData user;
        getline(inStream, user.username);
        if (user.username == "") {
            break;
        }
        getline(inStream, user.password);
        inStream >> user.isAdmin;

        staff.push_back(user);
    }

    inStream.close();
}

void Database::loadClients(ifstream &inStream, string fileName) {
    inStream.open((char*)fileName.c_str());

    while (inStream) {
        ClientData client;
        inStream >> client.SSN;
        inStream.ignore();
        getline(inStream, client.name);
        if (client.name == "") {
            break;
        }
        getline(inStream, client.address);
        getline(inStream, client.employer);
        inStream >> client.income;

        clients.push_back(client);
    }

    inStream.close();
}

void Database::loadAccounts(ifstream &inStream, string fileName) {
    inStream.open((char*)fileName.c_str());

    while (inStream) {
        AccountData acc;
        inStream >> acc.number;
        inStream >> acc.owner;

        string typeTemp;
        inStream >> typeTemp;
        if (typeTemp == "") {
            break;
        }
        acc.type = typeTemp[0];

        inStream >> acc.balance;

        accounts.push_back(acc);
    }

    inStream.close();
}

void Database::createDefaultAdmin(string fileName) {
    ofstream outStream;
    outStream.open((char*)fileName.c_str());
    outStream << "admin" << endl << "0000" << endl << "1" << endl;
    outStream.close();
}

UserData * Database::findStaff(string nameIn) {
    for (unsigned i = 0; i < staff.size(); i++) {
        if (staff[i].username == nameIn) {
            return &staff[i];
        }
    }

    static UserData notFound;
    notFound.username = "";
    return &notFound;
}

ClientData * Database::findClient(int ssnIn) {
    for (unsigned i = 0; i < clients.size(); i++) {
        if (clients[i].SSN == ssnIn) {
            return &clients[i];
        }
    }

    static ClientData notFound;
    notFound.SSN = -1;
    return &notFound;
}

AccountData * Database::findAccount(int numIn) {
    for (unsigned i = 0; i < accounts.size(); i++) {
        if (accounts[i].number == numIn) {
            return &accounts[i];
        }
    }

    static AccountData notFound;
    notFound.number = -1;
    return &notFound;
}

vector<AccountData> Database::findMatchingAccounts(int ownerSSN) {
    vector<AccountData> results;

    for (unsigned i = 0; i < accounts.size(); i++) {
        if (accounts[i].owner == ownerSSN) {
            results.push_back(accounts[i]);
        }
    }

    return results;
}

bool Database::staffExists(string username) {
    return findStaff(username)->username != "";
}

bool Database::clientExists(int clientSSN) {
    return findClient(clientSSN)->SSN >= 0;
}

bool Database::accountExists(int accNum) {
    return findAccount(accNum)->number >= 0;
}

bool Database::correctLogin(string username, string password) {
    return staffExists(username) && findStaff(username)->password == password;
}

void Database::addStaff(UserData dataIn) {
    if (!staffExists(dataIn.username)) {
        staff.push_back(dataIn);

        ofstream outStream;
        saveStaff(outStream);
        cout << "Staff Account has been created for " << dataIn.username << endl;
    }
    else {
        cout << "A staff account already exists with that username!" << endl;
    }
}

void Database::addClient(ClientData dataIn) {
    if (!clientExists(dataIn.SSN)) {
        clients.push_back(dataIn);

        ofstream outStream;
        saveClients(outStream);
        cout << "Client Data created for " << dataIn.name << endl;
    }
    else {
        cout << "A client with that SSN already exists!" << endl;
    }
}

void Database::addAccount(AccountData dataIn) {
    if (clientExists(dataIn.owner)) {
        dataIn.number = generateAccountNum();
        accounts.push_back(dataIn);

        ofstream outStream;
        saveAccounts(outStream);
        cout << "Account #" << setw(6) << setfill('0') << dataIn.number << " created." << endl << setfill(' ');
    }
    else {
        cout << "No client is attached to the given SSN." << endl;
    }
}

void Database::changePassword(string username, string newPass) {
    if (staffExists(username)) {
        UserData* foundUser = findStaff(username);
        foundUser->password = newPass;

        ofstream outStream;
        saveStaff(outStream);
        cout << "The password for " << foundUser->username << " has been changed." << endl;
    }
    else {
        cout << "No user with the given username was found." << endl;
    }
}

void Database::changePerms(string username, bool toAdmin) {
    if (staffExists(username)) {
        UserData* foundUser = findStaff(username);
        foundUser->isAdmin = toAdmin;

        ofstream outStream;
        saveStaff(outStream);
        cout << "The permissions for " << foundUser->username << " have been updated." << endl;
    }
    else {
        cout << "No user with the given username was found." << endl;
    }
}

void Database::editClient(ClientData dataIn) {
    if (clientExists(dataIn.SSN)) {
        ClientData* foundClient = findClient(dataIn.SSN);
        foundClient->address = dataIn.address;
        foundClient->employer = dataIn.employer;
        foundClient->income = dataIn.income;
        foundClient->name = dataIn.name;

        ofstream outStream;
        saveClients(outStream);
        cout << "The information for " << foundClient->name << " has been updated." << endl;
    }
    else {
        cout << "No client was found with the given SSN." << endl;
    }
}

void Database::deposit(int accountNum, double amount) {
    if (amount < 0) {
        withdraw(accountNum, -amount);
    }
    else if (accountExists(accountNum)) {
        AccountData* foundAccount = findAccount(accountNum);
        foundAccount->balance += amount;

        ofstream outStream;
        this->saveAccounts(outStream);
        cout << "Account #" << accountNum << " now has a balance of $";
        cout.setf(ios::showpoint);
        cout << setprecision(2) << foundAccount->balance << endl;
    }
    else {
        cout << "No account was found with the given account number." << endl;
    }
}

void Database::withdraw(int accountNum, double amount) {
    if (amount < 0) {
        deposit(accountNum, -amount);
    }
    else if (accountExists(accountNum)) {
        AccountData* foundAccount = findAccount(accountNum);

        if (amount > foundAccount->balance) {
            cout << "This withdrawal will put this account into the negative!" << endl;
            cout << "Are you sure you want to withdraw this amount? (Y/N)\t";

            if (!System::ynLoop()) {
                return;
            }
        }

        foundAccount->balance -= amount;

        ofstream outStream;
        this->saveAccounts(outStream);
        cout << "Account #" << accountNum << " now has a balance of $";
        cout.setf(ios::showpoint);
        cout << setprecision(2) << foundAccount->balance << endl;
    }
    else {
        cout << "No account was found with the given account number." << endl;
    }
}

void Database::deleteStaff(string username) {
    if (staffExists(username)) {
        cout << "This will delete the user " << username << "." << endl;
        cout << "Are you sure you want to do this? (Y/N)\t";
        if (System::ynLoop()) {
            unsigned i = 0;
            while (staff[i].username != username && i < staff.size()) {
                i++;
            }

            if (i < staff.size()) {
                staff.erase(staff.begin() + i);

                ofstream outStream;
                saveStaff(outStream);
                cout << "The user " << username << " was deleted." << endl;
            }
        }
    }
    else if (username != "") {
        cout << "There is no staff member with the given username." << endl;
    }
}

void Database::deleteAccount(int accNum) {
    unsigned i = 0;
    while (accounts[i].number != accNum && i < accounts.size()) {
        i++;
    }

    if (i < accounts.size()) {
        cout << "Are you sure you want to delete this account? (Y/N)\t";

        if (System::ynLoop()) {
            double amountAtDeletion = accounts[i].balance;
            accounts.erase(accounts.begin() + i);

            ofstream outStream;
            saveAccounts(outStream);

            cout << "Account #" << accNum << " has been deleted." << endl;
            cout.setf(ios::showpoint);
            cout << "Its balance at the time of deletion was $" << setprecision(2) << amountAtDeletion;
        }
    }
    else {
        cout << "No account was found with the given account number." << endl;
    }
}

void Database::displayStaff() {
    unsigned maxSize = 8;
    for (unsigned i = 0; i < staff.size(); i++) {
        maxSize = maxSize < staff[i].username.size() ? staff[i].username.size() : maxSize;
    }
    maxSize += 2;

    cout << "There are " << staff.size() << " users in the system." << endl;
    cout << right << setw(maxSize) << "Username" << setw(22) << "System Role" << endl;
    for (unsigned i = 0; i < staff.size(); i++) {
        cout << right << setw(maxSize) << staff[i].username
             << setw(22) << (staff[i].isAdmin ? "System Administrator" : "Branch Staff") << endl;
    }
}

void Database::displayClient(int ssnIn) {
    ClientData* clientData = findClient(ssnIn);

    cout << right << setw(max(static_cast<int>(clientData->name.size()) + 2, 6)) << "Name" << setw(11) << "SSN"
         << setw(max(static_cast<int>(clientData->address.size()) + 2, 9)) << "Address"
         << setw(max(static_cast<int>(clientData->employer.size()) + 2, 10)) << "Employer"
         << setw(10) << "Salary" << endl;

    ostringstream ostrs;
    ostrs << "$" << clientData->income;

    cout << right << setw(max(static_cast<int>(clientData->name.size()) + 2, 6)) << clientData->name
         << "  " << setw(9) << setfill('0') << clientData->SSN
         << setw(max(static_cast<int>(clientData->address.size()) + 2, 9)) << setfill(' ') << clientData->address
         << setw(max(static_cast<int>(clientData->employer.size()) + 2, 10)) << clientData->employer
         << setw(10) << ostrs.str() << endl;
}

void Database::displayAccounts(int ssnIn) {
    vector<AccountData> foundAccounts = findMatchingAccounts(ssnIn);

    double maxAmount = 999999.99;
    for (unsigned i = 0; i < foundAccounts.size(); i++) {
        maxAmount = max(maxAmount, foundAccounts[i].balance);
    }

    ostringstream ostrs;
    ostrs.setf(ios::fixed);
    ostrs.setf(ios::showpoint);
    ostrs << setprecision(2) << maxAmount;

    string header = findClient(ssnIn)->name + "'s Accounts";
    string spacer = "====";
    for (unsigned i = 0; i < header.size(); i++) {
        spacer += "=";
    }

    cout << spacer << endl << "| " << header << " |" << endl << spacer << endl;
    cout << right << setw(8) << "Number" << setw(10) << "Type"
         << setw(static_cast<int>(ostrs.tellp()) + 2) << "Balance" << endl;

    for (unsigned i = 0; i < foundAccounts.size(); i++) {
        string typeName = foundAccounts[i].type == 'C' ? "Checking" : "Savings";

        ostringstream balStream;
        balStream.setf(ios::fixed);
        balStream.setf(ios::showpoint);
        balStream << "$" << setprecision(2) << foundAccounts[i].balance;

        cout << right << "  " << setw(6) << setfill('0') << foundAccounts[i].number
             << setfill(' ') << setw(10) << typeName;
        cout << setw(static_cast<int>(ostrs.tellp()) + 2) << setprecision(2) << balStream.str() << endl;
    }
}

void Database::save() {
    ofstream outStream;

    saveStaff(outStream);
    saveClients(outStream);
    saveAccounts(outStream);

    cout << "All data has been saved to their respective files." << endl;
}

void Database::saveStaff(ofstream &outStream, string fileName) {
    outStream.open((char*)fileName.c_str());

    for (unsigned i = 0; i < staff.size(); i++) {
        outStream << staff[i].username << endl << staff[i].password << endl << (staff[i].isAdmin ? 1 : 0) << endl;
    }

    outStream.close();
}

void Database::saveClients(ofstream &outStream, string fileName) {
    outStream.open((char*)fileName.c_str());

    for (unsigned i = 0; i < clients.size(); i++) {
        outStream << clients[i].SSN << endl << clients[i].name << endl << clients[i].address << endl
                  << clients[i].employer << endl << clients[i].income << endl;

    }

    outStream.close();
}

void Database::saveAccounts(ofstream &outStream, string fileName) {
    outStream.open((char*)fileName.c_str());

    for (unsigned i = 0; i < accounts.size(); i++) {
        outStream << accounts[i].number << endl << accounts[i].owner << endl << accounts[i].type << endl << accounts[i].balance << endl;
    }

    outStream.close();
}

int Database::generateAccountNum() {
    int num = 0;

    do {
        num = System::getRandomInt(0, 1000000);
    } while (accountExists(num));

    return num;
}