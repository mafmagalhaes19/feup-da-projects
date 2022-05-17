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

    void sceneOneWeight();
    static bool compareOrderWeight(Order order1, Order order2);
    static bool compareVansWeightMax(Van van1, Van van2);
    //Returns number of vans needed using best fit decreasing algorithm
    int bestFitWeight();

    void sceneOneVolume();
    static bool compareOrderVolume(Order order1, Order order2);
    static bool compareVansVolMax(Van van1, Van van2);
    //Returns number of vans needed using best fit decreasing algorithm
    int bestFitVolume();

    void sceneOneVolPlusWeight();
    static bool compareOrderVolPlusWeight(Order order1, Order order2);
    static bool compareVansVolPlusWeight(Van van1, Van van2);
    //Returns number of vans needed using best fit decreasing algorithm
    int bestFitVolPlusWeight();

    void sceneTwoBenefit();
    static bool compareVansBenefit(Van van1, Van van2);
    static bool compareOrdersReward(Order order1, Order order2);
    int bestFitCostBenefit();

    void sceneTwoCost();
    static bool compareVansCost(Van van1, Van van2);
    int bestFitCost();

    static bool compareOrderDuration(Order order1, Order order2);
    void sceneThree();

private:
    vector<Order> _orders;
    vector<Van> _vans;



};


#endif //DA_PROJECT_DELIVERYMANAGER_H
