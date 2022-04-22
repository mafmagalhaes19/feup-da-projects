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

    //Scene 1 - Combine volMax and weightMax in a variable
    int _volPlusWeight;

    //Scene 2 - we want to use the cheaper vans that have the most space (benefit = volMax + weightMax - cost)
    int _benefit;


public:
    Van();
    Van(int volMax, int weightMax, int cost);
    int getWeightMax();
    int getVolMax();
    int getVolPlusWeight();
    int getCost();
    int getBenefit();
    void setWeightMax(int weightMax);
    void setVolMax (int volMax);
    void setVolPlusWeight (int volPlusWeight);

};


#endif //DA_PROJECT_VAN_H
