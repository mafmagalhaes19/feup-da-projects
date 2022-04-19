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

    //Helper variables for scene one
    int _densityMax;
    int _volMultWeightMax;


public:
    Van();
    Van(int volMax, int weightMax, int cost);
    int getDensityMax();
    int getVolMultWeightMax();

};


#endif //DA_PROJECT_VAN_H