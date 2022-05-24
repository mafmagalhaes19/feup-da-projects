//
// Created by Mafalda Magalhães on 24/05/2022.
//

#include "Graph.h"

Graph::Graph(int size) {
    _size = size;
    for(int i = 1; i < _size+1; i++) {
        Local local = Local(i);
        _locals.push_back(local);
    }
}

void Graph::addVehicle(Vehicle vehicle) {
    _locals.at(vehicle.getSource()-1).addAdjacentVehicle(vehicle);
}
