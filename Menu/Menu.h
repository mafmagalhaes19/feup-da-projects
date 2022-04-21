//
// Created by Mafalda Magalhães on 05/04/2022.
//

#ifndef DA_PROJECT_MENU_H
#define DA_PROJECT_MENU_H

#include "DeliveryManager/DeliveryManager.h"
#include <string>

using namespace std;

class Menu {

private:

    DeliveryManager _deliveryManager;


public:

    Menu(DeliveryManager deliveryManager);

    int validadeInput(string input);

    unsigned mainMenu();

    void showSceneOneMenu();


};


#endif //DA_PROJECT_MENU_H
