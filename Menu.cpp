/**
 * Creator: Luke Welton (law0047)
 * Filename: Menu.cpp
 *
 * I did not use any outside sources for this file.
 **/

#include <iostream>
#include "Menu.h"
#include "System.h"

Menu::Menu(int preset) {
    switch (preset) {
        case 0: {
            name = "Branch Staff"; //Main Menu

            options.push_back("Client and Account Management");
            options.push_back("Change Password");
            options.push_back("Log Out");
            break;
        }

        case 1: {
            name = "System Administration"; //Admin Main Menu

            options.push_back("Staff Management");
            options.push_back("Client and Account Management");
            options.push_back("Change Password");
            options.push_back("Log Out");
            break;
        }

        case 2: {
            name = "Client and Account Management";

            options.push_back("Add a Client");
            options.push_back("Add an Account");
            options.push_back("Edit Client Information");
            options.push_back("Display a Client's Accounts");
            options.push_back("Manage an Account");
            //options.push_back("Delete a Client");
            options.push_back("Delete an Account");
            options.push_back("Save Client and Account Information");
            options.push_back("Return to Main Menu");
            break;
        }

        case 3: {
            name = "Staff Management";

            options.push_back("Add Branch Staff Member");
            options.push_back("Promote Branch Staff Member");
            options.push_back("Delete Branch Staff Member");
            options.push_back("Display Branch Staff Members");
            options.push_back("Return to Main Menu");
            break;
        }

        case 4: {
            name = ""; // Deposit/Withdraw

            options.push_back("Deposit");
            options.push_back("Withdraw");
            options.push_back("Cancel");
            break;
        }

        case 5: {
            name = ""; //Login Menu

            options.push_back("Login");
            options.push_back("Quit");
            break;
        }

        default: {
            name = "";
        }
    }
}

void Menu::display() {
    if (name != "") {
        string title = "Teller Terminal System";
        string header = "==";
        for (unsigned i = 0; i < name.size() + title.size() + 3; i++) {
            header += "=";
        }
        header += "==";

        cout << endl << header << endl;
        cout << "| " << title << " - " << name << " |" << endl;
        cout << header << endl << endl;
    }

    for (unsigned i = 0; i < options.size(); i++) {
        cout << "\t" << (i + 1) << ") " << options[i] << endl;
    }
    cout << endl << "Enter the number before the option.\t";
}

int Menu::getSelection() {
    return System::intLoop(1, static_cast<int>(options.size()));
}