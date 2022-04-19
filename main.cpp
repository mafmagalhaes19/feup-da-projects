//
// Created by Mafalda Magalhães on 19/04/2022.
//

#include <iostream>
#include "DeliveryManager/DeliveryManager.h"
#include "Menu/Menu.h"

int main() {

    DeliveryManager deliveryManager;

    //stcpMap.readParagens();
    //stcpMap.readListaLinhas();

    Menu menu = Menu(deliveryManager);

    menu.mainMenu();


    return 0;
}