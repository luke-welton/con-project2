/**
 * Hello! I'm very tired and I have a final in the morning,
 * so I'm going to be very brief with my description on this project.
 *
 * To compile this project, enter
 *  g++ -o Project2.exe Project2.cpp Administrator.cpp Database.cpp Menu.cpp Session.cpp StaffMember.cpp System.cpp
 *
 * And after that, enter
 *  ./Project2.exe
 *
 * and the program will be running.
 *
 * Creator: Luke Welton (law0047)
 * Filename: Project1.cpp
 **/

#include "System.h"

int main() {
    System boot;
    bool exit = false;

    while (!exit) {
        exit = boot.displayLogin();
    }

    return 0;
}