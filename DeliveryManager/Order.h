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

public:
    Order();
    Order(int volume, int weight, int reward, int duration);
};


#endif //DA_PROJECT_ORDER_H
