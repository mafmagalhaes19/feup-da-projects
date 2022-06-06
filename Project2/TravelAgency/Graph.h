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

struct PathFordFulkerson{
    //Vector of a pair of int that contains the duration and the destination of the path
    vector<pair<int, int>> path;
    int capacity;
    int duration = 0;
    bool isFull;
};


class Graph {

private:
    //Graph size - locals are numbered from 1 to _size
    int _size;

    //The list of Locals
    vector<Local> _locals;

    //Ford Fulkerson
    vector<PathFordFulkerson> _pathsFF;

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

    //Ford Fulkerson
    bool findAugmentationPath(int source, int destination, vector<Vehicle*> &vehicles);
    void fordFulkerson(int source, int destination);
    static bool comparePathsFF(PathFordFulkerson path1, PathFordFulkerson path2);
    void printFordFulkerson(int source, int destination, int groupDimension, bool isSceneTwoTwo, int groupAdded);
    void printPathFF(PathFordFulkerson pathFF, int source, int &remainingSpots);
    void printFordFulkersonMax(int source, int destination);


};


#endif //DA_PROJECT_GRAPH_H
