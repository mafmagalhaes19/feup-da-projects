//
// Created by Mafalda Magalhães on 05/04/2022.
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

    void sceneOne();
    static bool compareOrderDensity(Order order1, Order order2);
    static bool compareVansDensityMax(Van van1, Van van2);
    //Returns number of vans needed using first fit approach (scan the previous vans in order -biggest van to smallest van- and place the order in the first van that fits)
    int firstFitOrderDensity(vector<int> ordersDensity, vector<int> vansDensity);
    //Returns number of vans needed using first fit decreasing algorithm
    int firstFitDecOrderDensity();

    void sceneTwo();
    void sceneThree();

private:
    vector<Order> _orders;
    vector<Van> _vans;



};


#endif //DA_PROJECT_DELIVERYMANAGER_H
