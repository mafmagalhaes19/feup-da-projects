//
// Created by Mafalda Magalhães on 05/04/2022.
//

#include "Order.h"

Order::Order() = default;

Order::Order(int volume, int weight, int reward, int duration) {
    _volume = volume;
    _weight = weight;
    _reward = reward;
    _duration = duration;
    _density = weight / volume;
    _volMultWeight = weight * volume;
}

int Order::getDensity() {
    return _density;
}

int Order::getVolMultWeight() {
    return _volMultWeight;
}

int Order::getDuration() {
    return _duration;
}

