//
// Created by Mafalda Magalhães on 24/05/2022.
//
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