/**
 * Creator: Luke Welton (law0047)
 * Filename: Administrator.h
 *
 * I did not use any outside sources for this file.
 **/

#ifndef PROJECT_2_ADMINISTRATOR_H
#define PROJECT_2_ADMINISTRATOR_H

#include "StaffMember.h"

class Administrator : public StaffMember {
private:
public:
    Administrator(UserData dataIn) : StaffMember(dataIn) {}

    UserData addBranchStaff();
    string deleteBranchStaff();
    string promoteBranchStaff();

    ~Administrator();
};


#endif //PROJECT_2_ADMINISTRATOR_H
