
#ifndef DA_PROJECT_TRAVELAGENCY_H
#define DA_PROJECT_TRAVELAGENCY_H

#include <vector>
#include <string>

#include "Graph.h"

using namespace std;

class TravelAgency {
private:
    //Each dataset has a graph representing it
    vector<Graph> _graphs;
    int _chosenGraph;

public:
    void readDatasets();
    void readOneDataset(string filename);

    void setGraph(int chosenGraph);

    void sceneOneOne(int source, int destination);
    void sceneOneTwo(int source, int destination);

    void sceneTwoOne(int source, int destination, int groupDimension, bool isSceneTwoTwo, int groupAdded);
    void sceneTwoThree(int source, int destination);
    void sceneTwoFour(int source, int destination, int groupDimension);
    void sceneTwoFive();
};


#endif //DA_PROJECT_TRAVELAGENCY_H
