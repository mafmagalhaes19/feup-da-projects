//
// Created by Mafalda Magalhães on 24/05/2022.
//

#include "Local.h"

Local::Local(int id) {
    _id = id;
}

void Local::addAdjacentVehicle(Vehicle vehicle) {
    _adj.push_back(vehicle);
}

vector<Vehicle> Local::getAdj() {
    return _adj;
}

double Local::getDistance() {
    return _dist;
}

void Local::setDistance(double dist) {
    _dist = dist;
}

int Local::getPred() {
    return _pred;
}

void Local::setPred(int pred) {
    _pred= pred;
}

bool Local::getVisited() {
    return _visited;
}


void Local::setVisited(bool visited) {
    _visited = visited;
}



