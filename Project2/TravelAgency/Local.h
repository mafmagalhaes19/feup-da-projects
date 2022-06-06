//
// Created by Mafalda Magalhães on 24/05/2022.
//

#ifndef DA_PROJECT_LOCAL_H
#define DA_PROJECT_LOCAL_H

#include <vector>

#include "Vehicle.h"

using namespace std;

class Local {
private:
    int _id;
    //The list of outgoing vehicles of the graph to adjacent locals
    vector<Vehicle> _adj;

    //Dijkstra Algorithm
    int _capacity;
    int _pred;
    bool _visited;

    //BFS algorithm
    int _transhipmentBFS;
    bool _visitedBFS;
    int _predBFS;

    //Ford Fulkerson
    bool _visitedFF;
    int _capacityFF;
    int _predFF;
    Vehicle _predVehicle;

public:
    explicit Local(int id, Vehicle predVehicle);
    void addAdjacentVehicle(Vehicle vehicle);

    vector<Vehicle> getAdj();

    int getId();

    //Dijkstra Algorithm
    int getCapacity();
    void setCapacity (int capacity);
    int getPred();
    void setPred( int pred);
    bool getVisited();
    void setVisited(bool visited);

    //BFS Algorithm
    int getTranshipmentBFS();
    void setTranshipmentBFS (int transhipmentBFS);
    int getPredBFS();
    void setPredBFS( int predBFS);
    bool getVisitedBFS();
    void setVisitedBFS(bool visited);

    //Ford Fulkerson
    bool getVisitedFF();
    void setVisitedFF(bool visitedFF);
    int getCapacityFF();
    void setCapacityFF(int capacityFF);
    int getPredFF();
    void setPredFF( int predFF);
    Vehicle * getPredVehicleFF();
    void setPredVehicleFF( Vehicle predVehicleFF);
    void setVehicleActiveFF(int source, int destination, bool activeFF);

};


#endif //DA_PROJECT_LOCAL_H
