/**
 * Creator: Luke Welton (law0047)
 * Filename: StaffMember.h
 *
 * I did not use any outside sources for this file.
 **/

#ifndef PROJECT_2_STAFFMEMBER_H
#define PROJECT_2_STAFFMEMBER_H

#include "DataStructures.h"
#include "Database.h"

class StaffMember {
protected:
    UserData info;
public:
    StaffMember(UserData infoIn);

    string getUsername();
    bool isAdmin();

    string changePassword();

    virtual UserData addBranchStaff();
    virtual string promoteBranchStaff();
    virtual string deleteBranchStaff();
    virtual ~StaffMember();

    ClientData addClient();
    AccountData addAccount();
    ClientData editClient(Database* db);
    void displayAccounts(Database* db);
    void manageAccount(Database* db);
    int deleteAccount();
};


#endif //PROJECT_2_STAFFMEMBER_H
