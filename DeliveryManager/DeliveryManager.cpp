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

}

void DeliveryManager::sceneTwo() {

}

void DeliveryManager::sceneThree() {

}
