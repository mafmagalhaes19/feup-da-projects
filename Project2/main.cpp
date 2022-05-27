
#include <iostream>

#include "TravelAgency/TravelAgency.h"
#include "Menu/Menu.h"

using namespace std;

int main() {

    TravelAgency travelAgency;


    travelAgency.readDatasets();

    Menu menu = Menu(travelAgency);

    menu.mainMenu();


    return 0;
}