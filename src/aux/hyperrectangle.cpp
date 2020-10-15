#include "hyperrectangle.h"


/** =================================
 *               PUBLIC
 *  =================================*/


Hyperrectangle::Hyperrectangle(std::vector<float> const& maxs, std::vector<float> const& mins){
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
