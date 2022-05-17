//
// Created by Mafalda Magalhães on 05/04/2022.
//

#include "Order.h"

Order::Order() = default;

Order::Order(int volume, int weight, int reward, int duration) {
    _volume = volume;
    _weight = weight;
    _reward = reward;
    _volPlusWeight = volume + weight;
    _duration = duration;
}

int Order::getWeight() {
    return _weight;
}

int Order::getVolume() {
    return _volume;
}

int Order::getVolPlusWeight() {
    return _volPlusWeight;
}

int Order::getReward(){
    return _reward;
}

int Order::getDuration() {
    return _duration;
}

