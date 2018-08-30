/**
 * Creator: Luke Welton (law0047)
 * Filename: DataStructures.h
 *
 * I did not use any outside sources for this file.
 **/

#ifndef PROJECT_2_DATASTRUCTURES_H
#define PROJECT_2_DATASTRUCTURES_H

#include <string>
using namespace std;

struct UserData {
    string username, password;
    bool isAdmin;
};

struct ClientData {
    string name, address, employer;
    int SSN, income;
};

struct AccountData {
    int number, owner;
    char type;
    double balance;
};

#endif //PROJECT_2_DATASTRUCTURES_H
