
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

public:
    Vehicle();
    Vehicle(int source, int destination, int capacity, int duration);
    int getSource();
    int getDestination();
    int getCapacity();
    int getDuration();
    int getFlow();
    void setFlow(int flow);
    bool getActiveFF();
    void setActiveFF(bool activeFF);

};


#endif //DA_PROJECT_VEHICLE_H
