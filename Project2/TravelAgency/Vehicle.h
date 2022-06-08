
#ifndef DA_PROJECT_VEHICLE_H
#define DA_PROJECT_VEHICLE_H

using namespace std;

class Vehicle {
private:
    int _source;
    int _destination;
    int _capacity;
    int _duration;

    //Ford Fulkerson
    int _flow;
    bool _activeFF;
    int _residual;

public:
    Vehicle();
    Vehicle(int source, int destination, int capacity, int duration);

    //getters
    int getSource();
    int getDestination();
    int getCapacity();
    int getDuration();
    int getResidual();

    //setters
    void setFlow(int flow);
    void setResidual(int residual);

};


#endif //DA_PROJECT_VEHICLE_H
