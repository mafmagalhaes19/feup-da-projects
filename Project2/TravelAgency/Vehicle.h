
#ifndef DA_PROJECT_VEHICLE_H
#define DA_PROJECT_VEHICLE_H

using namespace std;

class Vehicle {
private:
    int _source;
    int _destination;
    int _capacity;
    int _duration;

public:
    Vehicle(int source, int destination, int capacity, int duration);
    int getSource();
    int getDestination();
    int getCapacity();
    int getDuration();

};


#endif //DA_PROJECT_VEHICLE_H
