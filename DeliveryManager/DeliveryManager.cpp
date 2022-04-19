//
// Created by Mafalda Magalhães on 05/04/2022.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "DeliveryManager.h"
#include "Order.h"

using namespace std;

DeliveryManager::DeliveryManager() = default;

void DeliveryManager::readOrders() {
    string  path = "../datasets/encomendas.txt";
    string line;
    // volume peso recompensa duração(s)
    string vol, weight, reward, duration;
    ifstream file(path);
    Order order;


    if(file.is_open()){
        getline(file, line);

        while (getline(file,line)){
            stringstream ss(line);
            getline(ss, vol, ' ');
            getline(ss, weight, ' ');
            getline(ss, reward, ' ');
            getline(ss, duration, ' ');

            int orderVolume = stoi(vol);
            int orderWeight = stoi(weight);
            int orderReward = stoi(reward);
            int orderDuration = stoi(duration);

            order = Order(orderVolume, orderWeight, orderReward, orderDuration);
            _orders.push_back(order);
        }
        file.close();
    } else {
        cout << "Erro ao abrir ficheiro das encomendas." << endl;
    }
}

void DeliveryManager::readVans() {
    string  path = "../datasets/carrinhas.txt";
    string line;
    // volMax pesoMax custo
    string volMax, weightMax, cost;
    ifstream file(path);
    Van van;


    if(file.is_open()){
        getline(file, line);

        while (getline(file,line)){
            stringstream ss(line);
            getline(ss, volMax, ' ');
            getline(ss, weightMax, ' ');
            getline(ss, cost, ' ');

            int vanVolMax = stoi(volMax);
            int vanWeightMax = stoi(weightMax);
            int vanCost = stoi(cost);

            van = Van(vanVolMax, vanWeightMax, vanCost);
            _vans.push_back(van);
        }
        file.close();
    } else {
        cout << "Erro ao abrir ficheiro das carrinhas." << endl;
    }

}

void DeliveryManager::sceneOne() {
    int totalVans = firstFitDecOrderDensity();
    cout << "Total de carrinhas: " << totalVans << endl;

}

bool DeliveryManager::compareOrderDensity(Order order1, Order order2) {
    return (order1.getDensity() < order2.getDensity());
}


bool DeliveryManager::compareVansDensityMax(Van van1, Van van2) {
    return (van1.getDensityMax() < van2.getDensityMax());
}


int DeliveryManager::firstFitOrderDensity(vector<int> ordersDensity, vector<int> vansDensity) {
    int totalVans = 0;

    //Vector with remaining space (density) in each van
    vector<int> vanRemainingDensity = vansDensity;

    for (int i = 0; i < ordersDensity.size(); i++){
        //Search for the first van than can fit the order according to its density
        for (int j = 0; j < totalVans; j++) {
            if (vanRemainingDensity.at(j) >= ordersDensity.at(i)) {
                vanRemainingDensity.at(j) = vanRemainingDensity.at(j) - ordersDensity.at(i);
                break;
            }
        }
    }
    return totalVans;
}


int DeliveryManager::firstFitDecOrderDensity() {
    vector<int> _ordersDensity;
    _ordersDensity.reserve(_orders.size());
    vector<int> _vansDensityMax;
    _vansDensityMax.reserve(_vans.size());

    //TO DO - Sort all order densities in decreasing order
    sort(_orders.begin(), _orders.end(), compareOrderDensity);

    //TO DO - Sort all vans densities in decreasing order
    sort(_vans.begin(), _vans.end(), compareVansDensityMax);

    for(int i = 0; i < _orders.size(); i ++){
        _ordersDensity.push_back(_orders.at(i).getDensity());
    }

    for(int i = 0; i < _vans.size(); i ++){
        _vansDensityMax.push_back(_vans.at(i).getDensityMax());
    }

    return firstFitOrderDensity(_ordersDensity, _vansDensityMax);
}

void DeliveryManager::sceneTwo() {

}

void DeliveryManager::sceneThree() {

}
