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

void DeliveryManager::sceneOneWeight() {
    int totalVans = bestFitWeight();
    cout << "Total de carrinhas: " << totalVans << endl;

}

bool DeliveryManager::compareOrderWeight(Order order1, Order order2) {
    return (order1.getWeight() > order2.getWeight());
}


bool DeliveryManager::compareVansWeightMax(Van van1, Van van2) {
    return (van1.getWeightMax() > van2.getWeightMax());
}


int DeliveryManager::bestFitWeight() {

    //Sort all order by weight in decreasing order
    sort(_orders.begin(), _orders.end(), compareOrderWeight);

    //Sort all vans by weight in decreasing order
    sort(_vans.begin(), _vans.end(), compareVansWeightMax);

    vector<Van> vanRemaingSpace = _vans;
    //Vector of vans used in a day
    vector<Van> usedVans;
    usedVans.push_back(vanRemaingSpace[0]);
    vanRemaingSpace.erase(vanRemaingSpace.begin());

    //Initialize minimum space (weight) available at the "biggest" van
    int minWeight = usedVans[0].getWeightMax();
    //Initialize the index of the best van (minimum space)
    int vanIndex = 0;

    //Place orders in the vans
    for (int i = 0; i < _orders.size(); i++) {
        bool orderPacked = false;

        //We are trying to fit the order in the best van (minimum space available), so we try to find the best
        if(usedVans[vanIndex].getWeightMax() >= _orders[i].getWeight() && usedVans[vanIndex].getVolMax() >= _orders[i].getVolume() && !orderPacked){
            minWeight = usedVans[vanIndex].getWeightMax() - _orders[i].getWeight();
            usedVans[vanIndex].setWeightMax(minWeight);
            int remainingVolume = usedVans[vanIndex].getVolMax() - _orders[i].getVolume();
            usedVans[vanIndex].setVolMax(remainingVolume);
            orderPacked = true;

            //We filled a van and we are looking for the next best van (minimum space)
            if(minWeight == 0){
                for(int k = 0; k < usedVans.size(); k++){
                    //In the first iteration we change the minWeight to the first available van
                    if (minWeight == 0){
                        if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0){
                            minWeight = usedVans[k].getWeightMax();
                            vanIndex = k;
                        }
                    }
                    //Then we look for the actual best van (minimum space)
                    if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0 && usedVans[k].getWeightMax() < minWeight){
                        minWeight = usedVans[k].getWeightMax();
                        vanIndex = k;
                    }
                }
            }
        }

        int currentBestFitIndex = -1;
        int currentBestMinWeight = 0;

        if(!orderPacked){
            //We are trying to get the order int the best van for its current weight (minimum space available for this order) when it doesn't fit the current van with the minimum space available
            for (int k = 0; k < usedVans.size(); k++){
                //We change the currentBestFit to the first van tha can fit the current order
                if(currentBestFitIndex == -1){
                    if (usedVans[k].getWeightMax() >= _orders[i].getWeight() && usedVans[k].getVolMax() >= _orders[i].getVolume()){
                        currentBestFitIndex = k;
                        currentBestMinWeight = usedVans[k].getWeightMax();
                    }
                }
                //We check to see if there is another van with less space available that can also contain the order
                if (usedVans[k].getWeightMax() >= _orders[i].getWeight() && usedVans[k].getVolMax() >= _orders[i].getVolume() && usedVans[k].getWeightMax() < currentBestMinWeight) {
                    currentBestFitIndex = k;
                    currentBestMinWeight = usedVans[k].getWeightMax();
                }
            }
        }

        //If no van could fit the current order, use another van from the remaining vans vector
        if(currentBestFitIndex == -1 && !orderPacked){
            bool fits = false;
            int auxIndexRemaining = 0;
            while(!fits){
                //Find the first van from the remaing vans vector that can fit the current order and push it to the used vans
                if(vanRemaingSpace[auxIndexRemaining].getWeightMax() >= _orders[i].getWeight() && vanRemaingSpace[auxIndexRemaining].getVolMax() >= _orders[i].getVolume() && !orderPacked){
                    orderPacked = true;
                    usedVans.push_back(vanRemaingSpace[0]);
                    vanRemaingSpace.erase(vanRemaingSpace.begin());
                    fits = true;
                    int lastVan = usedVans.size()-1;
                    usedVans[lastVan].setWeightMax(usedVans[lastVan].getWeightMax()-_orders[i].getWeight());
                    int remainingVolume = usedVans[lastVan].getVolMax() - _orders[i].getVolume();
                    usedVans[lastVan].setVolMax(remainingVolume);
                    //If the remaining weight in the last added van is smaller than the minWeight, update it
                    if(usedVans[lastVan].getWeightMax() < minWeight){
                        minWeight = usedVans[lastVan].getWeightMax();
                        vanIndex = lastVan;
                    }
                }
            }
        }

        //We found a van that can fit the current order from the used vans vector
        else if(!orderPacked){
            orderPacked =true;
            usedVans[currentBestFitIndex].setWeightMax(usedVans[currentBestFitIndex].getWeightMax()-_orders[i].getWeight());
            int remainingVolume = usedVans[currentBestFitIndex].getVolMax() - _orders[i].getVolume();
            usedVans[currentBestFitIndex].setVolMax(remainingVolume);
            //If the remaining weight in this van is smaller than the minWeight, update it
            if(usedVans[currentBestFitIndex].getWeightMax() < minWeight){
                minWeight = usedVans[currentBestFitIndex].getWeightMax();
                vanIndex = currentBestFitIndex;
            }
        }
    }

    return usedVans.size();
}

void DeliveryManager::sceneOneVolume() {
    int totalVans = bestFitVolume();
    cout << "Total de carrinhas: " << totalVans << endl;

}

bool DeliveryManager::compareOrderVolume(Order order1, Order order2) {
    return (order1.getVolume() > order2.getVolume());
}


bool DeliveryManager::compareVansVolMax(Van van1, Van van2) {
    return (van1.getVolMax() > van2.getVolMax());
}


int DeliveryManager::bestFitVolume() {

    //Sort all order by weight in decreasing order
    sort(_orders.begin(), _orders.end(), compareOrderVolume);

    //Sort all vans by weight in decreasing order
    sort(_vans.begin(), _vans.end(), compareVansVolMax);

    vector<Van> vanRemaingSpace = _vans;
    //Vector of vans used in a day
    vector<Van> usedVans;
    usedVans.push_back(vanRemaingSpace[0]);
    vanRemaingSpace.erase(vanRemaingSpace.begin());

    //Initialize minimum space (volume) available at the "biggest" van
    int minVol = usedVans[0].getVolMax();
    //Initialize the index of the best van (minimum space)
    int vanIndex = 0;

    //Place orders in the vans
    for (int i = 0; i < _orders.size(); i++) {
        bool orderPacked = false;

        //We are trying to fit the order in the best van (minimum space available), so we try to find the best
        if(usedVans[vanIndex].getWeightMax() >= _orders[i].getWeight() && usedVans[vanIndex].getVolMax() >= _orders[i].getVolume() && !orderPacked){
            minVol = usedVans[vanIndex].getVolMax() - _orders[i].getVolume();
            usedVans[vanIndex].setVolMax(minVol);
            int remainingWeight = usedVans[vanIndex].getWeightMax() - _orders[i].getWeight();
            usedVans[vanIndex].setWeightMax(remainingWeight);
            orderPacked = true;

            //We filled a van and we are looking for the next best van (minimum space)
            if(minVol == 0){
                for(int k = 0; k < usedVans.size(); k++){
                    //In the first iteration we change the minWeight to the first available van
                    if (minVol == 0){
                        if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0){
                            minVol = usedVans[k].getVolMax();
                            vanIndex = k;
                        }
                    }
                    //Then we look for the actual best van (minimum space)
                    if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0 && usedVans[k].getVolMax() < minVol){
                        minVol = usedVans[k].getVolMax();
                        vanIndex = k;
                    }
                }
            }
        }

        int currentBestFitIndex = -1;
        int currentBestMinVol = 0;

        if(!orderPacked){
            //We are trying to get the order int the best van for its current weight (minimum space available for this order) when it doesn't fit the current van with the minimum space available
            for (int k = 0; k < usedVans.size(); k++){
                //We change the currentBestFit to the first van tha can fit the current order
                if(currentBestFitIndex == -1){
                    if (usedVans[k].getWeightMax() >= _orders[i].getWeight() && usedVans[k].getVolMax() >= _orders[i].getVolume()){
                        currentBestFitIndex = k;
                        currentBestMinVol = usedVans[k].getVolMax();
                    }
                }
                //We check to see if there is another van with less space available that can also contain the order
                if (usedVans[k].getWeightMax() >= _orders[i].getWeight() && usedVans[k].getVolMax() >= _orders[i].getVolume() && usedVans[k].getVolMax() < currentBestMinVol) {
                    currentBestFitIndex = k;
                    currentBestMinVol = usedVans[k].getVolMax();
                }
            }
        }

        //If no van could fit the current order, use another van from the remaining vans vector
        if(currentBestFitIndex == -1 && !orderPacked){
            bool fits = false;
            int auxIndexRemaining = 0;
            while(!fits){
                //Find the first van from the remaining vans vector that can fit the current order and push it to the used vans
                if(vanRemaingSpace[auxIndexRemaining].getWeightMax() >= _orders[i].getWeight() && vanRemaingSpace[auxIndexRemaining].getVolMax() >= _orders[i].getVolume() && !orderPacked){
                    orderPacked = true;
                    usedVans.push_back(vanRemaingSpace[0]);
                    vanRemaingSpace.erase(vanRemaingSpace.begin());
                    fits = true;
                    int lastVan = usedVans.size()-1;
                    usedVans[lastVan].setWeightMax(usedVans[lastVan].getWeightMax()-_orders[i].getWeight());
                    int remainingVolume = usedVans[lastVan].getVolMax() - _orders[i].getVolume();
                    usedVans[lastVan].setVolMax(remainingVolume);
                    //If the remaining weight in the last added van is smaller than the minWeight, update it
                    if(usedVans[lastVan].getVolMax() < minVol){
                        minVol = usedVans[lastVan].getVolMax();
                        vanIndex = lastVan;
                    }
                }
            }
        }

            //We found a van that can fit the current order from the used vans vector
        else if(!orderPacked){
            orderPacked =true;
            usedVans[currentBestFitIndex].setVolMax(usedVans[currentBestFitIndex].getVolMax()-_orders[i].getVolume());
            int remainingWeight = usedVans[currentBestFitIndex].getWeightMax() - _orders[i].getWeight();
            usedVans[currentBestFitIndex].setWeightMax(remainingWeight);
            //If the remaining weight in this van is smaller than the minWeight, update it
            if(usedVans[currentBestFitIndex].getVolMax() < minVol){
                minVol = usedVans[currentBestFitIndex].getVolMax();
                vanIndex = currentBestFitIndex;
            }
        }
    }

    return usedVans.size();
}


void DeliveryManager::sceneOneVolPlusWeight() {
    int totalVans = bestFitVolPlusWeight();
    cout << "Total de carrinhas: " << totalVans << endl;

}

bool DeliveryManager::compareOrderVolPlusWeight(Order order1, Order order2) {
    return (order1.getVolPlusWeight() > order2.getVolPlusWeight());
}


bool DeliveryManager::compareVansVolPlusWeight(Van van1, Van van2) {
    return (van1.getVolPlusWeight() > van2.getVolPlusWeight());
}


int DeliveryManager::bestFitVolPlusWeight() {

    //Sort all order by volPlusWeight in decreasing order
    sort(_orders.begin(), _orders.end(), compareOrderVolPlusWeight);

    //Sort all vans by volPlusWeight in decreasing order
    sort(_vans.begin(), _vans.end(), compareVansVolPlusWeight);

    vector<Van> vanRemaingSpace = _vans;
    //Vector of vans used in a day
    vector<Van> usedVans;
    usedVans.push_back(vanRemaingSpace[0]);
    vanRemaingSpace.erase(vanRemaingSpace.begin());

    //Initialize minimum space (volPlusWeight) available at the "biggest" van
    int minVolPlusWeight = usedVans[0].getVolPlusWeight();
    //Initialize the index of the best van (minimum space)
    int vanIndex = 0;

    //Place orders in the vans
    for (int i = 0; i < _orders.size(); i++) {
        bool orderPacked = false;

        //We are trying to fit the order in the best van (minimum space available), so we try to find the best
        if(usedVans[vanIndex].getWeightMax() >= _orders[i].getWeight() && usedVans[vanIndex].getVolMax() >= _orders[i].getVolume() && !orderPacked){
            minVolPlusWeight = usedVans[vanIndex].getVolPlusWeight() - _orders[i].getVolPlusWeight();
            usedVans[vanIndex].setVolPlusWeight(minVolPlusWeight);
            int remainingWeight = usedVans[vanIndex].getWeightMax() - _orders[i].getWeight();
            usedVans[vanIndex].setWeightMax(remainingWeight);
            int remainingVolume = usedVans[vanIndex].getVolMax() - _orders[i].getVolume();
            usedVans[vanIndex].setVolMax(remainingVolume);
            orderPacked = true;

            //We filled a van and we are looking for the next best van (minimum space)
            if(minVolPlusWeight == 0){
                for(int k = 0; k < usedVans.size(); k++){
                    //In the first iteration we change the minVolPlusWeight to the first available van
                    if (minVolPlusWeight == 0){
                        if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0){
                            minVolPlusWeight = usedVans[k].getVolPlusWeight();
                            vanIndex = k;
                        }
                    }
                    //Then we look for the actual best van (minimum space)
                    if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0 && usedVans[k].getVolPlusWeight() < minVolPlusWeight){
                        minVolPlusWeight = usedVans[k].getVolPlusWeight();
                        vanIndex = k;
                    }
                }
            }
        }

        int currentBestFitIndex = -1;
        int currentBestMinVolPlusWeight = 0;

        if(!orderPacked){
            //We are trying to get the order int the best van for its current weight (minimum space available for this order) when it doesn't fit the current van with the minimum space available
            for (int k = 0; k < usedVans.size(); k++){
                //We change the currentBestFit to the first van tha can fit the current order
                if(currentBestFitIndex == -1){
                    if (usedVans[k].getWeightMax() >= _orders[i].getWeight() && usedVans[k].getVolMax() >= _orders[i].getVolume()){
                        currentBestFitIndex = k;
                        currentBestMinVolPlusWeight = usedVans[k].getVolPlusWeight();
                    }
                }
                //We check to see if there is another van with less space available that can also contain the order
                if (usedVans[k].getWeightMax() >= _orders[i].getWeight() && usedVans[k].getVolMax() >= _orders[i].getVolume() && usedVans[k].getVolPlusWeight() < currentBestMinVolPlusWeight) {
                    currentBestFitIndex = k;
                    currentBestMinVolPlusWeight = usedVans[k].getVolMax();
                }
            }
        }

        //If no van could fit the current order, use another van from the remaining vans vector
        if(currentBestFitIndex == -1 && !orderPacked){
            bool fits = false;
            int auxIndexRemaining = 0;
            while(!fits){
                //Find the first van from the remaining vans vector that can fit the current order and push it to the used vans
                if(vanRemaingSpace[auxIndexRemaining].getWeightMax() >= _orders[i].getWeight() && vanRemaingSpace[auxIndexRemaining].getVolMax() >= _orders[i].getVolume() && !orderPacked){
                    orderPacked = true;
                    usedVans.push_back(vanRemaingSpace[0]);
                    vanRemaingSpace.erase(vanRemaingSpace.begin());
                    fits = true;
                    int lastVan = usedVans.size()-1;
                    usedVans[lastVan].setVolPlusWeight(usedVans[lastVan].getVolPlusWeight() - _orders[i].getVolPlusWeight());
                    usedVans[lastVan].setWeightMax(usedVans[lastVan].getWeightMax()-_orders[i].getWeight());
                    int remainingVolume = usedVans[lastVan].getVolMax() - _orders[i].getVolume();
                    usedVans[lastVan].setVolMax(remainingVolume);
                    //If the remaining weight in the last added van is smaller than the minWeight, update it
                    if(usedVans[lastVan].getVolMax() < minVolPlusWeight){
                        minVolPlusWeight = usedVans[lastVan].getVolPlusWeight();
                        vanIndex = lastVan;
                    }
                }
            }
        }

            //We found a van that can fit the current order from the used vans vector
        else if(!orderPacked){
            orderPacked =true;
            usedVans[currentBestFitIndex].setVolPlusWeight(usedVans[currentBestFitIndex].getVolPlusWeight() - _orders[i].getVolPlusWeight());
            usedVans[currentBestFitIndex].setVolMax(usedVans[currentBestFitIndex].getVolMax()-_orders[i].getVolume());
            int remainingWeight = usedVans[currentBestFitIndex].getWeightMax() - _orders[i].getWeight();
            usedVans[currentBestFitIndex].setWeightMax(remainingWeight);
            //If the remaining weight in this van is smaller than the minWeight, update it
            if(usedVans[currentBestFitIndex].getVolPlusWeight() < minVolPlusWeight){
                minVolPlusWeight = usedVans[currentBestFitIndex].getVolPlusWeight();
                vanIndex = currentBestFitIndex;
            }
        }
    }

    return usedVans.size();
}

void DeliveryManager::sceneTwoBenefit() {
    int profit = bestFitCostBenefit();
    if(profit > 0){
        cout << "O lucro foi de " << profit << " euros!" << endl;
    }
    else{
        cout << "Infelizmente nao ha lucro, por isso as encomendas nao se vao realizar!" << endl;
    }
}

bool DeliveryManager::compareOrdersReward(Order order1, Order order2) {
    return (order1.getReward() < order2.getReward());
}

bool DeliveryManager::compareVansBenefit(Van van1, Van van2) {
    return (van1.getVolPlusWeight() > van2.getVolPlusWeight());
}

int DeliveryManager::bestFitCostBenefit() {

    int totalCost;
    int totalReward;

    vector<Order> betterOrders = _orders;

    sort(betterOrders.begin(), betterOrders.end(), compareOrdersReward);

    //Remove the 10% orders with less reward
    int lessThanTen = _orders.size() / 10;

    for (int i = 0; i < lessThanTen +1; i++){
        betterOrders.erase(betterOrders.begin());
    }

    sort( betterOrders.begin(), betterOrders.end(), compareOrderVolPlusWeight);

    //Sort all vans by benefit in decreasing order
    sort(_vans.begin(), _vans.end(), compareVansBenefit);

    vector<Van> vanRemaingSpace = _vans;
    //Vector of vans used in a day
    vector<Van> usedVans;
    usedVans.push_back(vanRemaingSpace[0]);
    totalCost += usedVans[0].getCost();
    vanRemaingSpace.erase(vanRemaingSpace.begin());

    //Initialize minimum space (volPlusWeight) available at the "biggest" van
    int minVolPlusWeight = usedVans[0].getVolPlusWeight();
    //Initialize the index of the best van (minimum space)
    int vanIndex = 0;

    //Place orders in the vans
    for (int i = 0; i < betterOrders.size(); i++) {
        bool orderPacked = false;

        //We are trying to fit the order in the best van (maximum benefit), so we try to find the best
        if(usedVans[vanIndex].getWeightMax() >= betterOrders[i].getWeight() && usedVans[vanIndex].getVolMax() >= betterOrders[i].getVolume() && !orderPacked){
            minVolPlusWeight = usedVans[vanIndex].getVolPlusWeight() - betterOrders[i].getVolPlusWeight();
            usedVans[vanIndex].setVolPlusWeight(minVolPlusWeight);
            int remainingWeight = usedVans[vanIndex].getWeightMax() - betterOrders[i].getWeight();
            usedVans[vanIndex].setWeightMax(remainingWeight);
            int remainingVolume = usedVans[vanIndex].getVolMax() - betterOrders[i].getVolume();
            usedVans[vanIndex].setVolMax(remainingVolume);
            totalReward += betterOrders[i].getReward();
            orderPacked = true;

            //We filled a van and we are looking for the next best van (minimum space)
            if(minVolPlusWeight == 0){
                for(int k = 0; k < usedVans.size(); k++){
                    //In the first iteration we change the minVolPlusWeight to the first available van
                    if (minVolPlusWeight == 0){
                        if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0){
                            minVolPlusWeight = usedVans[k].getVolPlusWeight();
                            vanIndex = k;
                        }
                    }
                    //Then we look for the actual best van (minimum space)
                    if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0 && usedVans[k].getVolPlusWeight() < minVolPlusWeight){
                        minVolPlusWeight = usedVans[k].getVolPlusWeight();
                        vanIndex = k;
                    }
                }
            }
        }

        int currentBestFitIndex = -1;
        int currentBestMinVolPlusWeight = 0;

        if(!orderPacked){
            //We are trying to get the order int the best van for its current weight (minimum space available for this order) when it doesn't fit the current van with the minimum space available
            for (int k = 0; k < usedVans.size(); k++){
                //We change the currentBestFit to the first van tha can fit the current order
                if(currentBestFitIndex == -1){
                    if (usedVans[k].getWeightMax() >= betterOrders[i].getWeight() && usedVans[k].getVolMax() >= betterOrders[i].getVolume()){
                        currentBestFitIndex = k;
                        currentBestMinVolPlusWeight = usedVans[k].getVolPlusWeight();
                    }
                }
                //We check to see if there is another van with less space available that can also contain the order
                if (usedVans[k].getWeightMax() >= betterOrders[i].getWeight() && usedVans[k].getVolMax() >= betterOrders[i].getVolume() && usedVans[k].getVolPlusWeight() < currentBestMinVolPlusWeight) {
                    currentBestFitIndex = k;
                    currentBestMinVolPlusWeight = usedVans[k].getVolMax();
                }
            }
        }

        //If no van could fit the current order, use another van from the remaining vans vector
        if(currentBestFitIndex == -1 && !orderPacked){
            bool fits = false;
            int auxIndexRemaining = 0;
            while(!fits){
                //Find the first van from the remaining vans vector that can fit the current order and push it to the used vans
                if(vanRemaingSpace[auxIndexRemaining].getWeightMax() >= betterOrders[i].getWeight() && vanRemaingSpace[auxIndexRemaining].getVolMax() >= betterOrders[i].getVolume() && !orderPacked){
                    orderPacked = true;
                    usedVans.push_back(vanRemaingSpace[0]);
                    vanRemaingSpace.erase(vanRemaingSpace.begin());
                    fits = true;
                    int lastVan = usedVans.size()-1;
                    totalCost += usedVans[lastVan].getCost();
                    totalReward += betterOrders[i].getReward();
                    usedVans[lastVan].setVolPlusWeight(usedVans[lastVan].getVolPlusWeight() - betterOrders[i].getVolPlusWeight());
                    usedVans[lastVan].setWeightMax(usedVans[lastVan].getWeightMax()-betterOrders[i].getWeight());
                    int remainingVolume = usedVans[lastVan].getVolMax() - betterOrders[i].getVolume();
                    usedVans[lastVan].setVolMax(remainingVolume);
                    //If the remaining weight in the last added van is smaller than the minWeight, update it
                    if(usedVans[lastVan].getVolMax() < minVolPlusWeight){
                        minVolPlusWeight = usedVans[lastVan].getVolPlusWeight();
                        vanIndex = lastVan;
                    }
                }
            }
        }

            //We found a van that can fit the current order from the used vans vector
        else if(!orderPacked){
            orderPacked =true;
            totalReward += betterOrders[i].getReward();
            usedVans[currentBestFitIndex].setVolPlusWeight(usedVans[currentBestFitIndex].getVolPlusWeight() - betterOrders[i].getVolPlusWeight());
            usedVans[currentBestFitIndex].setVolMax(usedVans[currentBestFitIndex].getVolMax()-betterOrders[i].getVolume());
            int remainingWeight = usedVans[currentBestFitIndex].getWeightMax() - betterOrders[i].getWeight();
            usedVans[currentBestFitIndex].setWeightMax(remainingWeight);
            //If the remaining weight in this van is smaller than the minWeight, update it
            if(usedVans[currentBestFitIndex].getVolPlusWeight() < minVolPlusWeight){
                minVolPlusWeight = usedVans[currentBestFitIndex].getVolPlusWeight();
                vanIndex = currentBestFitIndex;
            }
        }
    }

    int profit = totalReward - totalCost;

    return profit;
}

void DeliveryManager::sceneTwoCost() {
    int profit = bestFitCost();
    if(profit > 0){
        cout << "O lucro foi de " << profit << " euros!" << endl;
    }
    else{
        cout << "Infelizmente nao ha lucro, por isso as encomendas nao se vao realizar!" << endl;
    }
}

bool DeliveryManager::compareVansCost(Van van1, Van van2) {
    return (van1.getCost() > van2.getCost());
}

int DeliveryManager::bestFitCost() {

    int totalCost;
    int totalReward;

    //Sort all vans by benefit in decreasing order
    sort(_vans.begin(), _vans.end(), compareVansCost);

    vector<Van> vanRemaingSpace = _vans;
    //Vector of vans used in a day
    vector<Van> usedVans;
    usedVans.push_back(vanRemaingSpace[0]);
    totalCost += usedVans[0].getCost();
    vanRemaingSpace.erase(vanRemaingSpace.begin());

    //Initialize minimum space (volPlusWeight) available at the "biggest" van
    int minVolPlusWeight = usedVans[0].getVolPlusWeight();
    //Initialize the index of the best van (minimum space)
    int vanIndex = 0;

    //Place orders in the vans
    for (int i = 0; i < _orders.size(); i++) {
        bool orderPacked = false;

        //We are trying to fit the order in the best van (maximum benefit), so we try to find the best
        if(usedVans[vanIndex].getWeightMax() >= _orders[i].getWeight() && usedVans[vanIndex].getVolMax() >= _orders[i].getVolume() && !orderPacked){
            minVolPlusWeight = usedVans[vanIndex].getVolPlusWeight() - _orders[i].getVolPlusWeight();
            usedVans[vanIndex].setVolPlusWeight(minVolPlusWeight);
            int remainingWeight = usedVans[vanIndex].getWeightMax() - _orders[i].getWeight();
            usedVans[vanIndex].setWeightMax(remainingWeight);
            int remainingVolume = usedVans[vanIndex].getVolMax() - _orders[i].getVolume();
            usedVans[vanIndex].setVolMax(remainingVolume);
            totalReward += _orders[i].getReward();
            orderPacked = true;

            //We filled a van and we are looking for the next best van (minimum space)
            if(minVolPlusWeight == 0){
                for(int k = 0; k < usedVans.size(); k++){
                    //In the first iteration we change the minVolPlusWeight to the first available van
                    if (minVolPlusWeight == 0){
                        if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0){
                            minVolPlusWeight = usedVans[k].getVolPlusWeight();
                            vanIndex = k;
                        }
                    }
                    //Then we look for the actual best van (minimum space)
                    if(usedVans[k].getWeightMax() > 0 && usedVans[k].getVolMax() > 0 && usedVans[k].getVolPlusWeight() < minVolPlusWeight){
                        minVolPlusWeight = usedVans[k].getVolPlusWeight();
                        vanIndex = k;
                    }
                }
            }
        }

        int currentBestFitIndex = -1;
        int currentBestMinVolPlusWeight = 0;

        if(!orderPacked){
            //We are trying to get the order int the best van for its current weight (minimum space available for this order) when it doesn't fit the current van with the minimum space available
            for (int k = 0; k < usedVans.size(); k++){
                //We change the currentBestFit to the first van tha can fit the current order
                if(currentBestFitIndex == -1){
                    if (usedVans[k].getWeightMax() >= _orders[i].getWeight() && usedVans[k].getVolMax() >= _orders[i].getVolume()){
                        currentBestFitIndex = k;
                        currentBestMinVolPlusWeight = usedVans[k].getVolPlusWeight();
                    }
                }
                //We check to see if there is another van with less space available that can also contain the order
                if (usedVans[k].getWeightMax() >= _orders[i].getWeight() && usedVans[k].getVolMax() >= _orders[i].getVolume() && usedVans[k].getVolPlusWeight() < currentBestMinVolPlusWeight) {
                    currentBestFitIndex = k;
                    currentBestMinVolPlusWeight = usedVans[k].getVolMax();
                }
            }
        }

        //If no van could fit the current order, use another van from the remaining vans vector
        if(currentBestFitIndex == -1 && !orderPacked){
            bool fits = false;
            int auxIndexRemaining = 0;
            while(!fits){
                //Find the first van from the remaining vans vector that can fit the current order and push it to the used vans
                if(vanRemaingSpace[auxIndexRemaining].getWeightMax() >= _orders[i].getWeight() && vanRemaingSpace[auxIndexRemaining].getVolMax() >= _orders[i].getVolume() && !orderPacked){
                    orderPacked = true;
                    usedVans.push_back(vanRemaingSpace[0]);
                    vanRemaingSpace.erase(vanRemaingSpace.begin());
                    fits = true;
                    int lastVan = usedVans.size()-1;
                    totalCost += usedVans[lastVan].getCost();
                    totalReward += _orders[i].getReward();
                    usedVans[lastVan].setVolPlusWeight(usedVans[lastVan].getVolPlusWeight() - _orders[i].getVolPlusWeight());
                    usedVans[lastVan].setWeightMax(usedVans[lastVan].getWeightMax()-_orders[i].getWeight());
                    int remainingVolume = usedVans[lastVan].getVolMax() - _orders[i].getVolume();
                    usedVans[lastVan].setVolMax(remainingVolume);
                    //If the remaining weight in the last added van is smaller than the minWeight, update it
                    if(usedVans[lastVan].getVolMax() < minVolPlusWeight){
                        minVolPlusWeight = usedVans[lastVan].getVolPlusWeight();
                        vanIndex = lastVan;
                    }
                }
            }
        }

        //We found a van that can fit the current order from the used vans vector
        else if(!orderPacked){
            orderPacked =true;
            totalReward += _orders[i].getReward();
            usedVans[currentBestFitIndex].setVolPlusWeight(usedVans[currentBestFitIndex].getVolPlusWeight() - _orders[i].getVolPlusWeight());
            usedVans[currentBestFitIndex].setVolMax(usedVans[currentBestFitIndex].getVolMax()-_orders[i].getVolume());
            int remainingWeight = usedVans[currentBestFitIndex].getWeightMax() - _orders[i].getWeight();
            usedVans[currentBestFitIndex].setWeightMax(remainingWeight);
            //If the remaining weight in this van is smaller than the minWeight, update it
            if(usedVans[currentBestFitIndex].getVolPlusWeight() < minVolPlusWeight){
                minVolPlusWeight = usedVans[currentBestFitIndex].getVolPlusWeight();
                vanIndex = currentBestFitIndex;
            }
        }
    }

    int profit = totalReward - totalCost;

    return profit;
}



bool DeliveryManager::compareOrderDuration(Order order1, Order order2) {
    return (order1.getDuration() < order2.getDuration());
}

void DeliveryManager::sceneThree() {
    //Total time
    int sumTime = 0;
    double count = 0;
    double averageTime = 0;
    vector<int> _ordersDuration;
    _ordersDuration.reserve(_orders.size());

    //Sort the orders by ascending duration
    sort(_orders.begin(), _orders.end(), compareOrderDuration);

    for(int i = 0; sumTime + _orders[i].getDuration() <= 28800; i++) {
        sumTime += _orders[i].getDuration();
        count++;
    }
    //Average delivery time per order
    averageTime = sumTime/count;

    cout << "O tempo medio minimo e de  " << averageTime << " s por encomenda" << endl;
    cout << "Foram entregues " << count << " encomendas (as " << count << " encomendas com a duracao de entrega mais curta)" << endl;
}
