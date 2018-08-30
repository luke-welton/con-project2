/**
 * Creator: Luke Welton (law0047)
 * Filename: Menu.h
 *
 * I did not use any outside sources for this file.
 **/

#ifndef PROJECT_2_MENU_H
#define PROJECT_2_MENU_H

#include <string>
#include <vector>
using namespace std;

class Menu {
private:
    string name;
    vector<string> options;
public:
    Menu(int preset);

    void display();
    int getSelection();
};


#endif //PROJECT_2_MENU_H
