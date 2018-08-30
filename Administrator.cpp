/**
 * Creator: Luke Welton (law0047)
 * Filename: Administrator.cpp
 *
 * I did not use any outside sources for this file.
 **/

#include <iostream>
#include "Administrator.h"
#include "System.h"

UserData Administrator::addBranchStaff() {
    UserData returnData;

    cout << "What is the new user's username?\t";
    returnData.username = System::unLoop();

    cout << "What is the new user's password?\t";
    returnData.password = System::pwLoop();

    cout << "Is the new user an administrator (Y/N)?\t";
    returnData.isAdmin = System::ynLoop();

    return returnData;
}

string Administrator::promoteBranchStaff() {
    string username;

    cout << "Which user would you like to promote?\t";
    cin >> username;

    return username;
}

string Administrator::deleteBranchStaff() {
    string username;

    cout << "Which user would you like to delete?\t";
    cin >> username;

    if (username == info.username) {
        cout << "You cannot delete your own account." << endl;
        return "";
    }

    string myPassword;
    cout << "Enter your password to continue:\t";

    do {
        cin >> myPassword;

        if (myPassword != info.password) {
            cout << "Incorrect password.\t";
        }
    } while (myPassword != info.password);

    return username;
}

Administrator::~Administrator() {}

