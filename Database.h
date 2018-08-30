/**
 * Creator: Luke Welton (law0047)
 * Filename: Database.h
 *
 * I did not use any outside sources for this file.
 **/

#ifndef PROJECT_2_DATABASE_H
#define PROJECT_2_DATABASE_H


#include <vector>
#include "DataStructures.h"

class Database {
private:
    vector<UserData> staff;
    vector<ClientData> clients;
    vector<AccountData> accounts;
public:
    Database();

    void loadStaff(ifstream &inStream, string fileName = "staff.txt");
    void loadClients(ifstream &inStream, string fileName = "client-info.txt");
    void loadAccounts(ifstream &inStream, string fileName = "account-info.txt");
    void createDefaultAdmin(string fileName);

    UserData * findStaff(string nameIn);
    ClientData * findClient(int ssnIn);
    AccountData * findAccount(int numIn);
    vector<AccountData> findMatchingAccounts(int ownerSSN);

    bool staffExists(string username);
    bool clientExists(int clientSSN);
    bool accountExists(int accNum);

    bool correctLogin(string username, string password);

    void addStaff(UserData dataIn);
    void addClient(ClientData dataIn);
    void addAccount(AccountData dataIn);

    void changePassword(string username, string newPass);
    void changePerms(string username, bool toAdmin);
    void editClient(ClientData dataIn);
    void deposit(int accountNum, double amount);
    void withdraw(int accountNum, double amount);

    void deleteStaff(string username);
    void deleteAccount(int accNum);

    void displayStaff();
    void displayClient(int ssnIn);
    void displayAccounts(int ssnIn);

    void save();
    void saveStaff(ofstream &outStream, string fileName = "staff.txt");
    void saveClients(ofstream &outStream, string fileName = "client-info.txt");
    void saveAccounts(ofstream &outStream, string fileName = "account-info.txt");

    int generateAccountNum();
};

#endif //PROJECT_2_DATABASE_H