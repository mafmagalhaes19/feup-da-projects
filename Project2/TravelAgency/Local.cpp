//
// Created by Mafalda Magalhães on 24/05/2022.
//

#include "Local.h"

Local::Local(int id, Vehicle predVehicle) : _predVehicle(predVehicle) {
    _id = id;
}

void Local::addAdjacentVehicle(Vehicle vehicle) {
    _adj.push_back(vehicle);
}

vector<Vehicle> Local::getAdj() {
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

bool Local::getVisited() {
    return _visited;
}


void Local::setVisited(bool visited) {
    _visited = visited;
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

int Local::getCapacityFF() {
    return _capacityFF;
}

void Local::setCapacityFF(int capacityFF) {
    _capacityFF;
}

int Local::getPredFF() {
    return _predFF;
}

void Local::setPredFF(int predFF) {
    _predFF = predFF;
}

Vehicle Local::getPredVehicleFF() {
    return _predVehicle;
}

void Local::setPredVehicleFF(Vehicle predVehicleFF) {
    _predVehicle = predVehicleFF;
}


