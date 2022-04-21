//
// Created by Mafalda Magalhães on 05/04/2022.
//

#ifndef DA_PROJECT_VAN_H
#define DA_PROJECT_VAN_H

using namespace std;

class Van {
private:
    int _volMax;
    int _weightMax;
    int _cost;


public:
    Van();
    Van(int volMax, int weightMax, int cost);
    int getWeightMax();
    int getVolMax();
    void setWeightMax(int weightMax);
    void setVolMax (int volMax);

};


#endif //DA_PROJECT_VAN_H
