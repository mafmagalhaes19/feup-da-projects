
#include "Graph.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>

#define INF (INT_MAX/2)

using namespace std;


Graph::Graph(int size) {
    _size = size;
    for(int i = 1; i < _size+1; i++) {
        Local local = Local(i);
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
        q.insert(v, 0);
        _locals[v].setVisited(false);
        _locals[v].setPred(0);
    }
    _locals[s-1].setCapacity(INF);
    //Changes the value of s in the priority queue
    q.increaseKey(s, INF);
    //The "father" of the first node is the node itself
    _locals[s-1].setPred(s);

    while(!q.empty()){
        //Removes the key with the biggest value
        int u = q.removeMax() + 1;

        //cout << "Local " << u << "with capacity = " << _locals[u-1].getCapacity() << endl;
        _locals[u-1].setVisited(true);

        //Cycle that goes through all adjcent nodes of u
        for(auto e : _locals[u-1].getAdj()){
            int v = e.getDestination();
            int w = e.getCapacity();
            /*if(min(_locals[u-1].getCapacity(), w) > _locals[v-1].getCapacity()) {
                _locals[v-1].setCapacity(min(_locals[u-1].getCapacity(), w));
                q.increaseKey(v, _locals[v-1].getCapacity());
                _locals[v-1].setPred(u);
            }*/

            if(!_locals[v-1].getVisited() && (_locals[u-1].getCapacity() < w) && (_locals[u-1].getCapacity() > _locals[v-1].getCapacity())){
                _locals[v-1].setCapacity(_locals[u-1].getCapacity());
                //Queue needs to have the same values that are stored in _locals[].dist
                q.increaseKey(v, _locals[v-1].getCapacity());
                _locals[v-1].setPred(u);
            }

            else if(!_locals[v-1].getVisited() && (_locals[u-1].getCapacity() > w) && (w > _locals[v-1].getCapacity())){
                _locals[v-1].setCapacity(w);
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
    cout << "A capacidade maxima do grupo e de " << maximumCapacity << " pessoas." << endl;
}

void Graph::printBFSLessStops( int s, int dest)
{
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
        crawl = _locals[crawl.getPredBFS()];
    }
    path.push_back(source);

    // printing path from source to destination
    cout << "O caminho que tem de fazer e: " << endl;
    for(int i = path.size() - 1 ; i >= 0; i--){
        if(i != 0 ){
            cout << path[i].getId()  << " --> ";
        }
        else{
            cout << path[i].getId() << endl;
        }
    }

    cout << "O numero total de transbordos e de " << path.size() - 1 << "." << endl;
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
