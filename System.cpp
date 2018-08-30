/**
 * Creator: Luke Welton (law0047)
 * Filename: System.cpp
 *
 * I did not use any outside sources for this file.
 **/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include "System.h"
#include "Menu.h"
#include "Session.h"
#include "Administrator.h"

using namespace std;

System::System() {
    srand(time(0));
    cout.setf(ios::fixed);

    db = new Database;
}

bool System::displayLogin() {
    cout << "\n===================================================" << endl;
    cout << "|   Welcome to the Auburn Branch of Tiger Bank!   |" << endl;
    cout << "===================================================\n" << endl;

    Menu loginMenu(5);
    loginMenu.display();

    switch (loginMenu.getSelection()) {
        case 1: {
            bool login = false;
            int tries = 0;
            string username, password;

            while (!login && tries < 10) {
                tries++;

                cout << endl;
                cout << "Username:\t";
                cin >> username;
                cout << "Password:\t";
                cin >> password;

                login = db->correctLogin(username, password);

                if (!login && tries < 10) {
                    cout << "The username or password is incorrect. Please try again!" << endl;
                }
            }

            if (login) {
                UserData* currentData = db->findStaff(username);
                StaffMember* currentUser;

                if (currentData->isAdmin) {
                    currentUser = new Administrator(*currentData);
                }
                else {
                    currentUser = new StaffMember(*currentData);
                }

                Session currentSession(currentUser, db);
                currentSession.begin();

                return false;
            }
            else {
                cout << "You have reached the maximum number of login attempts. Goodbye!" << endl;
                return true;
            }
        }
        default: {
            cout << "Goodbye!" << endl;
            return true;
        }
    }
}

int System::getRandomInt(int min, int max) {
    return rand() % (max - min) + min;
}

bool System::ynLoop() {
    char response = '?';

    while (!(response == 'N' || response == 'Y')) {
        cin >> response;
        response = static_cast<char>(toupper(response));

        if (!(response == 'N' || response == 'Y')) {
            cout << "Please enter either Y or N\t";
        }
    }

    return response == 'Y';
}

int System::intLoop(int min, int max) {
    int response = min - 1;

    while (response < min || response > max) {
        while (!(cin >> response)) {
            cout << "Please enter a number.\t";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (response < min || response > max) {
            cout << "Please enter a value greater than " << (min - 1);
            if (max == INT_MAX) {
                cout << " and less than " << (max + 1);
            }
            cout << ":\t";
        }
    }

    return response;
}

string System::unLoop() {
    string username = "";
    while (username == "" || username.find(' ') != string::npos) {
        cin >> username;

        if (username == "" || username.find(' ') != string::npos) {
            cout << "The username cannot be blank or contain spaces.\t";
        }
    }

    return username;
}

string System::pwLoop(string prevPass) {
    string password = "";
    while (password == "" || password.find(' ') != string::npos) {
        cin >> password;

        if (password == "" || password.find(' ') != string::npos) {
            cout << "The password cannot be blank or contain spaces.\t";
        }
        else if (password == prevPass) {
            cout << "The password cannot be the same as your previous password.\t";
        }
    }

    return password;
}

System::~System() {
    delete db;
}