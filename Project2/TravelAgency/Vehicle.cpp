//
// Created by Mafalda Magalhães on 24/05/2022.
//

#include "Vehicle.h"

Vehicle::Vehicle(int source, int destination, int capacity, int duration) {
    _source = source;
    _destination = destination;
    _capacity = capacity;
    _duration = duration;
}

int Vehicle::getSource() {
    return _source;
}

int Vehicle::getDestination() {
    return _destination;
}

int Vehicle::getCapacity() {
    return _capacity;
}

int Vehicle::getDuration() {
    return _duration;
}
