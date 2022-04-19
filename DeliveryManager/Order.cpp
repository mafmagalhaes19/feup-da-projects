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
}

