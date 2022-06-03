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
    double _dist;
    int _pred;
    bool _visited;

public:
    explicit Local(int id);
    void addAdjacentVehicle(Vehicle vehicle);

    vector<Vehicle> getAdj();
    double getDistance();
    void setDistance (double dist);
    int getPred();
    void setPred( int pred);
    bool getVisited();
    void setVisited(bool visited);


};


#endif //DA_PROJECT_LOCAL_H
