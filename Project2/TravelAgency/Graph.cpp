
#include "Graph.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>

#define INF (INT_MAX/2)

using namespace std;


Graph::Graph(int size) {
    _size = size;
    Vehicle vehicle;
    vehicle = Vehicle(0, 0, 0, 0);
    for(int i = 1; i < _size+1; i++) {
        Local local = Local(i, vehicle);
        _locals.push_back(local);
    }
}

void Graph::addVehicle(Vehicle vehicle) {
    _locals.at(vehicle.getSource()-1).addAdjacentVehicle(vehicle);
}


int Graph::dijkstraMaximumCapacity(int a, int b){
    dijkstra(a);
    //There is no path from a to b
    if(_locals[b-1].getCapacity() == 0){
        return -1;
    }
    return _locals[b-1].getCapacity();
}


vector<int> Graph::dijkstra_path(int source, int destination){
    //dijkstra(source);
    vector<int> path;
    if(_locals[destination-1].getCapacity() == 0){
        return path;
    }

    while( destination != source){
        path.push_back(destination);
        destination = _locals[destination-1].getPred();
    }
    path.push_back(source);
    return path;
}

void Graph::dijkstra(int s){
    //Priority Queue (n - number of maximum elements, -1 - returned value if key not found)
    MaxHeap<int, int> q(_size, -1);
    for(int v=0; v<_size; v++){
        _locals[v].setCapacity(0);
        _locals[v].setPred(0);
    }
    _locals[s-1].setCapacity(INF);
    //The "father" of the first node is the node itself
    _locals[s-1].setPred(s);

    for(int i = 1 ; i < _size+1; i++){
        q.insert(i, _locals[i-1].getCapacity());
    }

    while(!q.empty()){
        //Removes the key with the biggest value
        int u = q.removeMax();

        //cout << "Local " << u << "with capacity = " << _locals[u-1].getCapacity() << endl;

        //Cycle that goes through all adjcent nodes of u
        for(auto e : _locals[u-1].getAdj()){
            int v = e.getDestination();
            int w = e.getCapacity();
            if(min(_locals[u-1].getCapacity(), w) > _locals[v-1].getCapacity()) {
                _locals[v-1].setCapacity(min(_locals[u-1].getCapacity(), w));
                //Queue needs to have the same values that are stored in _locals[].dist
                q.increaseKey(v, _locals[v-1].getCapacity());
                _locals[v-1].setPred(u);
            }
        }
    }
}

void Graph::printDijkstra(int source, int dest) {
    int maximumCapacity = dijkstraMaximumCapacity(source, dest);
    if(maximumCapacity == -1){
        cout << "Nao existe nenhuma ligacao possivel entre a origem e o destino que escolheu." << endl;
        return;
    }
    vector<int> path = dijkstra_path(source, dest);

    // printing path from source to destination
    cout << "O caminho que o grupo tem de fazer e: " << endl;
    for(int i = path.size() - 1 ; i >= 0; i--){
        if(i != 0 ){
            cout << path[i]  << " --> ";
        }
        else{
            cout << path[i] << endl;
        }
    }

    // Final capacity is given by maximumCapacity of the graph
    cout << "A capacidade maxima do grupo e de " << maximumCapacity << " pessoas, com " << path.size() -1 << " transbordos." << endl;
}

void Graph::printBFSLessStops( int s, int dest)
{
    int maximumCapacity = INF;
    if (!bfsLS(s, dest)) {
        cout << "Nao existe nenhuma ligacao possivel entre a origem e o destino que escolheu." << endl;
        return;
    }
    //Vector path stores the shortest path
    vector<Local> path;
    Local crawl = _locals[dest-1];
    Local source = _locals[s-1];
    path.push_back(crawl);
    while (crawl.getId() != source.getId()) {
        path.push_back(_locals[crawl.getPredBFS()-1]);
        crawl = _locals[crawl.getPredBFS()-1];
    }
    //path.push_back(source);

    // printing path from source to destination
    cout << "O caminho que tem de fazer e: " << endl;
    for(int i = path.size() - 1 ; i >= 0; i--){
        if(path[i].getCapacity() < maximumCapacity){
            maximumCapacity = path[i].getCapacity();
        }

        if(i != 0 ){
            cout << path[i].getId()  << " --> ";
        }
        else{
            cout << path[i].getId() << endl;
        }
    }

    cout << "A capacidade maxima do grupo e de " << maximumCapacity << " pessoas, com " << path.size() - 1 << " transbordos." << endl;
}

bool Graph::bfsLS(int s, int d) {
    // initialize all nodes as unvisited
    for ( int v=0; v<_size; v++) {
        _locals[v].setVisitedBFS(false) ;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    _locals[s-1].setTranshipmentBFS(0);
    _locals[s-1].setVisitedBFS(true);
    while (!q.empty()) { // while there are still unprocessed nodes
        int u = q.front();
        q.pop(); // remove first element of q
        for (auto e : _locals[u-1].getAdj()) {
            int w = e.getDestination();
            if (!_locals[w-1].getVisitedBFS()) { // new node!
                q.push(w);
                _locals[w-1].setVisitedBFS(true);
                _locals[w-1].setTranshipmentBFS(_locals[u].getTranshipmentBFS() + 1);
                _locals[w-1].setPredBFS(u);
                if(w == d){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Graph::comparePathsFF(PathFordFulkerson path1, PathFordFulkerson path2) {
    return (path1.capacity > path2.capacity);
}

bool Graph::findAugmentationPath(int source, int destination, vector<Vehicle*> &vehicles){
    bool hasFoundAPath = false;
    Vehicle vehicle;
    vehicle = Vehicle(0, 0, 0, 0);
    for(int i = 0; i < _size; i++){
        _locals[i].setCapacityFF(0);
        _locals[i].setVisitedFF(false);
        _locals[i].setPredFF(0);
        _locals[i].setPredVehicleFF(vehicle);
    }
    queue<int> q;
    _locals[source-1].setCapacityFF(INF);
    q.push(source);

    while(!q.empty() ){
        int v = q.front();
        _locals[v-1].setVisitedFF(true);
        q.pop();

        for(auto e: _locals[v-1].getAdj()){
            if(e.getActiveFF()){
                int w = e.getDestination();
                if(!_locals[w-1].getVisitedFF() ){
                    int capacity = min(_locals[v-1].getCapacityFF(), e.getCapacity());
                    if(_locals[w-1].getCapacityFF() < capacity){
                        if(w == destination){
                            hasFoundAPath = true;
                        }
                        _locals[w-1].setCapacityFF(capacity);
                        _locals[w-1].setPredVehicleFF(e);
                        _locals[w-1].setPredFF(v);

                    }
                    q.push(w);
                }
            }
        }
    }

    if(!hasFoundAPath){
        return false;
    }
    while(destination != source){
        vehicles.push_back(_locals[destination-1].getPredVehicleFF());
        destination = _locals[destination-1].getPredFF();
    }
    return true;
}

void Graph::fordFulkerson(int source, int destination) {
    vector<Vehicle*> vehicles;
    for(int i = 0; i < _size; i++){
        _locals[i].setCapacityFF(0);
        for(auto e: _locals[i].getAdj()){
            e.setFlow(0);
        }
    }
    while(findAugmentationPath(source, destination, vehicles)){
        int capacity = INF;
        //Minimum global capacity
        for(auto vehicle: vehicles){
            capacity = min(capacity, vehicle->getCapacityFF());
        }
        PathFordFulkerson pathFF;

        //Residual capacity in the graph
        for(auto vehicle: vehicles){
            if(vehicle->getFlow() + capacity > vehicle->getCapacityFF()){
                capacity -= vehicle->getFlow() + capacity - vehicle->getCapacityFF();
            }
        }
        pathFF.capacity = capacity;

        //Final path
        for(auto vehicle: vehicles){
            int vehicleSource = vehicle->getSource();
            int vehicleDestination = vehicle->getDestination();
            vehicle->setFlow(vehicle->getFlow() + capacity);

            int newCapacity = capacity - vehicle->getFlow();
            _locals[vehicleSource-1].setVehicleCapacityFF(vehicleSource, vehicleDestination, newCapacity);

            if(vehicle->getFlow() == vehicle->getCapacity()){
                vehicle->setActiveFF(false);
                _locals[vehicleSource-1].setVehicleActiveFF(vehicleSource, vehicleDestination, false);
                _locals[vehicleSource-1].setVehicleCapacityFF(vehicleSource, vehicleDestination, 0);
            }
            pathFF.path.push_back({vehicle->getDuration(), vehicle->getDestination()});
            pathFF.duration += vehicle->getDuration();
        }
        pathFF.path.push_back({0, 1});
        _pathsFF.push_back(pathFF);
        vehicles.clear();
    }

}

void Graph::printFordFulkerson(int source, int destination, int groupDimension, bool isSceneTwoTwo, int groupAdded) {
    _pathsFF.clear();
    _chosenPathsFF.clear();

    fordFulkerson(source, destination);

    int maxElements = 0;
    for(int i = 0; i < _pathsFF.size(); i++){
        maxElements += _pathsFF[i].capacity;
    }

    if(maxElements < groupDimension){
        cout << "Nao existe ligacao possivel entre a origem e o destino que escolheu para o numero de pessoas escolhidas (" << groupDimension << ")." << endl;
        cout << "A capacidade maxima do grupo para este caminho e de: " << maxElements <<"." << endl;
        return;
    }

    //Sort the Paths by decreasing order in capacity
    sort(_pathsFF.begin(), _pathsFF.end(), comparePathsFF);

    cout << "O caminho que tem de fazer e: " << endl;

    int remainingSpots = groupDimension;

    for(int i = 0; i < _pathsFF.size(); i++ ){
        if(remainingSpots == 0){
            break;
        }
        _chosenPathsFF.push_back(_pathsFF[i]);
        printPathFF(_pathsFF[i], source, remainingSpots);

    }

    if(isSceneTwoTwo){
        cout << endl;
        cout << "2.2" << endl;
        cout << "Grupo adicional" << endl;
        cout << "O caminho que tem de fazer e: " << endl;
        remainingSpots += groupAdded;
        for (int i = 0; i < _pathsFF.size(); i++){
            if(remainingSpots == 0){
                break;
            }
            _chosenPathsFF.push_back(_pathsFF[i]);
            printPathFF(_pathsFF[i], source, remainingSpots);
        }

    }

}

void Graph::printPathFF(PathFordFulkerson &pathFF, int source, int &remainingSpots) {
    int capacity = INF;
    for (int i =  pathFF.path.size() - 1; i >= 0; i--){
        if(!pathFF.isFull) {
            capacity = min(capacity, pathFF.capacity);
            int next = pathFF.path[i].second;
            if(count(pathFF.completePath.begin(), pathFF.completePath.end(), next) == 0){
                pathFF.completePath.push_back(next);
            }
            if(i == 0){
                cout << next << " (capacidade = " << capacity << " / utilizados = " << min(remainingSpots, capacity) << ")." << endl;
                _totalElementsMax += capacity;
                pathFF.capacity -= min(remainingSpots, capacity);
                remainingSpots -= capacity;

                //There are still remaining people
                if(remainingSpots > 0){
                    pathFF.isFull = true;
                }

                //There are no more remaining spots
                else {
                    if (remainingSpots == 0){
                        pathFF.isFull = true;
                    }
                    else {
                        remainingSpots = 0;
                    }
                }
            }
            else{
                cout <<next  << " --> ";
            }
        }

    }
}

void Graph::printFordFulkersonMax(int source, int destination) {
    _pathsFF.clear();

    fordFulkerson(source, destination);

    int maxElements = 0;
    for(PathFordFulkerson pathFF: _pathsFF){
        maxElements += pathFF.capacity;
    }

    if( _pathsFF.size() == 0){
        cout << "Nao existe ligacao possivel entre a origem e o destino que escolheu." << endl;
        return;
    }

    int remainingSpots = INF;
    _totalElementsMax = 0;

    cout << "O caminho que tem de fazer e: " << endl;


    for (int i = 0; i < _pathsFF.size(); i++){
        //totalElements += _pathsFF[i].capacity;
        printPathFF(_pathsFF[i], source, remainingSpots);

    }
    cout << endl;
    cout <<  "A dimensao maxima do grupo e de " << _totalElementsMax << " pessoas." << endl;

}

void Graph::fastestReunion() {
    int firstReunion = 0;
    int mightBeReunion = 0;
    bool endCycle = false;
    //The path needs to be equal starting from the end to the reunion point, so we will iterate the chosen paths in reverse order
    for(int i = 0; i < _chosenPathsFF.size(); i++){
        if(endCycle){
            break;
        }
        firstReunion = mightBeReunion;
        mightBeReunion = 0;
       for(int j = _chosenPathsFF[i].completePath.size() - 1; j >= 0 ; j--){
           if(mightBeReunion == 0){
               mightBeReunion = _chosenPathsFF[i].completePath[j];
           }
           if(mightBeReunion != _chosenPathsFF[i].completePath[j]){
               endCycle = true;
               break;
           }
       }
    }

    if(firstReunion == 0){
        cout << "Nao ha nenhum local onde o grupo se possa encontrar antes de chegar ao destino." << endl;
    }
    else{
        cout << "O grupo pode encontrar-se no local " << firstReunion << " e continuar junto no resto do percurso" << endl;
    }


}
