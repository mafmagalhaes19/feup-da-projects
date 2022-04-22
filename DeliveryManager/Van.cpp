//
// Created by Mafalda Magalhães on 05/04/2022.
//

#include "Van.h"

Van::Van() = default;

Van::Van(int volMax, int weightMax, int cost) {
    _volMax = volMax;
    _weightMax = weightMax;
    _cost = cost;
    _volPlusWeight = volMax + weightMax;
    _benefit = volMax + weightMax - cost;
}

int Van::getWeightMax() {
    return _weightMax;
}

int Van::getVolMax() {
    return _volMax;
}

int Van::getVolPlusWeight() {
    return _volPlusWeight;
}

int Van::getCost() {
    return _cost;
}

int Van::getBenefit() {
    return _benefit;
}

void Van::setWeightMax(int weightMax) {
    _weightMax = weightMax;
}

void Van::setVolMax(int volMax) {
    _volMax = volMax;
}


void Van::setVolPlusWeight(int volPlusWeight)  {
    _volPlusWeight = volPlusWeight;
}
