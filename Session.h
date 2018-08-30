/**
 * Creator: Luke Welton (law0047)
 * Filename: Session.cpp
 *
 * I did not use any outside sources for this file.
 **/

#ifndef PROJECT_2_SESSION_H
#define PROJECT_2_SESSION_H


#include "StaffMember.h"
#include "Database.h"

class Session {
private:
    StaffMember* currentUser;
    Database* db;
public:
    Session(StaffMember *userIn, Database *dbIn);

    void begin();

    bool displaySessionMenu();
    bool staffManagement();
    bool clientManagement();

    ~Session();
};


#endif //PROJECT_2_SESSION_H
