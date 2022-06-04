//
// Created by Mafalda Magalhães on 24/05/2022.
//

#ifndef DA_PROJECT_GRAPH_H
#define DA_PROJECT_GRAPH_H

#include <vector>
#include <list>

#include "Local.h"
#include "maxHeap.h"

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

    //Dijkstra Algorithm
    int dijkstraMaximumCapacity(int a, int b);
    void dijkstra(int s);
    vector<int> dijkstra_path(int a, int b);
    void printDijkstra(int source, int dest);

    //BFS Algorithm
    void printBFSLessStops(int source, int dest);
    bool bfsLS(int s, int d);

};


#endif //DA_PROJECT_GRAPH_H
