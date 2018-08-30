/**
 * Creator: Luke Welton (law0047)
 * Filename: Session.cpp
 *
 * I did not use any outside sources for this file.
 **/

#include <iostream>
#include "Session.h"
#include "Menu.h"

Session::Session(StaffMember *userIn, Database *dbIn) {
    currentUser = userIn;
    db = dbIn;
}

void Session::begin() {
    bool logout = false;
    while (!logout) {
        logout = displaySessionMenu();
    }
}

bool Session::displaySessionMenu() {
    int menuNum = currentUser->isAdmin() ? 1 : 0;
    Menu sessionMenu(menuNum);

    sessionMenu.display();
    switch (sessionMenu.getSelection() - menuNum) {
        //Staff Management
        case 0: {
            bool returnToSession = false;
            while (!returnToSession) {
                returnToSession = staffManagement();
            }
            return false;
        }

        //Client & Account Management
        case 1: {
            bool returnToSession = false;
            while (!returnToSession) {
                returnToSession = clientManagement();
            }
            return false;
        }

        //Change Password
        case 2: {
            string newPassword = currentUser->changePassword();

            if (newPassword == "") {
                return true;
            }

            db->changePassword(currentUser->getUsername(), newPassword);
            return false;
        }

        //Log Out
        default: {
            return true;
        }
    }
}

bool Session::staffManagement() {
    if (!currentUser->isAdmin()) {
        cout << "Sorry, you don't have permissions to access this feature!" << endl;
        cout << "Contact your systems administrator for more information." << endl;
        return true;
    }

    Menu staffMenu(3);
    staffMenu.display();

    switch (staffMenu.getSelection()) {
        //Add Branch Staff
        case 1: {
            db->addStaff(currentUser->addBranchStaff());
            return false;
        }

        //Promote Branch Staff
        case 2: {
            db->changePerms(currentUser->promoteBranchStaff(), true);
            return false;
        }

        //Delete Branch Staff
        case 3: {
            db->deleteStaff(currentUser->deleteBranchStaff());
            return false;
        }

        //Display Branch Staff
        case 4: {
            db->displayStaff();
            return false;
        }

        //Return
        default: {
            return true;
        }
    }
}

bool Session::clientManagement() {
    Menu clientMenu(2);
    clientMenu.display();

    switch (clientMenu.getSelection()) {
        //Add Client
        case 1: {
            db->addClient(currentUser->addClient());
            return false;
        }

        //Add Account
        case 2: {
            db->addAccount(currentUser->addAccount());
            return false;
        }

        //Edit Client Info
        case 3: {
            db->editClient(currentUser->editClient(db));
            return false;
        }

        //Display Accounts
        case 4: {
            currentUser->displayAccounts(db);
            return false;
        }

        //Manage Account
        case 5: {
            currentUser->manageAccount(db);
            return false;
        }

        //Delete Account
        case 6: {
            db->deleteAccount(currentUser->deleteAccount());
            return false;
        }

        //Save Info
        case 7: {
            db->save();
            return false;
        }

        //Return
        default: {
            return true;
        }
    }
}

Session::~Session() {
    delete currentUser;
}
