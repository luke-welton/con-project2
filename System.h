/**
 * Creator: Luke Welton (law0047)
 * Filename: System.h
 *
 * I did not use any outside sources for this file.
 **/

#ifndef PROJECT_2_SYSTEM_H
#define PROJECT_2_SYSTEM_H

#include <climits>
#include "Database.h"

class System {
private:
    Database* db;
public:
    System();

    bool displayLogin();

    static int getRandomInt(int min, int max);

    static bool ynLoop();
    static int intLoop(int min, int max = INT_MAX);
    static string unLoop();
    static string pwLoop(string prevPass = "");

    ~System();
};


#endif //PROJECT_2_SYSTEM_H
