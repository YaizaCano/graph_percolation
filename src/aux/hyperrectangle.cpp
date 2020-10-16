#include "hyperrectangle.h"


/** =================================
 *               PUBLIC
 *  =================================*/


Hyperrectangle::Hyperrectangle(IntervalValuesType const& maxs, IntervalValuesType const& mins){
    maxValues = maxs;
    minValues = mins;
}



std::pair<Hyperrectangle, Hyperrectangle> Hyperrectangle::split(unsigned int axis, float splitValue) const{
    // split less rectangle
    auto mid = maxValues;
    mid[axis] = splitValue;
    less = Hyperrectangle(minValues, mid);
    // split greater rectangle
    mid = minValues;
    mid[axis] = splitValue;
    greater = Hyperrectangle(mid, maxValues);
    return {less, greater}

}

float Hyperrectangle::minDistance(Hyperrectangle const& other) const{
    return 0;
}

float Hyperrectangle::maxDistance(Hyperrectangle const& other) const{
    return 0; 
}


float Hyperrectangle::calculateDistance(IntervalValuesType const& v1, IntervalValuesType const& v2){
    auto size = v1.size();
    float distance = 0;
    for(auto i = 0; i < size; ++i){
        distance += v1[i]*v1[i] + v2[i]*v2[i];
    }

    return sqrt(distance);
}
