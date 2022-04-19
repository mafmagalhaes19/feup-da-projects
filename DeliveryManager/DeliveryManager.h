//
// Created by Mafalda Magalhães on 19/04/2022.
//

#ifndef DA_PROJECT_DELIVERYMANAGER_H
#define DA_PROJECT_DELIVERYMANAGER_H


#include "Order.h"
#include "Van.h"

#include <vector>

using namespace std;

class DeliveryManager {
public:
    DeliveryManager();

    //Reads the datasets
    void readOrders();
    void readVans();

private:
    vector<Order> _orders;
    vector<Van> _vans;



};


#endif //DA_PROJECT_DELIVERYMANAGER_H
