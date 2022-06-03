//
// Created by Mafalda Magalhães on 24/05/2022.
//

#ifndef DA_PROJECT_GRAPH_H
#define DA_PROJECT_GRAPH_H

#include <vector>
#include <list>

#include "Local.h"
#include "minHeap.h"

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

    double dijkstra_distance(int a, int b);
    void dijkstra(int s);
    list<int> dijkstra_path(int a, int b);
    void printDijkstra(int source, int dest);

};


#endif //DA_PROJECT_GRAPH_H
