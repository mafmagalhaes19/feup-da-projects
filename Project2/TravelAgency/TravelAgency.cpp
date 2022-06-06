
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "TravelAgency.h"
#include "Vehicle.h"
#include "Graph.h"

using namespace std;

void TravelAgency::readDatasets() {
    string  path1 = "../Tests_B/in01_b.txt";
    readOneDataset(path1);

    string  path2 = "../Tests_B/in02_b.txt";
    readOneDataset(path2);

    string  path3 = "../Tests_B/in03_b.txt";
    readOneDataset(path3);

    string  path4 = "../Tests_B/in04_b.txt";
    readOneDataset(path4);

    string  path5 = "../Tests_B/in05_b.txt";
    readOneDataset(path5);

    string  path6 = "../Tests_B/in06_b.txt";
    readOneDataset(path6);

    string  path7 = "../Tests_B/in07_b.txt";
    readOneDataset(path7);

    string  path8 = "../Tests_B/in08_b.txt";
    readOneDataset(path8);

    string  path9 = "../Tests_B/in09_b.txt";
    readOneDataset(path9);

    string  path10 = "../Tests_B/in10_b.txt";
    readOneDataset(path10);

    string  path11 = "../Tests_B/in11.txt";
    readOneDataset(path11);

}

void TravelAgency::readOneDataset(string filename) {
    // número de vértices (N) e o número de ramos (R)
    string firstLine;
    string n, r;
    // <Origem> <Destino> <Capacidade> <Duração>
    string line;
    string source, destination, capacity, duration;
    ifstream file(filename);

    if(file.is_open()){
        getline(file, firstLine);

        stringstream fs(firstLine);
        getline(fs, n, ' ');
        getline(fs, r, ' ');


        int graphSize = stoi(n);
        int graphNumberOfEdges = stoi(r);

        Graph graph = Graph(graphSize);


        while (graphNumberOfEdges > 0){
            getline(file,line);
            stringstream ss(line);
            getline(ss, source, ' ');
            getline(ss, destination, ' ');
            getline(ss, capacity, ' ');
            getline(ss, duration, ' ');

            int vehicleSource = stoi(source);
            int vehicleDestination = stoi(destination);
            int vehicleCapacity = stoi(capacity);
            int vehicleDuration = stoi(duration);

            Vehicle vehicle = Vehicle(vehicleSource, vehicleDestination, vehicleCapacity, vehicleDuration);
            graph.addVehicle(vehicle);
            graphNumberOfEdges--;
        }
        _graphs.push_back(graph);
        file.close();
    } else {
        cout << "Erro ao abrir ficheiro: " << filename << endl;
    }
}

void TravelAgency::setGraph(int chosenGraph) {
    _chosenGraph = chosenGraph;
}

//1.1. Maximizar a dimensão do grupo e indicar um qualquer encaminhamento.
void TravelAgency::sceneOneOne(int source, int destination) {
    cout << endl;
    cout << "1.1" << endl;
    _graphs[_chosenGraph-1].printDijkstra(source, destination);
}

void TravelAgency::sceneOneTwo(int source, int destination) {
    cout << endl;
    cout << "1.2" << endl;
    cout << "MAXIMIZAR A DIMENSAO DO GRUPO" << endl;
    _graphs[_chosenGraph-1].printDijkstra(source, destination);
    cout << endl;
    cout << "MINIMIZAR O NUMERO DE TRANSBORDOS" << endl;
    _graphs[_chosenGraph-1].printBFSLessStops(source, destination);
    cout << endl;
}

void TravelAgency::sceneTwoOne(int source, int destination, int groupDimension) {
    cout << endl;
    cout << "2.1" << endl;
    cout << "CAMINHO A PERCORRER" << endl;
    _graphs[_chosenGraph-1].printFordFulkerson(source, destination, groupDimension);
    cout << endl;
}

void TravelAgency::sceneTwoTwo() {
    cout << "2.2" << endl;
}

void TravelAgency::sceneTwoThree() {
    cout << "2.3" << endl;
}

void TravelAgency::sceneTwoFour() {
    cout << "2.4" << endl;
}

void TravelAgency::sceneTwoFive() {
    cout << "2.5" << endl;
}





