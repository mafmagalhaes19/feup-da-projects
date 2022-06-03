
#include "Graph.h"

#include <iostream>
#include <utility>
#include <algorithm>
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
    if(_locals[b-1].getCapacity() == INF){
        return -1;
    }
    return _locals[b-1].getCapacity();
}


list<int> Graph::dijkstra_path(int a, int b){
    dijkstra(a);
    list<int> path;
    if(_locals[b-1].getDistance() == INF){
        return path;
    }
    path.push_back(b);
    int v = b;
    while( v != a){
        v = _locals[v-1].getPred();
        path.push_front(v);
    }
    return path;
}

void Graph::dijkstra(int s){
    //Priority Queue (n - number of maximum elements, -1 - returned value if key not found)
    MaxHeap<int, int> q(_size, -1);
    for(int v=0; v<_size; v++){
        _locals[v].setCapacity(0);
        q.insert(v, 0);
        _locals[v].setVisited(false);
    }
    _locals[s-1].setCapacity(INF);
    //Changes the value of s in the priority queue
    q.increaseKey(s, INF);
    //The "father" of the first node is the node itself
    _locals[s-1].setPred(s);
    while(q.getSize()>0){
        //Removes the key with the smallest value
        int u = q.removeMax();
        //FIX HERE
        // cout << "Node " << u << "with dist = " << nodes[u].dist << endl;
        _locals[u-1].setVisited(true);
        //Cycle that goes through all adjcent nodes of u
        for(auto e : _locals[u-1].getAdj()){
            int v = e.getDestination();
            double w = e.getDuration();
            if(!_locals[v-1].getVisited() && (_locals[u-1].getDistance() + w < _locals[v-1].getDistance()) ){
                _locals[v-1].setDistance(_locals[u-1].getDistance() + w);
                //Queue needs to have the same values that are stored in nodes[].dist
                q.decreaseKey(v, _locals[v-1].getDistance());
                _locals[v-1].setPred(u);
            }
        }
    }
}

void Graph::printDijkstra(int source, int dest) {
    int maximumCapacity = dijkstraMaximumCapacity(source, dest);
    if(maximumCapacity == 0){
        cout << "Nao existe nenhuma ligacao possivel entre a origem e o destino que escolheu." << endl;
        return;
    }
    list<int> path = dijkstra_path(source, dest);

    // printing path from source to destination
    cout << "O caminho que tem de fazer e: " << endl;
    list<int>::iterator it = path.begin();
    int aux = path.size();
    while(it != path.end()){
        if(aux>1){
            //cout << _locals[*it].paragem.getCode()  << " - " << nodes[*it].paragem.getName() << " --> ";
        }
        else{
            //cout << nodes[*it].paragem.getCode()  << " - " << nodes[*it].paragem.getName() <<endl;
        }
        it++;
        aux--;
    }

    // distance from source is in distance array
    cout << "A distancia total e de " << distance << " km." << endl;
}
