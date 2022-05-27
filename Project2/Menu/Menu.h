

#ifndef DA_PROJECT_MENU_H
#define DA_PROJECT_MENU_H

#include "../TravelAgency/TravelAgency.h"
#include <sstream>
#include <iostream>
#include <limits>
#include <stdio.h>

using namespace std;

class Menu {
private:
    TravelAgency _travelAgency;
public:
    Menu(TravelAgency travelAgency);
    int validadeInput(string input);
    unsigned mainMenu();
    void SceneOneMenu();
    void SceneTwoMenu();

};


#endif //DA_PROJECT_MENU_H
