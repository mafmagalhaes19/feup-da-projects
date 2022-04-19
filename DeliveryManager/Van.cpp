//
// Created by Mafalda Magalhães on 05/04/2022.
//

#include "Van.h"

Van::Van() = default;

Van::Van(int volMax, int weightMax, int cost) {
    _volMax = volMax;
    _weightMax = weightMax;
    _cost = cost;
    _densityMax = weightMax / volMax;
    _volMultWeightMax = weightMax * volMax;
}

int Van::getDensityMax() {
    return _densityMax;
}

int Van::getVolMultWeightMax() {
    return _volMultWeightMax;
}


