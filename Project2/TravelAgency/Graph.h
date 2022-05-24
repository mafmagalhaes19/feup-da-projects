//
// Created by Mafalda Magalhães on 24/05/2022.
//

#ifndef DA_PROJECT_GRAPH_H
#define DA_PROJECT_GRAPH_H

#include <vector>

#include "Local.h"

using namespace std;

class Graph {
private:
    //Graph size - locals are numbered from 1 to _size
    int _size;
    //The list of Locals
    vector<Local> _locals;

public:
    explicit Graph(int size);
    void addVehicle(Vehicle vehicle);

};


#endif //DA_PROJECT_GRAPH_H
