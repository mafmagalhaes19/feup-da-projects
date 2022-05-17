//
// Created by Mafalda Magalhães on 05/04/2022.
//

#include <iostream>
#include "DeliveryManager/DeliveryManager.h"
#include "Menu/Menu.h"

using namespace std;

int main() {

    DeliveryManager deliveryManager;


    deliveryManager.readOrders();
    deliveryManager.readVans();

    Menu menu = Menu(deliveryManager);

    menu.mainMenu();


    return 0;
}