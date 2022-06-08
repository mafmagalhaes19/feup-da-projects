//
// Created by Mafalda Magalhães on 24/05/2022.
//

#include "Local.h"

Local::Local(int id, Vehicle predVehicle){
    _id = id;
}

void Local::addAdjacentVehicle(Vehicle vehicle) {
    _adj.push_back(vehicle);
}

vector<Vehicle>& Local::getAdj() {
    return _adj;
}

int Local::getId(){
    return _id;
}

int Local::getCapacity() {
    return _capacity;
}

void Local::setCapacity(int capacity) {
    _capacity = capacity;
}

int Local::getPred() {
    return _pred;
}

void Local::setPred(int pred) {
    _pred= pred;
}

int Local::getTranshipmentBFS() {
    return _transhipmentBFS;
}

void Local::setTranshipmentBFS(int transhipmentBFS) {
    _transhipmentBFS = transhipmentBFS;
}

int Local::getPredBFS() {
    return _predBFS;
}

void Local::setPredBFS(int predBFS) {
    _predBFS= predBFS;
}

bool Local::getVisitedBFS() {
    return _visitedBFS;
}


void Local::setVisitedBFS(bool visitedBFS) {
    _visitedBFS = visitedBFS;
}

bool Local::getVisitedFF() {
    return _visitedFF;
}

void Local::setVisitedFF(bool visitedFF) {
    _visitedFF = visitedFF;
}

int Local::getPredFF() {
    return _predFF;
}

void Local::setPredFF(int predFF) {
    _predFF = predFF;
}

void Local::beginFordFulkerson(){
    for(int i = 0; i < _adj.size(); i++){
        int aux = _adj[i].getCapacity();
        _adj[i].setFlow(0);
        _adj[i].setResidual(aux);
    }
}
