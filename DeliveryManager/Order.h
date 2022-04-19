//
// Created by Mafalda Magalhães on 05/04/2022.
//

#ifndef DA_PROJECT_ORDER_H
#define DA_PROJECT_ORDER_H

using namespace std;

class Order {
private:
    int _volume;
    int _weight;
    int _reward;
    int _duration;

    //Helper variables for scene one
    int _density;
    int _volMultWeight;

public:
    Order();
    Order(int volume, int weight, int reward, int duration);
    int getDensity();
    int getVolMultWeight();
};


#endif //DA_PROJECT_ORDER_H
